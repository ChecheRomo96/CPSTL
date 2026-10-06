$script:CPSTLRoot = Split-Path -Parent $PSScriptRoot
$script:CPSTLBuildRoot = Join-Path $script:CPSTLRoot "build"
$script:CPSTLDistRoot = Join-Path $script:CPSTLRoot "dist"
$script:CPSTLRoModularScripts = Join-Path `
    $script:CPSTLRoot `
    "tools/RoModularBuild/scripts"

$roModularCommon = Join-Path $script:CPSTLRoModularScripts "common.ps1"
if (-not (Test-Path -LiteralPath $roModularCommon -PathType Leaf)) {
    throw "RoModularBuild is unavailable; initialize tools/RoModularBuild with git submodule update --init --recursive"
}

$env:ROMODULAR_PROJECT_ROOT = $script:CPSTLRoot
$env:ROMODULAR_BUILD_ROOT = $script:CPSTLBuildRoot
$env:ROMODULAR_DIST_ROOT = $script:CPSTLDistRoot
$env:ROMODULAR_PROJECT_LABEL = "CPSTL"
$env:ROMODULAR_CONFIGURE_COMMAND = "scripts/configure.ps1"
$env:ROMODULAR_DEFAULT_CONFIGURATION = "Debug"
$env:ROMODULAR_INSTALL_CONFIGURATION = "Release"
$env:ROMODULAR_TESTING_CACHE_ARGUMENT = "-DCPSTL_TESTING=ON"
$env:ROMODULAR_EXAMPLES_CACHE_ARGUMENT = "-DCPSTL_EXAMPLES=ON"
