# Reverse playback

Generate exactly 20 pseudorandom byte samples (0–255) and traverse them with reverse iterators
for playback. The same iterator vocabulary works on hosted and freestanding
targets, so no target-specific reverse loop is needed.

Arduino uses `random(256)` and desktop uses `rand() % 256`; the generated
values may differ, but each reverse traversal replays its forward sequence
from newest to oldest. Both examples reserve storage before filling it and
report allocation failure rather than repeatedly trying to add samples.

## Example output

Observed on desktop with CPSTL mode enabled. Arduino prints the same scenario.
Pseudorandom values depend on the platform; the reverse line must reverse the forward line.

```text
Captured samples in time order:
Forward: 41 35 190 132 225 108 214 174 82 144 73 241 241 187 233 235 179 166 219 60
Undo/playback: 60 219 166 179 235 233 187 241 241 73 144 82 174 214 108 225 132 190 35 41
Reverse iterators start at rbegin() and stop at rend().
```
