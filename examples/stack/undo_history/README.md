# Undo history

Restore previous brightness settings in reverse order (LIFO).

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Restore previous brightness settings in reverse order (LIFO).
Initial brightness: 10
Changed brightness to: 20
Changed brightness to: 40
Undo saves the previous setting before each edit.
Undo restored brightness: 20
  Remaining undo entries: 1
Undo restored brightness: 10
  Remaining undo entries: 0
No older setting remains; top() is never called on an empty stack.
```
