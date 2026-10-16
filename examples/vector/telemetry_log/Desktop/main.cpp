#include <CPSTL.h>
#include <stdio.h>

// Capture a simulated telemetry burst in preallocated storage.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    printf("%s: ", label);
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        printf(i == 0 ? "%d" : ", %d", values[i]);
    }
    printf("\n");
}

int main() {
    printf("Capture a simulated telemetry burst in preallocated storage.\n");
    cpstd::vector<int> log;
    const cpstd::size_t samplesPerBurst = 4;
    log.reserve(samplesPerBurst);
    if (log.capacity() < samplesPerBurst) { printf("Not enough memory for the telemetry burst.\n"); return 1; }
    const cpstd::size_t reserved = log.capacity();
    printf("Capacity before capture: %ld\n", static_cast<long>(reserved));
    printf("Simulated sensor readings in millivolts:\n");
    for (int sample = 0; sample < 4; ++sample) {
        const int reading = 420 + sample * 7;
        log.push_back(reading);
    }
    PrintValues("Stored burst (mV)", log);
    cpstd::string message("Recorded ");
    message += cpstd::to_string(static_cast<int>(log.size()));
    message += " samples.";
    printf("Summary: %s\n", message.c_str());
    printf("Capacity after capture: %ld\n", static_cast<long>(log.capacity()));
    printf("Storage stayed the same during capture: %s\n", log.capacity() == reserved ? "yes" : "no");
    printf("Capture first, then format and print; serial output is outside the capture loop.\n");
    return 0;
}
