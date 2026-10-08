// Verifiable cpstd::function example for Arduino.
// Open the Serial Monitor at 9600 baud. The final line must report PASS.

#include <CPSTL.h>

namespace {
    int Triple(int value) { return value * 3; }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    int total = 0;
    cpstd::function<void(int)> record = [&total](int value) { total += value; };
    cpstd::function<int(int)> transform = Triple;

    record(4);
    record(7);
    const int transformed = transform(total);
    const bool passed = static_cast<bool>(record) && static_cast<bool>(transform) &&
                        total == 11 && transformed == 33;

    Serial.print("recorded total: ");
    Serial.println(total);
    Serial.print("triple(total): ");
    Serial.println(transformed);
    Serial.print("CPSTL Arduino Function: ");
    Serial.println(passed ? "PASS" : "FAIL");
}

void loop() {
}
