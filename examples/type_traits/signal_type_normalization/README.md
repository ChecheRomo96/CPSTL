# Signal type normalization

Copy a qualified observation into a plain value type.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Copy a qualified observation into a plain value type.
Source type: const volatile int (simulated hardware register).
remove_cv<SensorValue>::type: int (checked by static_assert).
Value copied from the simulated register: 512
Plain value passed to generic code: 512
remove_cv changes a type; copying the value performs the register read.
```
