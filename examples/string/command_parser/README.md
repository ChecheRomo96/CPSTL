# Command parser

Parse a `name=value` command with `find`, `substr` and `stoi`. In production,
validate the separator before slicing; CPSTL's string conversions are designed
for exception-free embedded use.
