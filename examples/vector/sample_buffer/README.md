# Sample buffer

Reserve storage before an eight-sample capture.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.
`reserve(n)` guarantees at least n slots; the reported capacity may vary by implementation.

```text
Reserve storage before an eight-sample capture.
Before reserve, size: 0
Before reserve, capacity: 0
After reserve(8), size: 0
After reserve(8), capacity: 8
reserve() allocates space but does not create samples.
Captured reading: 100
  Stored samples: 1
  Available capacity: 8
Captured reading: 103
  Stored samples: 2
  Available capacity: 8
Captured reading: 106
  Stored samples: 3
  Available capacity: 8
Captured reading: 109
  Stored samples: 4
  Available capacity: 8
Captured reading: 112
  Stored samples: 5
  Available capacity: 8
Captured reading: 115
  Stored samples: 6
  Available capacity: 8
Captured reading: 118
  Stored samples: 7
  Available capacity: 8
Captured reading: 121
  Stored samples: 8
  Available capacity: 8
Completed capture: 100, 103, 106, 109, 112, 115, 118, 121
Capacity unchanged during capture: yes
```
