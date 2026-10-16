# Status message

Compose a readable status message from simulated telemetry.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Compose a readable status message from simulated telemetry.
Simulated channel ID: 2
Simulated battery reading (mV): 3712
Composed status: Channel 2 is ready; battery=3712 mV
Message length (characters): 35
operator+= joins the text and numeric fields; c_str() supplies the printable string.
```
