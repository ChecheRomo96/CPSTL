#include <CPSTL.h>

// Reserve storage before an eight-sample capture.
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
    Serial.println("Reserve storage before an eight-sample capture.");
    cpstd::vector<int> samples;
    const cpstd::size_t captureBudget = 8;
    Serial.print("Before reserve, size: "); Serial.println(static_cast<long>(samples.size()));
    Serial.print("Before reserve, capacity: "); Serial.println(static_cast<long>(samples.capacity()));
    samples.reserve(captureBudget);
    if (samples.capacity() < captureBudget) { Serial.println("Not enough memory for the capture budget."); return; }
    const cpstd::size_t reserved = samples.capacity();
    Serial.print("After reserve(8), size: "); Serial.println(static_cast<long>(samples.size()));
    Serial.print("After reserve(8), capacity: "); Serial.println(static_cast<long>(reserved));
    Serial.println("reserve() allocates space but does not create samples.");
    for (int sample = 0; sample < 8; ++sample) {
        const int reading = 100 + sample * 3;
        samples.push_back(reading);
        Serial.print("Captured reading: "); Serial.println(static_cast<long>(reading));
        Serial.print("  Stored samples: "); Serial.println(static_cast<long>(samples.size()));
        Serial.print("  Available capacity: "); Serial.println(static_cast<long>(samples.capacity()));
    }
    PrintValues("Completed capture", samples);
    Serial.print("Capacity unchanged during capture: "); Serial.println(samples.capacity() == reserved ? "yes" : "no");
}

void loop() {}
