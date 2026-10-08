#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<int> readings;
    readings.reserve(5);
    readings.push_back(42);
    readings.push_back(18);
    readings.push_back(31);
    readings.push_back(18);
    readings.push_back(27);
    cpstd::sort(readings.begin(), readings.end());

    Serial.print("Sorted readings: ");
    for (cpstd::size_t index = 0; index < readings.size(); ++index) {
        Serial.print(index == 0 ? "" : ", ");
        Serial.print(readings[index]);
    }
    Serial.println();
}

void loop() {
}
