# Telemetry log

Capture a simulated telemetry burst in preallocated storage.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.
`reserve(n)` guarantees at least n slots; the reported capacity may vary by implementation.

```text
Capture a simulated telemetry burst in preallocated storage.
Capacity before capture: 4
Simulated sensor readings in millivolts:
Stored burst (mV): 420, 427, 434, 441
Summary: Recorded 4 samples.
Capacity after capture: 4
Storage stayed the same during capture: yes
Capture first, then format and print; serial output is outside the capture loop.
```
