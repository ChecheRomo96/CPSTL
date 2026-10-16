#include <CPSTL.h>

// Sort a report copy while preserving capture order.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    Serial.print(label); Serial.print(": ");
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        if (i != 0) Serial.print(", ");
        Serial.print(values[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Sort a report copy while preserving capture order.");
    cpstd::vector<int> readings = {42, 18, 31, 18, 27};
    if (readings.size() != 5) { Serial.println("Not enough memory for the history."); return; }
    PrintValues("Original capture order", readings);
    cpstd::vector<int> ranked(readings);
    if (ranked.size() != readings.size()) { Serial.println("Not enough memory for the report copy."); return; }
    cpstd::sort(ranked.begin(), ranked.end());
    PrintValues("Sorted report copy (lowest to highest)", ranked);
    PrintValues("Original history after sorting the copy", readings);
    Serial.println("sort() changed the copy, so the capture order remains available.");
}

void loop() {}
