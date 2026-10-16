#include <CPSTL.h>

// Capture a simulated telemetry burst in preallocated storage.
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
    Serial.println("Capture a simulated telemetry burst in preallocated storage.");
    cpstd::vector<int> log;
    const cpstd::size_t samplesPerBurst = 4;
    log.reserve(samplesPerBurst);
    if (log.capacity() < samplesPerBurst) { Serial.println("Not enough memory for the telemetry burst."); return; }
    const cpstd::size_t reserved = log.capacity();
    Serial.print("Capacity before capture: "); Serial.println(static_cast<long>(reserved));
    Serial.println("Simulated sensor readings in millivolts:");
    for (int sample = 0; sample < 4; ++sample) {
        const int reading = 420 + sample * 7;
        log.push_back(reading);
    }
    PrintValues("Stored burst (mV)", log);
    cpstd::string message("Recorded ");
    message += cpstd::to_string(static_cast<int>(log.size()));
    message += " samples.";
    Serial.print("Summary: "); Serial.println(message.c_str());
    Serial.print("Capacity after capture: "); Serial.println(static_cast<long>(log.capacity()));
    Serial.print("Storage stayed the same during capture: "); Serial.println(log.capacity() == reserved ? "yes" : "no");
    Serial.println("Capture first, then format and print; serial output is outside the capture loop.");
}

void loop() {}
