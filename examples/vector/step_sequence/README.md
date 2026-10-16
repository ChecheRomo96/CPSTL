# Step sequence

Edit control steps and inspect each resulting sequence.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Edit control steps and inspect each resulting sequence.
Step codes: 10=warm-up, 20=calibration, 30=run.
Original program: 10, 30
After insert at zero-based index 1: 10, 20, 30
After erase of the first step: 20, 30
The remaining program calibrates, then runs; warm-up was removed.
```
