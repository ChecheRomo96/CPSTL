# Exclusive sensor

Transfer ownership of a simulated sensor to a logger.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Transfer ownership of a simulated sensor to a logger.
Before move, driver owns sensor ID: 42
After move, driver is empty: yes
After move, logger owns sensor ID: 42
Simulated logger reading (ID * 10): 420
The sensor was transferred, not copied; logger releases it automatically on exit.
```
