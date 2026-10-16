# Configuration report

Use this first when moving a program between desktop and embedded targets. It
prints CPSTL's version, language mode, allocation strategy and enabled modules.
Compare the desktop output with the serial monitor before diagnosing a build.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.
Version, language value, enabled modules and allocation mode reflect the current build.

```text
CPSTL version: 1.1.8
C++ language value: 201402
Vocabulary: CPSTL portable implementation
Allocation: C (malloc/free)
cpstd::vector: enabled
cpstd::string: enabled
Unsigned byte maximum: 255
Use this report first after changing a board, compiler, or CPSTL build option.
Compare its output with the Arduino tutorial before investigating a mismatch.
```
