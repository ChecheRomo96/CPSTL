# CPSTL agent instructions

CPSTL (Cross-Platform STL) gives C++11 and newer code the `std` container and
utility interface (`cpstd::vector`, `cpstd::string`, `cpstd::function`, type
traits, iterators, algorithms) on targets with or without a C++ standard
library. With `CPSTL_USING_STL` every `cpstd` name aliases `std`; otherwise
CPSTL provides its own implementation.

## Scope

Do not modify Foundation, MCC, MIDILAR, RoModular, RoModularBuild, or another
sibling repository unless the user explicitly includes it.

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
- Preserve configuration selection through the `CPSTL_*` cache options
  (`CPSTL_USING_STL`, `CPSTL_ALLOCATION`, `CPSTL_VECTOR`, `CPSTL_STRING`,
  `CPSTL_STACK`, `CPSTL_QUEUE`, `CPSTL_CXX_STANDARD`) and their
  `src/CPSTL_UserSetup.h` equivalents for IDE builds.
- A change to a `cpstd` interface affects every RoModular library above it;
  report such a change to the user before making it.
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

AVR: `atmega328p_avrgcc_avr5` and `atmega2560_avrgcc_avr6` build the library and the `CPSTLAvrSmoke`
firmware (no tests or examples on AVR); run its `.hex` under simavr and look
for `CPSTL AVR smoke: PASS`. Public Arduino tutorials are grouped by module
under `examples/<module>/<tutorial_name>/`, alongside the matching desktop
entry point.

Run the smallest relevant validation first, then broaden it: the C, CPP and
STD allocation modes, `-DCPSTL_USING_STL=ON`, and C++11 through C++20 via
`-DCPSTL_CXX_STANDARD=`. State which hosts, compilers and embedded targets
were not available.
