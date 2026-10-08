#include <CPfunctional.h>
#include <CPvector>

namespace {
    int total = 0;

    void Record(int value) {
        total += value;
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<cpstd::function<void(int)> > listeners;
    listeners.reserve(1);
    listeners.push_back(&Record);
    listeners[0](12);
    listeners[0](8);
    Serial.print("Event total: ");
    Serial.println(total);
}

void loop() {
}
