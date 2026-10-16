# State handoff

Replace active state with exchange, then trade values with swap.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Replace active state with exchange, then trade values with swap.
Initial active channel: 1
Initial standby channel: 3
Operation: exchange(activeChannel, 2).
  Returned previous channel: 1
  New active channel: 2
Operation: swap(activeChannel, standbyChannel).
  Active channel after swap: 3
  Standby channel after swap: 2
exchange replaces one value and returns its old value; swap trades two values.
```
