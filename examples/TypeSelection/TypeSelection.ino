#include <CPSTL.h>
#include <CPlimits.h>

static_assert(cpstd::is_integral<int>::value, "int is integral");
static_assert(!cpstd::is_integral<float>::value, "float is not integral");

void setup() {
    Serial.begin(9600);
    Serial.print("int is integral: ");
    Serial.println(cpstd::is_integral<int>::value ? "yes" : "no");
    Serial.print("Byte max: ");
    Serial.println(cpstd::numeric_limits<unsigned char>::max());
}

void loop() {}
