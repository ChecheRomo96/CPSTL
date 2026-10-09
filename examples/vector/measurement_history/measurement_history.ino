#include <CPSTL.h>


/*
  Goal: History and algorithms: preserve capture order while deriving a ranked report.
  Interfaces: vector::reserve(), push_back(), copy construction, cpstd::sort().
  Observe: The chronological data remains unchanged after sorting the report copy.
*/
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
    Serial.print("Capture order: ");
    for (cpstd::size_t index = 0; index < readings.size(); ++index) {
        Serial.print(index == 0 ? "" : ", ");
        Serial.print(readings[index]);
    }
    Serial.println();
    // Sort a copy only when the report, not the capture order, needs ranking.
    cpstd::vector<int> ranked(readings);
    cpstd::sort(ranked.begin(), ranked.end());
    Serial.print("Lowest to highest: ");
    for (cpstd::size_t index = 0; index < ranked.size(); ++index) {
        Serial.print(index == 0 ? "" : ", ");
        Serial.print(ranked[index]);
    }
    Serial.println("\nThe original history is retained for time-based analysis.");
}

void loop() {
}
