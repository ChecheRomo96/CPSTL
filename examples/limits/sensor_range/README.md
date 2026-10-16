# Sensor range

Check whether a simulated ADC reading fits its storage type.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.
The maximum `int` is typically 32767 on AVR and 2147483647 on this desktop build.

```text
Check whether a simulated ADC reading fits its storage type.
Candidate storage: unsigned char, minimum 0.
Maximum value for that type: 255
Simulated ADC reading: 300
Does the reading fit? no
Maximum int on this target: 2147483647
Check the range before converting; choose a wider type when the reading does not fit.
```
