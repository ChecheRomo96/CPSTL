# Exclusive sensor

Create a sensor object with `unique_ptr` and transfer its sole ownership with
`move`. After a move, only the destination may access the object; this makes
lifetime and cleanup explicit without a garbage collector.
