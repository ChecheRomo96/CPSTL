#requires -Version 7.0
[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$ToolchainRoot,
    [ValidateSet("C", "CPP", "STD", "STL")][string]$Allocation = "C",
    [ValidateSet("Debug", "Release")][string]$Configuration = "Release",
    [switch]$InjectFailure,
    [switch]$Flash,
    [string]$Programmer = "",
    [ValidateRange(100, 4000)][int]$Frequency = 1000,
    [string]$ProbeSerial = ""
)
$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest
if ($Flash -and -not (Test-Path -LiteralPath $Programmer -PathType Leaf)) {
    throw "-Flash requires -Programmer pointing to STM32_Programmer_CLI.exe"
}
$ToolchainRoot = (Resolve-Path -LiteralPath $ToolchainRoot).Path
$Compiler = Join-Path $ToolchainRoot "bin/arm-none-eabi-g++.exe"
$Nm = Join-Path $ToolchainRoot "bin/arm-none-eabi-nm.exe"
if (-not (Test-Path -LiteralPath $Compiler) -or -not (Test-Path -LiteralPath $Nm)) {
    throw "ToolchainRoot must contain bin/arm-none-eabi-g++.exe and bin/arm-none-eabi-nm.exe"
}
$Root = Split-Path $PSScriptRoot -Parent
$Preset = "stm32g0b1cbt6_armgcc_cortex_m0plus_soft"
$Mode = $Allocation.ToUpperInvariant()
$Id = [guid]::NewGuid().ToString("N").Substring(0, 8).ToUpperInvariant()
$RunDirectory = Join-Path $Root "build/hardware/stm32-native/$Mode-$Id"
New-Item -ItemType Directory -Path $RunDirectory -Force | Out-Null
$Backend = if ($Mode -eq "STL") { "STD" } else { $Mode }
$Stl = if ($Mode -eq "STL") { "ON" } else { "OFF" }
$Injection = if ($InjectFailure) { "ON" } else { "OFF" }
$Options = @("-DROMODULAR_ARM_TOOLCHAIN_ROOT=$ToolchainRoot", "-DCPSTL_ALLOCATION=$Backend",
    "-DCPSTL_USING_STL=$Stl", "-DCPSTL_STM32_BUILD_ID=0x$Id", "-DCPSTL_STM32_INJECT_FAILURE=$Injection")
& "$PSScriptRoot/configure.ps1" $Preset -CMakeArguments $Options
& "$PSScriptRoot/build.ps1" $Preset -Configuration $Configuration -Parallel 4
$BuiltElf = Join-Path $Root "build/$Preset/bin/$Configuration/CPSTLStm32Native.elf"
foreach ($Extension in @("elf", "hex", "bin", "map")) {
    Copy-Item -LiteralPath ([IO.Path]::ChangeExtension($BuiltElf, $Extension)) -Destination $RunDirectory
}
$Elf = Join-Path $RunDirectory "CPSTLStm32Native.elf"
$Symbols = & $Nm --print-size $Elf
if ($LASTEXITCODE -ne 0) { throw "Cannot inspect the native firmware ELF" }
$Symbols | Set-Content -LiteralPath (Join-Path $RunDirectory "symbols.txt")
$Symbol = @($Symbols | Where-Object { $_ -match '^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+\w\s+cpstlNativeReport$' })
if ($Symbol.Count -ne 1) { throw "Missing or ambiguous cpstlNativeReport symbol" }
$null = $Symbol[0] -match '^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)'
$Address = "0x" + $Matches[1]
$Size = [Convert]::ToInt32($Matches[2], 16)
$Defines = @()
if ($Mode -eq "STL") { $Defines += "-DCPSTL_USING_STL" }
$Manifest = & $Compiler -E -P -x c++ @Defines (Join-Path $Root "tests/Arduino/CPSTLHardware/Cases.h")
if ($LASTEXITCODE -ne 0) { throw "Cannot preprocess the case manifest" }
$Cases = @($Manifest | ForEach-Object {
    if ($_ -match '^CPSTL_HW_CASE\((\w+)\)$') { $Matches[1] }
})
if ($Cases.Count -eq 0 -or $Size -ne (7 + 2 * $Cases.Count) * 4) { throw "Unexpected native report layout" }
$Metadata = Join-Path $RunDirectory "build.json"
[pscustomobject]@{buildId=$Id; mode=$Mode; injected=[bool]$InjectFailure; elf=$Elf;
    sha256=(Get-FileHash -LiteralPath $Elf -Algorithm SHA256).Hash; address=$Address; size=$Size;
    cases=$Cases} | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $Metadata
Write-Host "Native firmware ready: $Elf"
Write-Host "Expected cases: $($Cases.Count); metadata: $Metadata"
if ($Flash) {
    Write-Host "Flashing native firmware through SWD; this replaces the current application."
    & (Join-Path $Root "tools/RoModularBuild/scripts/stlink.ps1") -Action Flash `
        -Programmer $Programmer -File $Elf -Frequency $Frequency -ProbeSerial $ProbeSerial `
        -Log (Join-Path $RunDirectory "flash.log")
    Start-Sleep -Seconds 2
    & "$PSScriptRoot/read-stm32-native.ps1" -Metadata $Metadata -Programmer $Programmer `
        -Frequency $Frequency -ProbeSerial $ProbeSerial
}
