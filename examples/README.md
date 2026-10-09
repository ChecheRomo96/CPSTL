# CPSTL tutorials

These are small, complete programs, not test cases. Each tutorial starts with
a practical situation, walks through the CPSTL operations that solve it, and
prints an observable result on either a serial monitor or stdout. Edge cases,
allocation failures and API conformance remain in `tests/`.

Tutorials are grouped by their primary CPSTL class or module. Arduino IDE
shows these folders as nested groups, so `vector`, `string`, `queue`, and the
other facilities can be explored independently.

Every `examples/<module>/<tutorial_name>/` directory contains:

```text
<tutorial_name>.ino    # Arduino entry point; opens directly in Arduino IDE
Desktop/main.cpp       # same scenario for a hosted desktop build
CMakeLists.txt         # enables the tutorial only when its modules exist
README.md              # goal, walkthrough, expected output and extensions
```

| Tutorial | Situation | Primary CPSTL facilities |
| --- | --- | --- |
| [`configuration_report`](configuration/configuration_report) | Report the selected portable build configuration | configuration |
| [`measurement_history`](vector/measurement_history) | Sort a sensor history before presenting it | vector, algorithms |
| [`measurement_lookup`](vector/measurement_lookup) | Find a selected measurement in a session | vector, algorithms |
| [`telemetry_log`](vector/telemetry_log) | Preallocate a telemetry log before sampling | vector, string |
| [`sample_buffer`](vector/sample_buffer) | Budget vector capacity before starting a capture | vector |
| [`step_sequence`](vector/step_sequence) | Edit an ordered sequence of control steps | vector |
| [`chord_notes`](vector/chord_notes) | Start a note collection from literal values | initializer list, vector |
| [`command_parser`](string/command_parser) | Parse a small `name=value` command | string |
| [`status_message`](string/status_message) | Assemble a readable channel status | string |
| [`event_dispatch`](functional/event_dispatch) | Deliver an event to registered callbacks | function, vector |
| [`reverse_playback`](vector/reverse_playback) | Play a recorded sequence in reverse | iterators, vector |
| [`sample_copy`](vector/sample_copy) | Copy samples through an output iterator | iterators, algorithms, vector |
| [`undo_history`](stack/undo_history) | Undo the most recent user action | stack |
| [`message_scheduler`](queue/message_scheduler) | Process messages in arrival order | queue |
| [`exclusive_sensor`](memory/exclusive_sensor) | Transfer ownership of a sensor object | unique_ptr, move |
| [`generic_scaling`](type_traits/generic_scaling) | Select integral-only behavior at compile time | type traits |
| [`signal_type_normalization`](type_traits/signal_type_normalization) | Normalize qualified signal types safely | type traits |
| [`sensor_range`](limits/sensor_range) | Choose a portable numeric storage range | numeric_limits |
| [`diagnostic_record`](exception/diagnostic_record) | Carry a diagnostic message without throwing | exception |
| [`state_handoff`](utility/state_handoff) | Replace and exchange active state explicitly | utility |

Compile desktop tutorials through the normal CMake examples target. Compile
all Arduino tutorials with `scripts/test-arduino.sh`; it uses the stock C++11
flags of the selected core.
