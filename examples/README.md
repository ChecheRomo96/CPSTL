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
| `AlgorithmSearch` | Locate a selected reading in a sequence | algorithms, vector |
| `FixedCapacityLog` | Reserve storage before recording a time-critical log | vector, string, utility |
| `VectorCapacity` | Plan vector storage before a recording session | vector |
| `VectorInsertion` | Insert and remove items from an ordered list | vector |
| `InitialValues` | Start a sequence from a compact literal list | initializer list, vector |
| `TextCommand` | Parse a small textual command without exceptions | string, algorithms |
| `TextFormatting` | Assemble a human-readable status line | string, utility |
| `EventPipeline` | Chain callbacks and transfer ownership safely | function, vector, memory, utility |
| `IteratorTraversal` | Traverse a recorded sequence in both directions | iterator, vector |
| `IteratorInsertion` | Copy readings through an output iterator | iterator, algorithms, vector |
| `UndoStack` | Store and undo the most recent actions | stack |
| `MessageQueue` | Process work in first-in-first-out order | queue |
| `OwnershipTransfer` | Express exclusive ownership without a standard library | memory, utility |
| `TypeSelection` | Select overloads from compile-time type properties | type traits, numeric limits |
| `TypeInspection` | Remove qualifiers and inspect a type safely | type traits |
| `NumericBounds` | Choose a portable numeric range for a sensor value | numeric limits |
| `DiagnosticMessage` | Use CPSTL diagnostic vocabulary without throwing | exception |
| `ValueExchange` | Replace and swap state without temporary storage | utility |

Compile desktop tutorials through the normal CMake examples target. Compile
all Arduino tutorials with `scripts/test-arduino.sh`; the script uses the
stock C++11 flags of the selected Arduino core.
