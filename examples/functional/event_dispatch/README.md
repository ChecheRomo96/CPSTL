# Event dispatch

Send every simulated reading to two independent callbacks.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Send every simulated reading to two independent callbacks.
Listeners: recorder sums readings; alarm counts readings >= 10.
Registered listeners: 2
Dispatch reading: 8
  Recorder running total: 8
  Alarm count (reading >= 10): 0
Dispatch reading: 12
  Recorder running total: 20
  Alarm count (reading >= 10): 1
Dispatch reading: 15
  Recorder running total: 35
  Alarm count (reading >= 10): 2
Each reading reached both callbacks; the recorder and alarm keep separate state.
```
