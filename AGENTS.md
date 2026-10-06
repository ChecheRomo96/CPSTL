# CPSTL agent instructions

CPSTL (Cross-Platform STL) gives C++11 and newer code the `std` container and
utility interface (`cpstd::vector`, `cpstd::string`, `cpstd::function`, type
traits, iterators, algorithms) on targets with or without a C++ standard
library. With `CPSTL_USING_STL` every `cpstd` name aliases `std`; otherwise
CPSTL provides its own implementation.

## Shared RoModular guidance

Before starting work, look for the shared guidance in `../RoModularAgents`.

- If it exists and is readable, read `AGENTS.md` and `CONTRACT.md` completely.
- Read the CPSTL repository adapter under `repositories/` when one exists.
- If the sibling repository is unavailable, continue with the rules in this
  file and report that the shared guidance was not loaded.

Shared guidance does not expand the user's requested scope. Do not modify
Foundation, MCC, MIDILAR, RoModular, RoModularBuild, or another sibling
repository unless the user explicitly includes it.

## Repository rules

- Treat `CMakePresets.json`, its included preset files, and the scripts under
  `scripts/` as the supported build interface.
- Initialize the pinned `tools/RoModularBuild` submodule before invoking a
  workflow in a fresh checkout. Treat it as read-only; updating the gitlink is
  a separate, explicit dependency change.
- Keep the library C++11-compatible: Arduino cores compile it as C++11. The
  GoogleTest suites need C++17; `tests/HeaderCheck.cpp` and the examples cover
  the configured standard.
- Every public behaviour must hold in both modes. A test that only applies to
  the CPSTL implementation is guarded with `#if !defined(CPSTL_USING_STL)`.
- Without STL, containers never throw and never crash on allocation failure:
  the operation has no effect. Keep that contract when changing them.
- Use only freestanding C headers (`<stddef.h>`, `<stdint.h>`, `<limits.h>`,
  `<float.h>`, `<stdlib.h>`) outside STL mode; AVR-GCC has no C++ library.
- Keep public headers, examples, tests, `CHANGELOG.md`, and the version in
  `CMakeLists.txt`, `library.properties` and `src/CPSTL_BuildSettings.h`
  synchronized.
- Preserve unrelated work and do not commit, tag, push, publish, or merge
  unless the user explicitly requests it.

## Supported entry points

Use the PowerShell equivalent on Windows.

```text
./scripts/configure.sh <preset> [--fresh] [-- <cmake-options>]
./scripts/build.sh <preset> [--fresh] [--config <configuration>] [--examples-on]
./scripts/test.sh <preset> [--fresh] [--config <configuration>]
./scripts/install.sh <preset>
./scripts/clean.sh <preset> [--dist]
./scripts/test-arduino.sh [--fqbn <board>]... [-- <arduino-cli options>]   # Bash only
```

AVR: `atmega328p_avrgcc_avr5` builds the library and the `CPSTLAvrSmoke`
firmware (no tests or examples on AVR); run its `.hex` under simavr and look
for `CPSTL AVR smoke: PASS`. Arduino sketches live in `examples/arduino/`.

Run the smallest relevant validation first, then broaden it: the C, CPP and
STD allocation modes, `-DCPSTL_USING_STL=ON`, and C++11 through C++20 via
`-DCPSTL_CXX_STANDARD=`. State which hosts, compilers and embedded targets
were not available.
