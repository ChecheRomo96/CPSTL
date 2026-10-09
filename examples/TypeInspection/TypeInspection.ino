#include <CPSTL.h>

typedef const volatile int SensorValue;
typedef cpstd::remove_cv<SensorValue>::type PlainSensorValue;
static_assert(cpstd::is_same<PlainSensorValue, int>::value, "qualifiers are removed");

void setup() {
    Serial.begin(9600);
    Serial.print("Sensor value is integral: ");
    Serial.println(cpstd::is_integral<PlainSensorValue>::value ? "yes" : "no");
}

void loop() {}
