# Measurement lookup

Search a short measurement session with `cpstd::find` instead of hand-writing
an index loop. Check the returned iterator against `end()` before consuming it
even when the example's searched value is present.

Both versions print the five readings and search for an exact value, not a
threshold crossing. Searching for 31 returns zero-based index 2; try 18 for
the first of multiple matches (index 0), or 99 for no match.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.

```text
Measurement lookup: find the first exact match.
Session: 18, 24, 31, 18, 27
Looking for exact reading: 31
Matched reading: 31
Index (zero-based): 2
Sample number (one-based): 3
find() stops at the first exact match; end() means no match.
Try 18 for the first match, or 99 for no match.
```
