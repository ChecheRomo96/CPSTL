# Measurement lookup

Search a short measurement session with `cpstd::find` instead of hand-writing
an index loop. Check the returned iterator against `end()` before consuming it
when the searched value may be absent in a real application.
