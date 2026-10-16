# Diagnostic record

Reject an invalid sample index and report a recovery action.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Reject an invalid sample index and report a recovery action.
Captured sample count: 4
Valid zero-based indices: 0 through 3.
Requested index: 6
Request rejected: requested sample is outside the capture
Recovery: request an index from 0 through 3; no buffer access was attempted.
The diagnostic object carries a message; this example does not throw an exception.
```
