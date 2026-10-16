#requires -Version 7.0
[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$Metadata,
    [Parameter(Mandatory)][string]$Programmer,
    [ValidateRange(100, 4000)][int]$Frequency = 1000,
    [string]$ProbeSerial = ""
)
$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest
$Metadata = (Resolve-Path -LiteralPath $Metadata).Path
$RunDirectory = Split-Path $Metadata -Parent
$Build = Get-Content -LiteralPath $Metadata -Raw | ConvertFrom-Json
if ((Get-FileHash -LiteralPath $Build.elf -Algorithm SHA256).Hash -ne $Build.sha256) {
    throw "The ELF changed after this metadata was produced; rebuild before reading"
}
$ReportFile = Join-Path $RunDirectory "report.bin"
if (Test-Path -LiteralPath $ReportFile) { Remove-Item -LiteralPath $ReportFile }
$Transport = Join-Path (Split-Path $PSScriptRoot -Parent) "tools/RoModularBuild/scripts/stlink.ps1"
& $Transport -Action Read -Programmer $Programmer -Address $Build.address -Size $Build.size `
    -File $ReportFile -Frequency $Frequency -ProbeSerial $ProbeSerial -Log (Join-Path $RunDirectory "read.log")
$Bytes = [IO.File]::ReadAllBytes($ReportFile)
$Count = $Build.cases.Count
if ($Bytes.Length -ne (7 + 2 * $Count) * 4) { throw "Unexpected report size" }
$Words = @(0..(($Bytes.Length / 4) - 1) | ForEach-Object { [BitConverter]::ToUInt32($Bytes, $_ * 4) })
if (@($Words | Where-Object { $_ -ne 0 }).Count -eq 0) {
    throw "SRAM report is all zeros: firmware has not initialized the report, or SWD cannot read it. Rebuild/reflash the active-loop firmware and retry."
}
if ($Words[0] -ne 0x4350534e -or $Words[1] -ne [Convert]::ToUInt32($Build.buildId, 16)) {
    throw ("Report does not match this firmware: magic=0x{0:X8}, ID=0x{1:X8}, expected ID=0x{2}. Check the flashed ELF." -f $Words[0], $Words[1], $Build.buildId)
}
if ($Words[2] -ne 2) { throw "Firmware did not finish: state=$($Words[2]) (1=running, 3=fault)" }
if ($Words[3] -ne $Count -or $Words[6] -eq 0) { throw "Incomplete or empty test suite" }
$Results = @(for ($i = 0; $i -lt $Count; $i++) {
    if ($Words[7 + $i] -notin @(1, 2)) { throw "Case $i has no valid outcome" }
    $Passed = $Words[7 + $i] -eq 1
    $Line = $Words[7 + $Count + $i]
    [pscustomobject]@{name=$Build.cases[$i]; passed=$Passed; failureLine=$Line}
})
$Failed = @($Results | Where-Object { -not $_.passed }).Count
if ($Words[5] -ne $Failed -or $Words[4] -ne $Count - $Failed) { throw "Inconsistent report counters" }
foreach ($Result in $Results) {
    $Label = if ($Result.passed) { "PASS" } else { "FAIL" }
    Write-Host "$Label $($Result.name)$(if ($Result.failureLine) { " (assertion line $($Result.failureLine))" })"
}
[pscustomobject]@{buildId=$Build.buildId; mode=$Build.mode; total=$Count; passed=$Words[4];
    failed=$Failed; assertions=$Words[6]; cases=$Results} | ConvertTo-Json -Depth 5 |
    Set-Content -LiteralPath (Join-Path $RunDirectory "result.json")
Write-Host "Native STM32: $($Words[4])/$Count passed, $Failed failed, $($Words[6]) assertions"
Write-Host "Results: $RunDirectory"
if ($Failed) { throw "$Failed native STM32 test case(s) failed" }
