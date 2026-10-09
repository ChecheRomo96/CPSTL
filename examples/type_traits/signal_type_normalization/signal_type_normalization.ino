#include <CPSTL.h>


/*
  Goal: Type normalization: remove hardware qualifiers for generic value code.
  Interfaces: remove_cv<T>::type and is_same<T, U>::value.
  Observe: The volatile observation is passed as a normal value deliberately.
*/
typedef const volatile int SensorValue;
typedef cpstd::remove_cv<SensorValue>::type PlainSensorValue;
static_assert(cpstd::is_same<PlainSensorValue, int>::value, "qualifiers are removed");

void ReportSample(PlainSensorValue value) {
    Serial.print("Normalized sample: "); Serial.println(value);
}

void setup() {
    Serial.begin(9600);
    const volatile int hardwareRegister = 512;
    SensorValue observed = hardwareRegister;
    ReportSample(observed);
    Serial.println("remove_cv gives generic code its plain value type without reading hardware twice.");
}

void loop() {}
