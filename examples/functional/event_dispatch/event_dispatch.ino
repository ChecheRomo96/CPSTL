#include <CPSTL.h>

// Send every simulated reading to two independent callbacks.
namespace {
    int total = 0;
    int alarms = 0;
    void Record(int value) { total += value; }
    void CheckAlarm(int value) { if (value >= 10) ++alarms; }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Send every simulated reading to two independent callbacks.");
    cpstd::vector<cpstd::function<void(int)> > listeners;
    listeners.reserve(2);
    if (listeners.capacity() < 2) { Serial.println("Not enough memory for listeners."); return; }
    cpstd::function<void(int)> record(&Record);
    cpstd::function<void(int)> alarm(&CheckAlarm);
    if (!record || !alarm) { Serial.println("Could not create the callbacks."); return; }
    listeners.push_back(record);
    listeners.push_back(alarm);
    if (!listeners[0] || !listeners[1]) { Serial.println("Could not store the callbacks."); return; }
    Serial.println("Listeners: recorder sums readings; alarm counts readings >= 10.");
    Serial.print("Registered listeners: "); Serial.println(static_cast<long>(listeners.size()));
    const int readings[] = {8, 12, 15};
    for (cpstd::size_t i = 0; i < sizeof(readings) / sizeof(readings[0]); ++i) {
        Serial.print("Dispatch reading: "); Serial.println(static_cast<long>(readings[i]));
        for (cpstd::size_t listener = 0; listener < listeners.size(); ++listener) {
            listeners[listener](readings[i]);
        }
        Serial.print("  Recorder running total: "); Serial.println(static_cast<long>(total));
        Serial.print("  Alarm count (reading >= 10): "); Serial.println(static_cast<long>(alarms));
    }
    Serial.println("Each reading reached both callbacks; the recorder and alarm keep separate state.");
}

void loop() {}
