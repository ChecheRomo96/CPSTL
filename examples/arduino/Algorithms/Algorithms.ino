// Verifiable CPSTL algorithm example for Arduino.
// Open the Serial Monitor at 9600 baud. The final line must report PASS.

#include <CPSTL.h>

namespace {
    void PrintValues(const char* label, const int* values, cpstd::size_t count) {
        Serial.print(label);
        for (cpstd::size_t index = 0; index < count; ++index) {
            Serial.print(index == 0 ? " " : ", ");
            Serial.print(values[index]);
        }
        Serial.println();
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    int source[] = {6, 2, 9, 2};
    int copied[4] = {0, 0, 0, 0};
    cpstd::copy(source, source + 4, copied);
    cpstd::sort(copied, copied + 4);
    PrintValues("sorted:", copied, 4);

    const int* found = cpstd::find(copied, copied + 4, 6);
    int expected[] = {2, 2, 6, 9};
    const bool passed = found != copied + 4 && *found == 6 &&
                        cpstd::equal(copied, copied + 4, expected);

    Serial.print("found 6 at index: ");
    Serial.println(found == copied + 4 ? -1 : static_cast<int>(found - copied));
    Serial.print("CPSTL Arduino Algorithms: ");
    Serial.println(passed ? "PASS" : "FAIL");
}

void loop() {
}
