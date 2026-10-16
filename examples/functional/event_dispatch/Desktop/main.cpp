#include <CPSTL.h>
#include <stdio.h>

// Send every simulated reading to two independent callbacks.
namespace {
    int total = 0;
    int alarms = 0;
    void Record(int value) { total += value; }
    void CheckAlarm(int value) { if (value >= 10) ++alarms; }
}

int main() {
    printf("Send every simulated reading to two independent callbacks.\n");
    cpstd::vector<cpstd::function<void(int)> > listeners;
    listeners.reserve(2);
    if (listeners.capacity() < 2) { printf("Not enough memory for listeners.\n"); return 1; }
    cpstd::function<void(int)> record(&Record);
    cpstd::function<void(int)> alarm(&CheckAlarm);
    if (!record || !alarm) { printf("Could not create the callbacks.\n"); return 1; }
    listeners.push_back(record);
    listeners.push_back(alarm);
    if (!listeners[0] || !listeners[1]) { printf("Could not store the callbacks.\n"); return 1; }
    printf("Listeners: recorder sums readings; alarm counts readings >= 10.\n");
    printf("Registered listeners: %ld\n", static_cast<long>(listeners.size()));
    const int readings[] = {8, 12, 15};
    for (cpstd::size_t i = 0; i < sizeof(readings) / sizeof(readings[0]); ++i) {
        printf("Dispatch reading: %ld\n", static_cast<long>(readings[i]));
        for (cpstd::size_t listener = 0; listener < listeners.size(); ++listener) {
            listeners[listener](readings[i]);
        }
        printf("  Recorder running total: %ld\n", static_cast<long>(total));
        printf("  Alarm count (reading >= 10): %ld\n", static_cast<long>(alarms));
    }
    printf("Each reading reached both callbacks; the recorder and alarm keep separate state.\n");
    return 0;
}
