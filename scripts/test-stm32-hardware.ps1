[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$ArduinoCli,
    [Parameter(Mandatory)][string]$Programmer,
    [Parameter(Mandatory)][string]$Nm,
    [ValidateSet('C','CPP','STD','STL')][string]$Allocation = 'C',
    [switch]$InjectFailure
)
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$id = [Guid]::NewGuid().ToString('N').Substring(0,8).ToUpperInvariant()
$output = Join-Path $root "build/hardware/stm32/$Allocation-$id"
New-Item -ItemType Directory -Path $output -Force | Out-Null
function Invoke-Logged([string]$Exe, [string[]]$Arguments, [string]$Log) {
    @($Exe) + $Arguments | ConvertTo-Json | Set-Content "$Log.command.json"
    & $Exe @Arguments 2>&1 | Tee-Object -FilePath $Log | Out-Host
    if ($LASTEXITCODE -ne 0) { throw "Command failed ($LASTEXITCODE): $Exe; see $Log" }
}
$flags = "-DCPSTL_HW_BUILD_ID=0x${id}UL -DCPSTL_USING_${Allocation}_ALLOCATION"
if ($Allocation -eq 'STL') {
    $flags = "-DCPSTL_HW_BUILD_ID=0x${id}UL -DCPSTL_USING_STL -DCPSTL_USING_STD_ALLOCATION"
}
if ($InjectFailure) { $flags += ' -DCPSTL_HW_INJECT_FAILURE' }
Invoke-Logged $ArduinoCli @('compile','--fqbn','STMicroelectronics:stm32:GenG0:pnum=GENERIC_G0B1CBTX',
    '--warnings','default','--build-path',"$output/firmware",'--build-property',
    "compiler.cpp.extra_flags=$flags","$root/tests/Arduino/CPSTLHardware") "$output/compile.log"
$elf = "$output/firmware/CPSTLHardware.ino.elf"
$symbols = & $Nm --print-size $elf
if ($LASTEXITCODE -ne 0) { throw 'Cannot inspect ELF' }
$symbols | Set-Content "$output/symbols.txt"
$symbol = @($symbols | Where-Object { $_ -match '^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+\w\s+cpstlHardwareReport$' })
if ($symbol.Count -ne 1) { throw 'Missing or ambiguous report symbol' }
$null = $symbol[0] -match '^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)'
$address = '0x' + $Matches[1]
$size = [Convert]::ToInt32($Matches[2],16)
$compiler = Join-Path (Split-Path $Nm -Parent) 'arm-none-eabi-g++.exe'
$manifest = & $compiler -E -P -x c++ @($flags.Split(' ')) "$root/tests/Arduino/CPSTLHardware/Cases.h"
if ($LASTEXITCODE -ne 0) { throw 'Cannot preprocess case manifest' }
$manifest | Set-Content "$output/cases.txt"
$cases = @($manifest | ForEach-Object {
    if ($_ -match '^CPSTL_HW_CASE\((\w+)\)$') { $Matches[1] }
})
if ($cases.Count -eq 0 -or $size -ne (7+$cases.Count)*4) { throw 'Invalid report layout' }
& "$root/tools/RoModularBuild/scripts/stlink.ps1" -Action Flash -Programmer $Programmer -File $elf -Log "$output/flash.log"
Start-Sleep -Seconds 2
& "$root/tools/RoModularBuild/scripts/stlink.ps1" -Action Read -Programmer $Programmer -Address $address -Size $size -File "$output/report.bin" -Log "$output/read.log"
$bytes = [IO.File]::ReadAllBytes("$output/report.bin")
if ($bytes.Length -ne $size) { throw 'Truncated report' }
$words = @(0..(($size/4)-1) | ForEach-Object { [BitConverter]::ToUInt32($bytes,$_ * 4) })
if ($words[0] -ne 0x43505354 -or $words[1] -ne [Convert]::ToUInt32($id,16) -or
    $words[2] -ne 2 -or $words[3] -ne $cases.Count -or $words[6] -eq 0) { throw 'Incomplete or stale report' }
$results = @(for ($i=0; $i -lt $cases.Count; $i++) {
    if ($words[7+$i] -notin @(1,2)) { throw "Case $i not executed" }
    [pscustomobject]@{name=$cases[$i];passed=($words[7+$i] -eq 1)}
})
$failed = @($results | Where-Object { -not $_.passed }).Count
if ($words[5] -ne $failed -or $words[4] -ne ($cases.Count-$failed)) { throw 'Inconsistent report counts' }
[pscustomobject]@{buildId=$id;allocation=$Allocation;injected=[bool]$InjectFailure;
    address=$address;total=$words[3];passed=$words[4];failed=$failed;assertions=$words[6];cases=$results} |
    ConvertTo-Json -Depth 5 | Set-Content "$output/result.json"
$xml = [xml]'<testsuite/>'
$suite = $xml.DocumentElement
$suite.SetAttribute('name',"STM32-CPSTL-$Allocation")
$suite.SetAttribute('tests',"$($cases.Count)")
$suite.SetAttribute('failures',"$failed")
foreach ($result in $results) {
    $case = $xml.CreateElement('testcase'); $case.SetAttribute('name',$result.name)
    if (-not $result.passed) { $null = $case.AppendChild($xml.CreateElement('failure')) }
    $null = $suite.AppendChild($case)
}
$xml.Save("$output/junit.xml")
Write-Host "Report: $output/result.json; $($words[4]) passed, $failed failed, $($words[6]) assertions"
if ($failed) { exit 1 }
