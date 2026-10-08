$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
if (-not (Get-Command doxygen -ErrorAction SilentlyContinue)) { throw "doxygen not found" }
$output = Join-Path $root "build/documentation"
if (Test-Path -LiteralPath $output) { Remove-Item -LiteralPath $output -Recurse -Force }
New-Item -ItemType Directory -Force -Path $output | Out-Null
Push-Location $root
try { & doxygen "docs/Doxyfile"; if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE } }
finally { Pop-Location }
