#requires -Version 7.0
$ErrorActionPreference = "Stop"
$Root = Split-Path $PSScriptRoot -Parent
$Fixture = Join-Path ([IO.Path]::GetTempPath()) ("cpstl-native-report-" + [guid]::NewGuid())
New-Item -ItemType Directory -Path $Fixture | Out-Null
$Elf = Join-Path $Fixture "test.elf"
Set-Content -LiteralPath $Elf "Synthetic ELF for host decoder tests; never flashed."
$Metadata = Join-Path $Fixture "build.json"
[pscustomobject]@{elf=$Elf; sha256=(Get-FileHash $Elf).Hash; buildId="1234ABCD";
    address="0x20000000"; size=52; cases=@("First", "Second", "Third"); mode="C"} |
    ConvertTo-Json | Set-Content $Metadata
$FakeProgrammer = Join-Path $Fixture "programmer.ps1"
@'
Copy-Item -LiteralPath $env:CPSTL_NATIVE_FAKE_REPORT -Destination $args[-1] -Force
$global:LASTEXITCODE = 0
'@ | Set-Content $FakeProgrammer
$Previous = $env:CPSTL_NATIVE_FAKE_REPORT
$env:CPSTL_NATIVE_FAKE_REPORT = Join-Path $Fixture "source.bin"
try {
    foreach ($Scenario in @("pass", "failed-case", "stale-id", "incomplete", "bad-counters", "bad-outcome", "truncated", "all-zero")) {
        [uint32[]]$Words = @(0x4350534e, 0x1234ABCD, 2, 3, 3, 0, 8, 1, 1, 1, 0, 0, 0)
        switch ($Scenario) {
            "failed-case" { $Words[4]=2; $Words[5]=1; $Words[8]=2; $Words[11]=42 }
            "stale-id" { $Words[1]=0 }
            "incomplete" { $Words[2]=1 }
            "bad-counters" { $Words[4]=1 }
            "bad-outcome" { $Words[7]=0 }
            "truncated" { $Words = $Words[0..10] }
            "all-zero" { $Words = [uint32[]]::new(13) }
        }
        [byte[]]$Bytes = @($Words | ForEach-Object { [BitConverter]::GetBytes($_) })
        [IO.File]::WriteAllBytes($env:CPSTL_NATIVE_FAKE_REPORT, $Bytes)
        $Rejected = $false
        try { & "$Root/scripts/read-stm32-native.ps1" -Metadata $Metadata -Programmer $FakeProgrammer }
        catch { $Rejected = $true }
        if ($Rejected -ne ($Scenario -ne "pass")) { throw "Unexpected decoder result: $Scenario" }
        Write-Host "Verified native report decoder: $Scenario"
    }
    Add-Content -LiteralPath $Elf "ELF changed"
    $Rejected = $false
    try { & "$Root/scripts/read-stm32-native.ps1" -Metadata $Metadata -Programmer $FakeProgrammer }
    catch { $Rejected = $true }
    if (-not $Rejected) { throw "Changed ELF was accepted" }
    Write-Host "Verified native report decoder: changed ELF"
}
finally { $env:CPSTL_NATIVE_FAKE_REPORT = $Previous }
