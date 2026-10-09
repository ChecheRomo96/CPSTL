#include <CPtype_traits.h>

#include <stdio.h>

typedef const volatile int SensorValue;
typedef cpstd::remove_cv<SensorValue>::type PlainSensorValue;
static_assert(cpstd::is_same<PlainSensorValue, int>::value, "qualifiers are removed");

int main() {
    printf("Sensor value is integral: %s\n", cpstd::is_integral<PlainSensorValue>::value ? "yes" : "no");
    return 0;
}
