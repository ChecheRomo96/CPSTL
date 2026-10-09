#include <CPSTL.h>
#include <CPlimits.h>

void setup() {
    Serial.begin(9600);
    Serial.print("Unsigned byte range: 0..");
    Serial.println(cpstd::numeric_limits<unsigned char>::max());
}

void loop() {}
