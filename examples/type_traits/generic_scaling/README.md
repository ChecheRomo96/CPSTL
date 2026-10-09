# Generic scaling

Use type traits to permit an integral-only scaling operation at compile time.
The Arduino sketch uses direct trait inspection because the IDE preprocessor
does not reliably generate prototypes for every templated free function.
