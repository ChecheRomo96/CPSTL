# Event dispatch

Register a callback in `cpstd::function` and dispatch measurements to it. The
vector is reserved before listener registration; extend the scenario by adding
multiple independent subscribers such as a logger and a threshold monitor.
