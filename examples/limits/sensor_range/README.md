# Sensor range

Query `numeric_limits` instead of hard-coding an assumed byte width. This is
useful when choosing storage or validating a protocol field across compilers
and targets with different native integer characteristics.
