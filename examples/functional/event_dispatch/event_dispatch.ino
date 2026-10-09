#include <CPfunctional.h>
#include <CPvector>


/*
  Goal: Callbacks: fan one measurement out to independent reactions.
  Interfaces: cpstd::function<void(int)>, cpstd::vector::push_back(), operator().
  Observe: Every measurement updates the recorder and the alarm independently.
*/
namespace {
    int total = 0;
    int alarms = 0;

    void Record(int value) {
        total += value;
    }

    void CheckAlarm(int value) {
        if (value >= 10) ++alarms;
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<cpstd::function<void(int)> > listeners;
    listeners.reserve(2);
    listeners.push_back(&Record);
    listeners.push_back(&CheckAlarm);
    const int readings[] = {8, 12, 15};
    for (cpstd::size_t reading = 0; reading < 3; ++reading) {
        Serial.print("Dispatch measurement: "); Serial.println(readings[reading]);
        for (cpstd::size_t listener = 0; listener < listeners.size(); ++listener)
            listeners[listener](readings[reading]);
    }
    Serial.print("Recorded total: "); Serial.println(total);
    Serial.print("Threshold alarms: "); Serial.println(alarms);
    Serial.println("One event fan-outs to every registered cpstd::function callback.");
}

void loop() {
}
