# CPSTL tutorials

Every directory in this folder is a small program that solves one portable
application problem. It is not a unit test: boundary cases and failure modes
belong under `tests/`.

Each tutorial has an Arduino sketch at its root and a matching desktop entry
point in `Desktop/main.cpp`. Shared source files, when a tutorial needs them,
live next to those entry points.

| Tutorial | What it teaches | CPSTL facilities |
| --- | --- | --- |
| `BuildConfiguration` | Inspect the selected portable configuration | build settings, type traits, numeric limits |
| `SortedReadings` | Collect and order a small set of measurements | vector, algorithms, iterators |
| `FixedCapacityLog` | Reserve storage before recording a time-critical log | vector, string, utility |
| `TextCommand` | Parse a small textual command without exceptions | string, algorithms |
| `EventPipeline` | Chain callbacks and transfer ownership safely | function, vector, memory, utility |

Compile desktop tutorials through the normal CMake examples target. Compile
all Arduino tutorials with `scripts/test-arduino.sh`; the script uses the
stock C++11 flags of the selected Arduino core.
