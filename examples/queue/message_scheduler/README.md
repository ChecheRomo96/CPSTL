# Message scheduler

Process messages in arrival order (FIFO).

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Process messages in arrival order (FIFO).
Incoming message IDs: 101, 205, 112.
Processing the oldest waiting message first:
  Processing message ID: 101
  Messages still waiting: 2
  Processing message ID: 205
  Messages still waiting: 1
  Processing message ID: 112
  Messages still waiting: 0
Queue empty after processing: yes
```
