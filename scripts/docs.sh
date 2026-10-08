#!/bin/sh
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
command -v doxygen >/dev/null 2>&1 || { echo "error: doxygen not found" >&2; exit 1; }
rm -rf "$ROOT/build/documentation"
mkdir -p "$ROOT/build/documentation"
(cd "$ROOT" && doxygen docs/Doxyfile)
