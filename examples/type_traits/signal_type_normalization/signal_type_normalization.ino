#include <CPSTL.h>
#include <CPtype_traits.h>

// Copy a qualified observation into a plain value type.
typedef const volatile int SensorValue;
typedef cpstd::remove_cv<SensorValue>::type PlainSensorValue;
static_assert(cpstd::is_same<PlainSensorValue, int>::value, "qualifiers are removed");

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Copy a qualified observation into a plain value type.");
    SensorValue simulatedRegister = 512;
    const PlainSensorValue sample = simulatedRegister;
    Serial.println("Source type: const volatile int (simulated hardware register).");
    Serial.println("remove_cv<SensorValue>::type: int (checked by static_assert).");
    Serial.print("Value copied from the simulated register: "); Serial.println(static_cast<long>(sample));
    Serial.print("Plain value passed to generic code: "); Serial.println(static_cast<long>(sample));
    Serial.println("remove_cv changes a type; copying the value performs the register read.");
}

void loop() {}
