#include <CPSTL.h>

// Edit control steps and inspect each resulting sequence.
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
    Serial.println("Edit control steps and inspect each resulting sequence.");
    cpstd::vector<int> steps;
    steps.reserve(3);
    if (steps.capacity() < 3) { Serial.println("Not enough memory for the control steps."); return; }
    steps.push_back(10);
    steps.push_back(30);
    Serial.println("Step codes: 10=warm-up, 20=calibration, 30=run.");
    PrintValues("Original program", steps);
    steps.insert(steps.begin() + 1, 20);
    PrintValues("After insert at zero-based index 1", steps);
    steps.erase(steps.begin());
    PrintValues("After erase of the first step", steps);
    Serial.println("The remaining program calibrates, then runs; warm-up was removed.");
}

void loop() {}
