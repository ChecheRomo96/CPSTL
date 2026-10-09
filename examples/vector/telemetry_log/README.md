# Telemetry log

Reserve the required capacity before a time-sensitive sampling loop, then turn
the captured count into a readable status. This is the portable pattern when
allocation must happen before—not during—the critical section.
