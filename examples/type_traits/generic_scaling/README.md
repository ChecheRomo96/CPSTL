# Generic scaling

Convert a simulated 10-bit ADC sample to millivolts.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Convert a simulated 10-bit ADC sample to millivolts.
Simulated ADC sample: 768
ADC full-scale count: 1023
Reference voltage (mV): 5000
Calculation: 768 * 5000 / 1023, using long integers to avoid AVR int overflow.
Converted voltage (mV): 3753
Integer division discards the fraction; this sample is about 3753 mV.
is_integral rejects floating-point inputs at compile time, not at runtime.
```
