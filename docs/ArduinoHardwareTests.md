# Automated physical tests: ATmega2560

This Windows PowerShell 7 runner builds a dedicated CPSTL contract suite with
Arduino CLI, flashes an Arduino Mega 2560 through its serial bootloader using
avrdude, and checks the actual board's serial test results. It does not burn a
bootloader, change fuses or use a simulator.

The runner described here targets the Mega. A separate STM32 Arduino candidate
uses the same cases and a report in RAM for ST-LINK-only connections; its
[execution status](STM32ArduinoValidation.md) is recorded separately and must
not be inferred from the successful AVR runs below.

## Requirements

- Arduino Mega 2560 connected over USB, identified by Arduino CLI.
- PowerShell 7 or newer.
- Arduino CLI on PATH or supplied using `-ArduinoCli`. The script also locates
  the CLI bundled with a WinGet-installed Arduino IDE.
- The `arduino:avr` platform installed in Arduino CLI's default data directory.
- The serial monitor closed so the test command can use the port.

## Run

From the CPSTL repository root:

```powershell
./scripts/test-hardware.ps1 -Port COM3
./scripts/test-hardware.ps1 -Port COM3 -Allocation CPP
```

Select the board's actual COM port. The target is explicitly
`arduino:avr:mega:cpu=atmega2560`; this first version does not support other
boards. The test replaces the application firmware currently on the board.

To use a CLI outside PATH:

```powershell
./scripts/test-hardware.ps1 -Port COM3 -ArduinoCli C:/tools/arduino-cli.exe
```

`-TimeoutSeconds 30` controls the serial test deadline. Compilation and upload
also have bounded deadlines (120 and 45 seconds respectively). Failure to
compile, upload, verify or receive a complete test run causes a nonzero script
exit. The script terminates its own subprocess tree if its deadline expires.

## What runs on the board

`tests/Arduino/CPSTLHardware/Cases.h` is the expected case manifest. The
firmware runs 23 cases covering:

- type traits and numeric limits against the AVR C headers, including 16-bit int;
- copy, fill, find, sort, iterator helpers, reverse iteration and back insertion;
- vector growth, insertion, erasure, copy/move and element lifetimes;
- strings, conversions, termination and mutation;
- stack and queue order;
- unique ownership, construction in raw memory, callable copy/move and utilities;
- controlled allocator failure and allocation size boundaries.

The firmware uses C++11 and the CPSTL implementation, with C allocation by
default. CPP selects the Arduino core's nothrow new/delete support. STD
allocation and STL mode cannot be tested on this AVR toolchain, which has no
C++ standard library.

This is a dedicated embedded contract suite, not the complete desktop
GoogleTest suite. It does not establish every desktop case, real system-wide
out-of-memory behavior, heap fragmentation endurance, stack high-water marks,
interrupt safety or timing guarantees. Simulated allocation failures use a
test allocator and check unchanged contents and outstanding allocation counts.

## Evidence and failure detection

Every invocation creates `build/hardware/atmega2560/<allocation>-<build-id>/`.
It records board identity/core/tool versions, source revision and dirty state,
the RoModularBuild revision, exact CLI argument arrays, compilation log,
firmware and SHA256, and the verbose avrdude command and verification log.

After upload, the host requests the freshly compiled build ID over serial at
115200 baud. It requires a matching BEGIN, one PASS/FAIL for every manifest
case, and a matching END with consistent counts and positive assertions.
Duplicate cases, unknown cases, missing results and timeouts cannot pass.

Complete runs produce `serial.log`, `junit.xml` and `result.json`. Runs that
fail earlier still produce `result.json` with the error; a missing JUnit
report is not a successful run.

To check that board-reported failures propagate to the host:

```powershell
pwsh -NoProfile -File scripts/test-hardware.ps1 -Port COM3 -InjectFailure
# Expected: first case FAIL, a complete summary with one failure, exit code 1.
# Afterwards restore and test the normal firmware:
./scripts/test-hardware.ps1 -Port COM3
```

The failure injection only changes the first case's reported verdict. It does
not intentionally damage memory or induce unsafe behavior.

## Execution record: 2026-10-15

Board detected on COM3: Arduino Mega 2560, USB VID/PID `2341:0042`.
Arduino CLI 1.5.1, Arduino AVR Boards 1.8.8, AVR-GCC 7.3.0,
avrdude 8.0-arduino.1. Avrdude read signature `1E 98 01` and verified
17,088 bytes of firmware in the initial normal run (`C-41D2617A`). The
physical board reported 23/23 cases passing and 131 assertions. Static globals
occupied 373 of 8,192 SRAM bytes; this is not a runtime peak-memory measurement.

The first runner revision then failed while generating JUnit; the XML element
handling was corrected. Two subsequent uploads of the failure-injection build
stalled during flash writes. Those invocations were failures, not test passes.
Bounded process timeouts were added, and the user reconnected USB before
retrying. The subsequent complete runs are recorded below. Local evidence
is under `build/hardware/atmega2560/`, including the failed invocations;
the cause of the earlier upload stalls was not established.

While awaiting USB recovery, CPP allocation compiled successfully without
flashing (`CPP-compile-only`): 17,090 bytes of flash and 373 bytes of static
globals. That invocation was compilation evidence only. Warnings seen in these builds
were unused parameters in the Arduino core's `new.cpp`; no CPSTL warnings
were observed.

### Completed after USB reconnection

| Run directory | Allocation | Physical cases | Assertions | Host result |
| --- | --- | --- | --- | --- |
| `C-17143F7A` | C, failure injection enabled | 22 PASS, 1 FAIL | 131 | Exit 1, expected rejection |
| `C-8E80B266` | C | 23 PASS, 0 FAIL | 131 | Exit 0 |
| `CPP-140D5BCB` | CPP | 23 PASS, 0 FAIL | 131 | Exit 0 |

Commands run from the CPSTL root:

```powershell
pwsh -NoProfile -File scripts/test-hardware.ps1 -Port COM3 -InjectFailure
# Observed exit code 1 and exactly one failed case, as expected.
./scripts/test-hardware.ps1 -Port COM3
./scripts/test-hardware.ps1 -Port COM3 -Allocation CPP
```

All three uploads completed with avrdude's flash verification. Normal C used
17,088 flash bytes and normal CPP used 17,090; both used 373 static SRAM bytes.
Each run produced serial logs, a JUnit report and JSON metadata with matching
build IDs. The negative JUnit contained 23 tests and one failure; both normal
reports contained 23 tests and zero failures. The last firmware left on the
board at the end of that sequence was the normal CPP variant, with failure
injection disabled. A later IDE-library check below replaced it with a tutorial.

This completes the dedicated 23-case physical contract suite in both supported
AVR allocation backends. It does not claim that all desktop GoogleTest cases
have been ported or executed on ATmega2560. RoModularBuild remained pinned at
`c905ef4fbddc39d5602a097387c175fe11832135`; no shared engine changes were made.

## Arduino IDE library compatibility — 2026-10-15

The user's objective was to establish that CPSTL works as a normal Arduino IDE
library, rather than testing the Arduino core's own GPIO/timer APIs or a bare
AVR build. No bare-AVR source or preset changes were retained.

Arduino IDE 2.3.10 is installed through WinGet. Its bundled Arduino CLI 1.5.1
was used with Arduino AVR Boards 1.8.8 and its stock C++11 flags. A standalone
copy of CPSTL 1.1.5 (`src`, `examples`, metadata and documents) was installed at
`C:/Users/jromo/Documents/Arduino/libraries/CPSTL`. There was no existing CPSTL
installation to overwrite. Arduino CLI enumerated it as a user library and
discovered its example sketches.

All **20 public tutorials** compiled successfully for
`arduino:avr:mega:cpu=atmega2560`, using their installed example directories.
No `--library` argument or include path into this Git checkout was supplied.
The historical `AUnit_Tests` sketch is not a public tutorial and was excluded;
this check does not establish compatibility of that legacy sketch.

The executed compilation sequence was equivalent to:

```powershell
$cli = "$env:LOCALAPPDATA/Microsoft/WinGet/Packages/ArduinoSA.IDE.stable_Microsoft.Winget.Source_8wekyb3d8bbwe/resources/app/lib/backend/resources/arduino-cli.exe"
$library = "$env:USERPROFILE/Documents/Arduino/libraries/CPSTL"
$evidence = Join-Path (Get-Location) 'build/validation/arduino-ide'
foreach ($sketch in Get-ChildItem "$library/examples" -Filter *.ino -Recurse) {
    if (-not (Test-Path (Join-Path $sketch.DirectoryName 'CMakeLists.txt'))) { continue }
    & $cli compile --fqbn arduino:avr:mega:cpu=atmega2560 `
        --build-path "$evidence/$($sketch.BaseName)/firmware" `
        --warnings default $sketch.DirectoryName
}
```

The installed `telemetry_log` example was uploaded and verified:

```powershell
& $cli upload --fqbn arduino:avr:mega:cpu=atmega2560 --port COM3 `
    --build-path "$evidence/telemetry_log/firmware" --verify --verbose `
    "$library/examples/vector/telemetry_log"
```

The physical Mega's serial output at 9600 baud contained all seven expected
lines, checked using ordinal string equality after removing leading NUL bytes
from boot/reset noise. The raw serial log was retained:

```text
Capacity reserved before capture: 4
Captured 420
Captured 427
Captured 434
Captured 441
Recorded 4 samples without growing storage during capture.
If a burst can exceed this budget, reserve more before sampling.
```

Compiler dependency files were checked: they reference the installed library's
headers and do not reference the original checkout's `src` directory.
Results, per-tutorial logs, library discovery, upload verification and raw
serial output are in `build/validation/arduino-ide/`, with `summary.json`.

This validates the installed IDE's compilation/upload backend and the physical
application. No GUI interaction, menu rendering or IDE button operation was
performed. For the GUI workflow, open the installed `telemetry_log.ino` in
Arduino IDE, select Arduino Mega or Mega 2560 / ATmega2560 / COM3, and open
Serial Monitor at 115200 baud for the current tutorial (the recorded firmware
used 9600 baud). Reset the board to repeat the output. The board
is now left running that tutorial, and the installed library copy remains
available in the user's sketchbook.
