# Sample copy

Copy a packet into an independent log.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Copy a packet into an independent log.
Source packet: 3, 5, 8
Destination size before copy: 0
Destination after copy with back_inserter: 3, 5, 8
Destination after changing its first sample to 99: 99, 5, 8
Source packet remains unchanged: 3, 5, 8
The copied vector owns independent storage.
```
