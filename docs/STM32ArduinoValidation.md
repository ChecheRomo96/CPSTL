# STM32G0B1CBT6 with Arduino: physical validation

## Objective and firmware

Validate CPSTL as an installed Arduino IDE library on STM32G0B1CBT6. The
firmware under test is an Arduino application using CPSTL, not a replacement
bootloader, Arduino-core conformance suite or bare-metal CMake application.

The public tutorials exercise documented application workflows. The separate
`tests/Arduino/CPSTLHardware` firmware runs 23 CPSTL contract cases. The desktop
GoogleTest suite has not been ported in full to this microcontroller.

## Compilation evidence — 2026-10-15

- Arduino IDE backend: bundled Arduino CLI 1.5.1, IDE 2.3.10.
- Core: STMicroelectronics STM32 3.0.0.
- Compiler: xPack GNU Arm Embedded GCC 14.2.1, build 20241119.
- Exact FQBN: `STMicroelectronics:stm32:GenG0:pnum=GENERIC_G0B1CBTX`.
- CPSTL: 1.1.5, implementation mode, C allocation.
- RoModularBuild remains pinned at
  `c905ef4fbddc39d5602a097387c175fe11832135`; no shared tool changes.

All 20 public tutorials compiled from the installed sketchbook library at
`C:/Users/jromo/Documents/Arduino/libraries/CPSTL`, without `--library` or a
source include path into this checkout. The legacy `AUnit_Tests` example was
excluded as in the AVR tutorial validation. Logs and per-tutorial exit codes
are under `build/validation/stm32-arduino/`.

The baseline builds emitted an architecture-metadata warning: `stm32` was
missing from CPSTL's `library.properties`. That architecture was added to the
repository and the previously installed library copy. The subsequent suite
build no longer emits that warning. This change does not establish physical
execution by itself.

```powershell
# Use the arduino-cli executable bundled with the installed Arduino IDE.
$fqbn = 'STMicroelectronics:stm32:GenG0:pnum=GENERIC_G0B1CBTX'
& $cli compile --fqbn $fqbn --warnings default `
    --build-path build/validation/stm32-arduino/suite-swd/firmware `
    --build-property 'compiler.cpp.extra_flags=-DCPSTL_HW_BUILD_ID=0x474F4231UL -DCPSTL_USING_C_ALLOCATION' `
    tests/Arduino/CPSTLHardware
```

The SWD-capable suite compiled successfully: 26,536 flash bytes and 1,588
static SRAM bytes. These are build sizes, not runtime peak-memory measurements.
The ATmega2560 branch was also recompiled after the transport refactor and
still occupies 17,088 flash bytes and 373 static SRAM bytes. It was not
reflashed during this STM32 work.

## Results without a serial adapter

The user has only ST-LINK. On STM32 the suite therefore runs automatically
from Arduino `setup()` and stores a volatile report in SRAM. Arduino core
startup, allocation/runtime support and library configuration remain in use.
The AVR branch retains its serial-command-triggered behavior.

The `cpstlHardwareReport` symbol holds 30 little-endian 32-bit words:

| Word | Meaning |
| --- | --- |
| 0 | Magic `0x43505354` |
| 1 | Build ID, `0x474F4231` for the current candidate |
| 2 | State: 0 not started, 1 running, 2 all cases completed |
| 3–6 | Total, passed, failed, assertions |
| 7–29 | One outcome per `Cases.h` entry: 0 not executed, 1 PASS, 2 FAIL |

The current ELF places the 120-byte symbol at `0x20000178`; its address must
be obtained from each actual ELF, not assumed for a future build. Physical
passes below include flash verification, a completed report with matching build
ID, all 23 case outcomes, consistent counts and positive assertions.


## Physical execution and installation

STM32CubeIDE 2.2.0 was downloaded from the authenticated official ST portal
and installed at `C:/ST/STM32CubeIDE_2.2.0/STM32CubeIDE`. The installer had a
valid STMicroelectronics Authenticode signature. Its ST-LINK driver now reports
Windows device status OK. CubeIDE's bundled STM32CubeProgrammer is 2.23.0.
The IDE GUI itself was not exercised.

SWD identified device ID 0x467, revision Z, Cortex-M0+, 128 KB flash, supply
3.25 V, ST-LINK firmware V2J45S7. Requested SWD 1000 kHz negotiated 950 kHz.
Before programming, the original 131072 flash bytes were backed up to
`build/validation/stm32-arduino/original-flash.bin`. No option bytes,
protection settings or probe firmware were changed.

The repeatable host entry point is `scripts/test-stm32-hardware.ps1`:

```powershell
$cli = "$env:LOCALAPPDATA/Microsoft/WinGet/Packages/ArduinoSA.IDE.stable_Microsoft.Winget.Source_8wekyb3d8bbwe/resources/app/lib/backend/resources/arduino-cli.exe"
$p = Get-ChildItem C:/ST/STM32CubeIDE_2.2.0 -Filter STM32_Programmer_CLI.exe -Recurse |
    Select-Object -First 1 -ExpandProperty FullName
$nm = "$env:LOCALAPPDATA/Arduino15/packages/STMicroelectronics/tools/xpack-arm-none-eabi-gcc/14.2.1-1.1/bin/arm-none-eabi-nm.exe"
./scripts/test-stm32-hardware.ps1 -ArduinoCli $cli -Programmer $p -Nm $nm -Allocation C
./scripts/test-stm32-hardware.ps1 -ArduinoCli $cli -Programmer $p -Nm $nm -Allocation CPP
./scripts/test-stm32-hardware.ps1 -ArduinoCli $cli -Programmer $p -Nm $nm -Allocation STD
./scripts/test-stm32-hardware.ps1 -ArduinoCli $cli -Programmer $p -Nm $nm -Allocation STL
# Expected exit code 1, one deliberately failed case:
./scripts/test-stm32-hardware.ps1 -ArduinoCli $cli -Programmer $p -Nm $nm -Allocation C -InjectFailure
```

Each invocation compiles a new build ID, obtains the SRAM symbol address and
size from its actual ELF, flashes with verification, resets, waits two seconds,
and reads the report using HOTPLUG so the read does not reset the application.
It rejects stale IDs, incomplete/empty suites, missing outcomes and inconsistent
counts. A failed case gives exit code 1. Transport/build errors also fail.
The underlying programmer commands are:

```powershell
& $p -c port=SWD freq=1000 -w $elf -v -rst
& $p -c port=SWD freq=1000 mode=HOTPLUG -u $address $size $reportFile
```

Per-run directories under `build/hardware/stm32/` contain exact command arrays,
compile/flash/read logs, ELF symbol listings, raw SRAM bytes, `result.json`
and per-case `junit.xml`. These are local execution artifacts, not committed.

Confirmed executions:

| Build ID | Allocation | Passed / failed | Assertions | Host exit |
| --- | --- | --- | --- | --- |
| 474F4231 | C, initial manual run | 23 / 0 | 131 | 0 |
| FA06F5BD | C, injected failure | 22 / 1 | 131 | 1, expected |
| 3E4C5C61 | CPP | 23 / 0 | 131 | 0 |
| 1544CB1C | C, repeatable script | 23 / 0 | 131 | 0 |
| 61420837 | STD allocation, CPSTL containers | 23 / 0 | 129 | 0 |
| 61B92E52 | STL aliases | 20 / 0 | 122 | 0 |

STD uses the standard allocator and therefore does not assert CPSTL's null
return behavior for zero/oversized allocations. STL excludes the three
CPSTL-specific no-effect-on-allocation-failure cases. It also avoids empty
adapter pops and invalid numeric input, and treats `shrink_to_fit` as a
non-binding request. These operations have different standard-library
contracts. The remaining cases execute real checks; exclusions are not
counted as passes. The host preprocesses `Cases.h` with the selected mode
to obtain the actual case manifest before validating the SRAM layout.

STD used 26,320 flash bytes / 1,588 static SRAM bytes; STL used 27,572 / 1,564.
Both images were flash-verified and returned their matching unique build ID,
completed state and per-case outcomes from physical SRAM over SWD. The board
currently contains the passing STL image. No CPSTL library implementation
changes were needed to support these two modes.

These are results with the local Arduino test harness and metadata changes,
while the RoModularBuild pin remains unchanged. They validate CPSTL contracts
on the physical STM32 using the installed Arduino core and IDE backend.
They do not claim execution of the complete desktop GoogleTest suite,
Arduino IDE GUI upload buttons, or CPSTL embedded CMake presets.
