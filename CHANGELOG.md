# Changelog

This file records user-visible changes to CPSTL. Release dates use the
`YYYY-MM-DD` format. No CPSTL version has been tagged yet; the unreleased
changes below are planned for 1.1.0, the version the sources already declare.

## [Unreleased]

Planned for 1.1.0, a rescue release: CPSTL builds, is tested in every
configuration it supports and uses the RoModularBuild workflow.

### Added

- `cpstd::stack` (`CPstack`) and `cpstd::queue` (`CPqueue`) container
  adapters with the `std` interface: `push`, `emplace`, `pop`, `top` or
  `front`/`back`, `empty`, `size`, `swap` and the comparison operators. In STL
  mode they are `std::stack` and `std::queue`. The CPSTL implementation has no
  `deque`, so both default to `cpstd::vector`; `queue::pop` uses the
  container's `pop_front` when it has one and otherwise erases the first
  element (O(n), keeping the capacity, so a reserved queue never allocates
  again). New cache options `CPSTL_STACK` and `CPSTL_QUEUE` (default `ON`),
  `CPSTL_STACK_ENABLED`/`CPSTL_QUEUE_ENABLED` in `CPSTL_UserSetup.h`, tests in
  `CPSTLAdapterTests`, and checks in the header check, the package consumer
  and the AVR smoke firmware.
- `LICENSE`: the proprietary all-rights-reserved notice used by the other
  RoModular repositories, installed with the package and referenced from the
  README.
- RoModularBuild v0.4.0 as the pinned `tools/RoModularBuild` submodule, native
  CMake presets for Linux, macOS and Windows, and the `configure`, `build`,
  `test`, `install` and `clean` scripts (Bash and PowerShell).
- CMake package export: `find_package(CPSTL)` provides `CPSTL::CPSTL` with the
  configuration it was built with as compile definitions.
- Cache options `CPSTL_TESTING`, `CPSTL_EXAMPLES`, `CPSTL_CXX_STANDARD`
  (11/14/17/20), `CPSTL_USING_STL`, `CPSTL_ALLOCATION` (C/CPP/STD),
  `CPSTL_VECTOR`, `CPSTL_STRING` and `CPSTL_UNICODE_STRINGS`.
- GoogleTest suites for every module: string (previously empty), vector growth,
  lifetimes, aliasing, allocation failure, algorithm, memory, functional,
  numeric limits, utility, exceptions and iterator functions, plus a C++11
  header check. 176 tests (165 in STL mode), run in C, C++ and STL allocation
  modes with GCC and Clang, C++11 to C++20, and under AddressSanitizer/UBSan.
- Self-checking examples for build configuration, vector, string, sorting and
  callbacks, run by CTest when testing is enabled.
- AVR support verified: preset `atmega328p_avrgcc_avr5` (bare AVR-GCC, C
  allocation) builds the library and `CPSTLAvrSmoke`, a self-checking firmware
  that reports PASS/FAIL over USART0 and runs under simavr (`CPSTL_AVR_SMOKE`).
  The `examples/arduino/BasicUsage` sketch compiles for Arduino Uno and Mega
  with `scripts/test-arduino.sh`, warning-free. Checked with avr-gcc 7.3 (the
  Arduino and Ubuntu toolchain) and 14.1.
- `embedded-ci.yml`: AVR build plus simavr run, and Arduino Uno/Mega sketch
  compilation.
- `cpstd::stoi`, `stol`, `stoul`, `stoll`, `stoull`, `stof`, `stod` and
  `stold` (declared before but never defined). Without STL they never throw.
- `cpstd::advance`, `next`, `prev`, `max`, `copy_backward`, `fill`, `equal`,
  `find`, and `basic_string` assignment operators.
- `numeric_limits` specializations for every character, integer and
  floating-point type (only `bool` existed, so `max()` returned 0).

### Changed

- `cpstd::vector` (CPSTL implementation) was rewritten on placement new:
  `push_back` grows geometrically (it reallocated on every call), elements no
  longer need a default constructor, and every operation is safe when its
  argument refers to an element of the vector.
- Allocation failure never crashes or throws: `cpstd::allocator` returns
  `nullptr` and vector and string leave themselves unchanged. An empty string
  no longer allocates.
- `cpstd::sort` is a heapsort: O(n log n) worst case and no recursion (the
  quicksort was O(n^2) and recursed deeply on sorted input); it also sorted only
  `int`-convertible values without a comparator.
- `CPSTL_BuildSettings.h` selects one allocation mode (C on AVR, C++ elsewhere,
  std in STL mode); the per-module `CPSTL_VECTOR_USING_*` and
  `CPSTL_STRING_USING_*` macros, which nothing read, were removed.
- `CPSTL_UserSetup.h` enables vector and string for every Arduino board.
- `cpstd::function` takes a signature in both modes (`function<int(int)>`); in
  STL mode it previously took separate return and argument types.
- `iterator_traits<T*>::value_type` drops cv-qualifiers, as in C++20.
- The CPSTL exception classes are a working `cpstd` hierarchy; containers do
  not throw. The `CPSTL_EXCEPTIONS`, `CPSTL_*_EXCEPTIONS`, `CPSTL_BUILD_TARGET`
  and per-module `*_TESTING`/`*_EXAMPLES` options were removed.

### Fixed

- Linux builds: two includes used the wrong case for `CPSTL_Iterator.h`.
- `is_base_of`, `is_convertible` and friends caused undefined-reference link
  errors before C++17; `is_nothrow_convertible` was always false and failed to
  compile for non-convertible types.
- `cpstd::swap` on arrays recursed forever; `iter_swap` did nothing in STL mode;
  the two-type `min` returned a dangling reference.
- `vector::rend()` returned a forward iterator; the friend `swap` did not
  compile with Clang; relational operators were not lexicographic; range
  `insert` overwrote the vector and returned nothing.
- `basic_string` had no copy assignment, so assigning one string to another
  freed the same buffer twice; integer arguments chose the iterator-range
  constructor; appending or inserting a string into itself read freed memory;
  `to_string` on negative floating-point values wrote through a null iterator.
- Variable templates (`is_arithmetic_v`, ...) were declared in C++11 builds.
- Test binaries were written into the source tree, so different builds
  overwrote each other's executables.

### Known limitations

- ESP32 and the other non-AVR Arduino targets were not compiled in this
  release cycle; the `AUnit_Tests` sketch still holds an older copy of the
  tests.
- `cpstd::function`, `unique_ptr` and `make_unique` allocate with plain
  `new`: bare AVR-GCC firmware must define `operator new`/`delete` (the
  Arduino core already does), and an allocation failure is not detected.
- `CPios.h` (`ios_base`) is an unfinished stub and is not part of `CPSTL.h`.
- `at()` does not check bounds in the CPSTL implementation.

## [1.0.0]

Initial version.
