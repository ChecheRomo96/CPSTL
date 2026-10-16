# Command parser

Parse complete integer commands and explain rejected input.

Arduino and desktop run the same scenario. Values labeled simulated do not
come from attached hardware. Read the printed inputs, operations and results
in order.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Parse complete integer commands and explain rejected input.
Input: tempo=120
  Parsed name: tempo
  Parsed integer value: 120
Input: transpose=-2
  Parsed name: transpose
  Parsed integer value: -2
Input: broken
  Rejected: missing '='; expected name=integer.
Input: =120
  Rejected: both the name and value must be present.
Input: tempo=
  Rejected: both the name and value must be present.
Input: tempo=fast
  Rejected: the whole value must be an integer, with an optional sign.
Input: tempo=12x
  Rejected: the whole value must be an integer, with an optional sign.
Check structure, digits and the application range before converting with stoi().
```
