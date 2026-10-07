# CPSTL: Cross-Platform STL

CPSTL gives C++11 and newer code the familiar `std` interface on targets with
or without a C++ standard library. Code written against `cpstd::vector`,
`cpstd::string`, `cpstd::function`, `cpstd::sort` or `cpstd::is_same` builds
unchanged on a desktop and on an 8-bit AVR.

- **STL mode** (`CPSTL_USING_STL`): every `cpstd` name is an alias of its `std`
  counterpart, at no cost.
- **CPSTL implementation** (default): CPSTL provides the facilities itself,
  using only freestanding C headers. Containers never throw: when memory runs
  out the operation has no effect and the container stays as it was.

## Modules

| Header | Contents |
| --- | --- |
| `CPvector` | `cpstd::vector` |
| `CPstring` | `cpstd::basic_string`, `string`, `to_string`, `stoi` and the other conversions |
| `CPstack` | `cpstd::stack` (LIFO adapter, default container `cpstd::vector`) |
| `CPqueue` | `cpstd::queue` (FIFO adapter, default container `cpstd::vector`) |
| `CPalgorithm` | `min`, `max`, `copy`, `copy_backward`, `fill`, `equal`, `find`, `iter_swap`, `sort` |
| `CPfunctional.h` | `cpstd::function` |
| `CPmemory.h` | `allocator`, `unique_ptr`, `make_unique`, `uninitialized_copy`, `uninitialized_move` |
| `CPiterator.h` | iterator tags and traits, `begin`, `end`, `distance`, `advance`, `next`, `prev`, `reverse_iterator`, `back_inserter` |
| `CPtype_traits` | type categories, properties and relationships |
| `CPutility` | `move`, `forward`, `swap`, `exchange` |
| `CPlimits.h` | `numeric_limits` for every arithmetic type |
| `CPexception` | `exception`, `logic_error`, `out_of_range`, `length_error`, `bad_alloc` |
| `CPinitializer_list` | `initializer_list` |
| `CPSTL.h` | everything above that is enabled |

## Configuration

CMake builds set these cache options; Arduino and PSoC Creator builds edit
`src/CPSTL_UserSetup.h` instead.

| Option | Default | Meaning |
| --- | --- | --- |
| `CPSTL_USING_STL` | `OFF` | Alias every `cpstd` name to `std` (hosted targets only) |
| `CPSTL_ALLOCATION` | `C` | `C` (`malloc`/`free`, works without `operator new`), `CPP` (`operator new(nothrow)`) or `STD` (`std::allocator`) |
| `CPSTL_VECTOR` / `CPSTL_STRING` | `ON` | Include the container in `CPSTL.h` |
| `CPSTL_STACK` / `CPSTL_QUEUE` | `ON` | Include the adapter in `CPSTL.h` |
| `CPSTL_UNICODE_STRINGS` | `OFF` | Declare `u16string` and `u32string` |
| `CPSTL_CXX_STANDARD` | `11` | Language level: 11, 14, 17 or 20 |
| `CPSTL_TESTING` / `CPSTL_EXAMPLES` | `OFF` | Build the tests and the examples |

Without CMake, CPSTL uses C allocation. Select `CPSTL_USING_CPP_ALLOCATION`
explicitly only where a C++ allocation runtime is available.

## Stack and queue

In STL mode `cpstd::stack` and `cpstd::queue` are `std::stack` and
`std::queue`, with `std::deque` as the default container. The CPSTL
implementation has no `deque` or `list`, so both adapters default to
`cpstd::vector`:

- `stack` pushes and pops at the back of the vector: O(1) amortized.
- `queue::pop` uses the container's `pop_front` when it has one and otherwise
  erases the first element, which is O(n) in the queue's length. The elements
  stay contiguous and `pop` keeps the capacity, so a queue whose container was
  reserved beforehand never allocates again. For long queues pass a container
  with a constant-time `pop_front`.

Write portable code against the common interface: name the container type
through `container_type` instead of assuming the default, do not use the
return value of `emplace` (`void` here and in C++11), and do not pop an empty
adapter (it has no effect in CPSTL and is undefined in std). The
allocator-extended constructors are not provided.

`push` and `emplace` may allocate; in the CPSTL implementation a failure
leaves the adapter unchanged, so check `size()`. For time-critical code reserve the storage first and pass it
to the constructor. A stack over an explicit `cpstd::vector` does this in both
modes; the default queue does it in the CPSTL implementation (`std::queue`
cannot use a vector, which has no `pop_front`):

```cpp
cpstd::vector<int> storage;
storage.reserve(16);
cpstd::stack<int, cpstd::vector<int> > undo(cpstd::move(storage));  // no allocation up to 16
```

## Build and test

CPSTL uses the shared [RoModularBuild](https://github.com/ChecheRomo96/RoModularBuild)
workflow, pinned as a submodule:

```sh
git submodule update --init --recursive
./scripts/test.sh linux_gcc_x64          # or macos_arm64, windows_msvc_x64, ...
./scripts/build.sh macos_arm64 --examples-on
./scripts/install.sh macos_arm64         # Release package in dist/macos_arm64
```

For AVR, `./scripts/build.sh atmega328p_avrgcc_avr5` cross-compiles the
library and a self-checking ATmega328P firmware with the bare AVR-GCC
toolchain, and `./scripts/test-arduino.sh` compiles the Arduino sketches with
`arduino-cli` for the Uno, Mega and ESP32. The physical verification matrix is
AVR, ESP32 and STM32G0B1; see [HardwareVerification.md](docs/HardwareVerification.md).

On Windows use the matching `.ps1` scripts. List the presets with
`cmake --list-presets`. To test another configuration, pass cache options to
the configure step, for example
`./scripts/configure.sh linux_gcc_x64 --fresh -- -DCPSTL_USING_STL=ON`.

## Use from CMake

```cmake
find_package(CPSTL 1.1.4 CONFIG REQUIRED)
target_link_libraries(app PRIVATE CPSTL::CPSTL)
```

The package carries the configuration it was built with as compile
definitions, so consumers see the same `cpstd` types.

## Use from Arduino

Install the repository as a library and include `<CPSTL.h>`; see
`examples/arduino/BasicUsage`. Pick the configuration in
`src/CPSTL_UserSetup.h`. On AVR boards containers allocate with `malloc`;
`cpstd::function` and `unique_ptr` use the core's `operator new`.

## Status

See [CHANGELOG.md](CHANGELOG.md). The 1.1.4 candidate is validated on Linux
(GCC, Clang), macOS (Apple Clang), AVR (ATmega328P under simavr, Arduino Uno
and Mega) and ESP32 compilation. Hardware execution remains a separate,
recorded gate for AVR, ESP32 and STM32G0B1.

## License

Copyright (c) 2026 José Manuel Romo. All rights reserved.

CPSTL is currently proprietary. No permission is granted for external use,
compilation, modification, redistribution, integration, or commercial use
without prior written authorization. See [LICENSE](LICENSE).
