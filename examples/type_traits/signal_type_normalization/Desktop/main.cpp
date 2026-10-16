#include <CPSTL.h>
#include <CPtype_traits.h>
#include <stdio.h>

// Copy a qualified observation into a plain value type.
typedef const volatile int SensorValue;
typedef cpstd::remove_cv<SensorValue>::type PlainSensorValue;
static_assert(cpstd::is_same<PlainSensorValue, int>::value, "qualifiers are removed");

int main() {
    printf("Copy a qualified observation into a plain value type.\n");
    SensorValue simulatedRegister = 512;
    const PlainSensorValue sample = simulatedRegister;
    printf("Source type: const volatile int (simulated hardware register).\n");
    printf("remove_cv<SensorValue>::type: int (checked by static_assert).\n");
    printf("Value copied from the simulated register: %ld\n", static_cast<long>(sample));
    printf("Plain value passed to generic code: %ld\n", static_cast<long>(sample));
    printf("remove_cv changes a type; copying the value performs the register read.\n");
    return 0;
}
