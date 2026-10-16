# Native STM32G0B1CBT6 validation

This firmware uses CMake, GNU Arm Embedded and ST-LINK/SWD. It does not use
Arduino, STM32 HAL, UART, semihosting or an RTOS. Startup, linker template,
bounded runtime, firmware artifact conversion and ST-LINK transport come from
the pinned RoModularBuild `v0.5.1`. CPSTL owns only the assertions, report
protocol, target configuration and test orchestration. The assertions are reused
from the existing hardware fixture; their header location under
`tests/Arduino/CPSTLHardware` does not introduce an Arduino-core dependency.

The [STM32G0B1CB product documentation](https://www.st.com/en/microcontrollers-microprocessors/stm32g0b1cb.html)
specifies 128 KiB flash and 144 KiB SRAM. This fixture uses only the normal
128 KiB SRAM region and does not modify parity or other option bytes. Its
linker reserves a 16 KiB newlib heap and at least 8 KiB for the stack. Startup
copies data, clears BSS, initializes C++ globals and runs the cases with
interrupts disabled, using the reset clock configuration.
After completion or a fault it stays in an active loop rather than WFI, so
a new HOTPLUG session can read the report after the programming session closes.

## Commands on this Windows host

Use PowerShell 7. CMake, Ninja and STM32CubeIDE's GNU Arm tools must be
installed. The shared build submodule remains at its checked-in revision.

```powershell
Set-Location F:\Dev\RoModular\CPSTL

$gcc = Get-ChildItem C:\ST -Recurse -Filter arm-none-eabi-g++.exe |
    Select-Object -First 1 -ExpandProperty FullName
$toolchain = Split-Path (Split-Path $gcc -Parent) -Parent
$programmer = Get-ChildItem C:\ST -Recurse -Filter STM32_Programmer_CLI.exe |
    Select-Object -First 1 -ExpandProperty FullName

# Compile only; does not connect to or change the target.
.\scripts\test-stm32-native.ps1 -ToolchainRoot $toolchain -Allocation C

# Compile, overwrite the current application, verify flash, reset, then read SRAM.
.\scripts\test-stm32-native.ps1 -ToolchainRoot $toolchain `
    -Programmer $programmer -Allocation C -Flash
```

Use `-Allocation CPP`, `STD` or `STL` for the other modes. The native CMake
preset is `stm32g0b1cbt6_armgcc_cortex_m0plus_soft`; the runner delegates to
the existing public configure/build adapters. `-Configuration Debug` selects
the debug build; Release is the default. `-ProbeSerial` selects a probe when
more than one is present; `-Frequency 100` lowers SWD speed if needed.

Each run creates a unique directory under `build/hardware/stm32-native/`,
with its ELF, HEX, BIN, map, symbol list and `build.json`. The ELF report
address and size are discovered from that ELF, not hardcoded. The metadata
contains its SHA256, build ID and actual preprocessed case manifest.

## Reading the result

After `-Flash`, each case prints PASS or FAIL and a summary reports actual
case and assertion counts. C/CPP/STD have 23 cases; STL has 20. STD skips
nonstandard allocator boundary contracts, and STL excludes CPSTL-specific
allocation-failure cases. No excluded case is counted as a pass.

The raw SRAM report, per-case results and logs remain in that run directory.
To read it again without reflashing, supply the printed metadata path:

```powershell
.\scripts\read-stm32-native.ps1 `
    -Metadata 'build\hardware\stm32-native\C-<build-id>\build.json' `
    -Programmer $programmer
```

The reader checks the ELF hash, native report magic, build ID, completed
state, exact layout, case outcomes, nonzero assertions and consistent totals.
It rejects a stale image, partial execution, fault state or failed case.
`-InjectFailure -Flash` intentionally fails the first case to exercise the
negative path; afterwards re-run without that option to restore a normal
image. A failed case causes the PowerShell script to fail.

## Validation performed

On 2026-10-15, compiled C/CPP/STD/STL and an injected-failure image using
STM32CubeIDE's ARM GCC 14.3.1 with the pinned RoModularBuild toolchain.
The final C image uses 9748 flash bytes; reserved/static RAM is 25232 bytes,
including the 16 KiB heap and 8 KiB stack reservation, not peak heap usage.
Checked the reader with synthetic success, failed-case, stale-ID, incomplete,
inconsistent-count, invalid-outcome, truncated-report and changed-ELF inputs.
Both existing Arduino hardware fixtures still compile (Mega and STM32G0B1).

The user subsequently executed the native images on the physical
STM32G0B1CBT6 with ST-LINK, flash verification and matching SRAM build IDs:

| Run | Mode | Passed / total | Failed | Assertions |
| --- | --- | --- | --- | --- |
| `C-4520150C` | C | 23 / 23 | 0 | 131 |
| `CPP-03F67EA5` | CPP | 23 / 23 | 0 | 131 |
| `STD-33D1DDCC` | STD | 23 / 23 | 0 | 129 |
| `STL-17A8C60C` | STL | 20 / 20 | 0 | 122 |
| `C-C8AB925D` | C, injected failure | 22 / 23 | 1 | 131 |
| `C-12D358E1` | C, restored normal image | 23 / 23 | 0 | 131 |

The injected failure was `TypeTraits`; the reader saved the result and threw
an error. The final normal C run restored a passing image. The local raw
reports and JSON files were inspected when recording this table.

The first user flash (`C-CB42A7E3`) programmed and verified successfully, but
the subsequent HOTPLUG read returned an all-zero SRAM report and device
identification errors. Its firmware ended in WFI. The active-loop revision
removes that dependency on sleep/debug behavior; the successful runs above
used that revision.
See [ST's STM32G0 debug behavior discussion](https://community.st.com/stm32-mcus-products-25/stm32g0-changes-dbgmcu-behaviour-63861)
for context; the zero report alone does not establish which stage failed.

## CI

The board-support extraction into RoModularBuild was compiled independently
and with CPSTL in all four modes. The physical results above precede that
extraction; repeat the same user commands to collect evidence for the shared
runtime revision. This refactor did not flash or reset the user's board.

`.github/workflows/stm32-native-ci.yml` runs on main-branch push/PR and manual
dispatch. Ubuntu installs GNU Arm, newlib and the embedded C++ libraries,
then compiles and links Debug/Release images for C, CPP, STD, STL and a C
image with an injected failure. A separate job tests the report decoder with
synthetic transport. These jobs do not execute firmware on an STM32 and do
not claim physical passes; the injected image is compiled, not run, there.

`.github/workflows/stm32-hardware.yml` is manual-only. To enable physical CI:

1. Register a dedicated Windows x64 self-hosted GitHub Actions runner with
   the custom label `stm32g0b1`; connect the STM32G0B1CBT6 and ST-LINK.
2. Install PowerShell 7, Git, CMake, Ninja, GNU Arm Embedded and
   STM32CubeProgrammer on that runner.
3. Create the GitHub environment `stm32-hardware`. Add its variables
   `STM32_TOOLCHAIN_ROOT` (directory containing the compiler's `bin` folder)
   and `STM32_PROGRAMMER` (full programmer executable path).
   Optionally set `STM32_PROBE_SERIAL` to choose a particular probe.
4. Restrict that environment to trusted refs and require review if desired;
   use this dedicated runner only for trusted hardware workflows, not PR jobs.
5. Dispatch **STM32 Physical Contract Tests (Manual)** from Actions.

The physical workflow serializes access to the board, executes all four
modes, verifies that the deliberate `TypeTraits` failure really caused the
error (rather than accepting a transport error), and attempts to restore
passing C firmware in a `finally` block. It uploads ELF files and actual
per-run SRAM/JSON/log results, including the restoration run. Dispatching it
replaces the board's current application.

Runner registration and GitHub environment setup have not been performed by
these repository changes. The manual job needs that setup before it can run.
