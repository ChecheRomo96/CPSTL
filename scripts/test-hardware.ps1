#requires -Version 7.0
param(
    [Parameter(Mandatory = $true)]
    [ValidatePattern('^COM[0-9]+$')]
    [string]$Port,
    [string]$ArduinoCli = '',
    [ValidateSet('C', 'CPP')]
    [string]$Allocation = 'C',
    [ValidateRange(5, 300)]
    [int]$TimeoutSeconds = 30,
    [switch]$InjectFailure
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$Allocation = $Allocation.ToUpperInvariant()
$root = Split-Path -Parent $PSScriptRoot
$sketch = Join-Path $root 'tests/Arduino/CPSTLHardware'
$fqbn = 'arduino:avr:mega:cpu=atmega2560'
if (-not $ArduinoCli) {
    $command = Get-Command arduino-cli -ErrorAction SilentlyContinue
    if ($command) { $ArduinoCli = $command.Source }
    else {
        $bundled = Resolve-Path "$env:LOCALAPPDATA/Microsoft/WinGet/Packages/ArduinoSA.IDE.stable_*/resources/app/lib/backend/resources/arduino-cli.exe" -ErrorAction SilentlyContinue
        if ($bundled) { $ArduinoCli = @($bundled)[0].Path }
    }
}
if (-not $ArduinoCli -or -not (Test-Path -LiteralPath $ArduinoCli -PathType Leaf)) {
    throw 'arduino-cli not found; supply -ArduinoCli with its executable path'
}
$buildId = [guid]::NewGuid().ToString('N').Substring(0, 8).TrimStart('0').ToUpperInvariant()
if (-not $buildId) { $buildId = '1' }
$runRoot = Join-Path $root "build/hardware/atmega2560/$Allocation-$buildId"
$buildPath = Join-Path $runRoot 'firmware'
New-Item -ItemType Directory -Force $buildPath | Out-Null
Write-Host "Hardware evidence: $runRoot"

function Invoke-Arduino {
    param([string[]]$CliArguments, [string]$Log, [int]$LimitSeconds = 120)
    $info = [System.Diagnostics.ProcessStartInfo]::new($ArduinoCli)
    $info.UseShellExecute = $false
    $info.CreateNoWindow = $true
    $info.RedirectStandardOutput = $true
    $info.RedirectStandardError = $true
    foreach ($argument in $CliArguments) { $info.ArgumentList.Add($argument) }
    $process = [System.Diagnostics.Process]::new()
    $process.StartInfo = $info
    try {
        [void]$process.Start()
        $stdout = $process.StandardOutput.ReadToEndAsync()
        $stderr = $process.StandardError.ReadToEndAsync()
        $exited = $process.WaitForExit($LimitSeconds * 1000)
        if (-not $exited) { $process.Kill($true); $process.WaitForExit() }
        ($stdout.GetAwaiter().GetResult() + "`n" + $stderr.GetAwaiter().GetResult()) |
            Set-Content (Join-Path $runRoot $Log)
        if (-not $exited) { throw "arduino-cli timeout after $LimitSeconds seconds; see $Log" }
        if ($process.ExitCode -ne 0) { throw "arduino-cli failed ($($process.ExitCode)); see $Log" }
    }
    finally { $process.Dispose() }
}

$expected = @(Get-Content (Join-Path $sketch 'Cases.h') | ForEach-Object {
    if ($_ -match '^CPSTL_HW_CASE\((\w+)\)$') { $Matches[1] }
})
if ($expected.Count -eq 0 -or @($expected | Select-Object -Unique).Count -ne $expected.Count) {
    throw 'Empty or duplicate hardware case manifest'
}
$metadata = [ordered]@{
    startedUtc = [DateTime]::UtcNow.ToString('o')
    buildId = $buildId; port = $Port; fqbn = $fqbn; allocation = $Allocation
    injectedFailure = [bool]$InjectFailure; expectedCases = $expected
    status = 'INCOMPLETE'; results = @()
}
$serial = $null
try {
    & $ArduinoCli version | Set-Content (Join-Path $runRoot 'arduino-cli-version.txt')
    if ($LASTEXITCODE -ne 0) { throw 'Cannot read Arduino CLI version' }
    & $ArduinoCli board list --format json | Set-Content (Join-Path $runRoot 'boards.json')
    if ($LASTEXITCODE -ne 0) { throw 'Cannot enumerate boards' }
    $boards = Get-Content (Join-Path $runRoot 'boards.json') -Raw | ConvertFrom-Json
    $matching = @($boards.detected_ports | Where-Object {
        $_.port.address -eq $Port -and $_.PSObject.Properties.Name -contains 'matching_boards'
    } | Where-Object { @($_.matching_boards | Where-Object fqbn -eq 'arduino:avr:mega').Count -gt 0 })
    if ($matching.Count -ne 1) { throw "An Arduino Mega must be identified on $Port before flashing" }
    & git -C $root rev-parse HEAD | Set-Content (Join-Path $runRoot 'cpstl-revision.txt')
    & git -C $root status --short | Set-Content (Join-Path $runRoot 'working-tree.txt')
    & git -C (Join-Path $root 'tools/RoModularBuild') rev-parse HEAD | Set-Content (Join-Path $runRoot 'romodular-revision.txt')
    Invoke-Arduino -CliArguments @('board', 'details', '--fqbn', $fqbn, '--format', 'json') -Log 'board-details.json'
    $flags = "-DCPSTL_HW_BUILD_ID=0x${buildId}UL -DCPSTL_USING_${Allocation}_ALLOCATION"
    if ($InjectFailure) { $flags += ' -DCPSTL_HW_INJECT_FAILURE' }
    $compileArguments = @('compile', '--fqbn', $fqbn, '--library', $root,
        '--build-path', $buildPath, '--warnings', 'all', '--verbose',
        '--build-property', "compiler.cpp.extra_flags=$flags", $sketch)
    $uploadArguments = @('upload', '--fqbn', $fqbn, '--port', $Port,
        '--build-path', $buildPath, '--verify', '--verbose', $sketch)
    @{ compile = $compileArguments; upload = $uploadArguments } | ConvertTo-Json -Depth 4 |
        Set-Content (Join-Path $runRoot 'commands.json')
    Invoke-Arduino -CliArguments $compileArguments -Log 'compile.log'
    $normalizedRoot = $root.Replace('\', '/') + '/'
    $ownWarnings = @(Get-Content (Join-Path $runRoot 'compile.log') | Where-Object {
        $_ -match 'warning:' -and $_.Replace('\', '/').Contains($normalizedRoot)
    })
    if ($ownWarnings.Count -gt 0) { throw 'CPSTL compiled with warnings; see compile.log' }
    $metadata.firmwareSha256 = (Get-FileHash (Join-Path $buildPath 'CPSTLHardware.ino.hex')).Hash
    # Arduino's AVR platform invokes avrdude; verbose output records its exact command.
    Invoke-Arduino -CliArguments $uploadArguments -Log 'upload.log' -LimitSeconds 45

    $serial = [System.IO.Ports.SerialPort]::new($Port, 115200, 'None', 8, 'One')
    $serial.ReadTimeout = 500
    $serial.NewLine = "`n"
    $serial.Open()
    $serial.DtrEnable = $true
    Start-Sleep -Milliseconds 2000
    $deadline = [DateTime]::UtcNow.AddSeconds($TimeoutSeconds)
    $nextRequest = [DateTime]::MinValue
    $begun = $false; $completed = $false
    $results = [ordered]@{}
    while ([DateTime]::UtcNow -lt $deadline) {
        if (-not $begun -and [DateTime]::UtcNow -ge $nextRequest) {
            $serial.WriteLine("RUN $buildId")
            $nextRequest = [DateTime]::UtcNow.AddSeconds(1)
        }
        try { $line = $serial.ReadLine().Trim() }
        catch [System.TimeoutException] { continue }
        Add-Content (Join-Path $runRoot 'serial.log') $line
        Write-Host $line
        if ($line -eq "CPSTL_HW_BEGIN $buildId") {
            if ($begun) { throw 'Unexpected restart or duplicate run' }
            $begun = $true
        }
        elseif ($line -match '^CPSTL_HW_CASE (\w+) (PASS|FAIL)$') {
            if (-not $begun) { throw 'Case received before matching build ID' }
            $name = $Matches[1]; $outcome = $Matches[2]
            if ($name -notin $expected -or $results.Contains($name)) { throw "Unexpected or duplicate case: $name" }
            $results[$name] = $outcome
        }
        elseif ($line -match "^CPSTL_HW_END $buildId total=(\d+) passed=(\d+) failed=(\d+) assertions=(\d+)$") {
            $total = [int]$Matches[1]; $passed = [int]$Matches[2]
            $failed = [int]$Matches[3]; $assertions = [int]$Matches[4]
            $observedFailures = @($results.Values | Where-Object { $_ -eq 'FAIL' }).Count
            if (-not $begun -or $total -ne $expected.Count -or $results.Count -ne $total -or
                $failed -ne $observedFailures -or $passed + $failed -ne $total -or $assertions -le 0) {
                throw 'Incomplete or inconsistent hardware summary'
            }
            $completed = $true
            break
        }
    }
    if (-not $completed) { throw "Physical test timeout after $TimeoutSeconds seconds; no complete matching summary" }
    $metadata.results = @($results.GetEnumerator() | ForEach-Object { @{ name = $_.Key; outcome = $_.Value } })
    $metadata.assertions = $assertions
    $xml = [xml]'<testsuite />'
    $xml.DocumentElement.SetAttribute('name', 'CPSTL.ATmega2560')
    $xml.DocumentElement.SetAttribute('tests', "$total")
    $xml.DocumentElement.SetAttribute('failures', "$failed")
    foreach ($name in $expected) {
        $case = $xml.CreateElement('testcase')
        $case.SetAttribute('name', $name)
        if ($results[$name] -eq 'FAIL') {
            $failure = $xml.CreateElement('failure')
            $failure.SetAttribute('message', 'Physical test failed; see serial.log')
            [void]$case.AppendChild($failure)
        }
        [void]$xml.DocumentElement.AppendChild($case)
    }
    $xml.Save((Join-Path $runRoot 'junit.xml'))
    if ($failed -gt 0) { throw "$failed physical test(s) failed" }
    $metadata.status = 'PASS'
    Write-Host "PASS: $total physical cases, $assertions assertions ($Allocation allocation)."
}
catch {
    $metadata.status = 'FAIL'
    $metadata.error = $_.Exception.Message
    throw
}
finally {
    if ($serial) { $serial.Dispose() }
    $metadata.finishedUtc = [DateTime]::UtcNow.ToString('o')
    $metadata | ConvertTo-Json -Depth 8 | Set-Content (Join-Path $runRoot 'result.json')
}
