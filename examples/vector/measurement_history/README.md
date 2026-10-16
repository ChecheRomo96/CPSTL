# Measurement history

Sort a report copy while preserving capture order.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Sort a report copy while preserving capture order.
Original capture order: 42, 18, 31, 18, 27
Sorted report copy (lowest to highest): 18, 18, 27, 31, 42
Original history after sorting the copy: 42, 18, 31, 18, 27
sort() changed the copy, so the capture order remains available.
```
