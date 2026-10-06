#!/bin/sh
set -eu

# Compiles every sketch under examples/arduino with arduino-cli, using the
# repository itself as the library (exactly what an Arduino user who copied it
# into their libraries folder gets) and the core's unmodified flags.
#
# Usage: scripts/test-arduino.sh [--fqbn <board>]... [-- <arduino-cli compile options>]
#
# Default boards: arduino:avr:uno and arduino:avr:mega. Any warning that points
# into CPSTL fails the run, because the stock AVR core passes -fpermissive,
# which turns some real errors into warnings.

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)

die() {
    printf 'error: %s\n' "$1" >&2
    exit 1
}

usage() {
    printf '%s\n' "Usage: $0 [--fqbn <board>]... [-- <arduino-cli compile options>]"
}

BOARDS=
while [ "$#" -gt 0 ]; do
    case "$1" in
        --fqbn)
            [ "$#" -ge 2 ] || die "--fqbn needs a board"
            BOARDS="$BOARDS $2"
            shift 2
            ;;
        --)
            shift
            break
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            die "unknown argument: $1"
            ;;
    esac
done
[ -n "$BOARDS" ] || BOARDS="arduino:avr:uno arduino:avr:mega"

command -v arduino-cli >/dev/null 2>&1 || die "arduino-cli not found"

COUNT=0
for FQBN in $BOARDS; do
    BUILD_ROOT="$ROOT/build/arduino/$(printf '%s' "$FQBN" | tr ':' '_')"
    rm -rf -- "$BUILD_ROOT"
    for SKETCH in "$ROOT"/examples/arduino/*/*.ino; do
        [ -f "$SKETCH" ] || die "no sketches under examples/arduino"
        SKETCH_DIR=$(dirname -- "$SKETCH")
        NAME=$(basename -- "$SKETCH_DIR")
        LOG="$BUILD_ROOT/$NAME.log"
        mkdir -p -- "$BUILD_ROOT"
        printf '%s\n' "== $NAME ($FQBN)"

        STATUS=0
        arduino-cli compile \
            --fqbn "$FQBN" \
            --library "$ROOT" \
            --build-path "$BUILD_ROOT/$NAME" \
            --warnings default \
            "$@" \
            "$SKETCH_DIR" >"$LOG" 2>&1 || STATUS=$?
        cat -- "$LOG"
        [ "$STATUS" -eq 0 ] || die "$NAME failed to compile for $FQBN"

        if grep -F "$ROOT/" "$LOG" | grep -q "warning:"; then
            die "$NAME compiled with CPSTL warnings for $FQBN"
        fi
        COUNT=$((COUNT + 1))
    done
done

printf '%s\n' "All $COUNT Arduino sketch builds passed ($BOARDS )."
