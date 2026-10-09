#include <CPSTL.h>


/*
  Goal: Real-time capture pattern: reserve first, then append readings during a burst.
  Interfaces: vector::reserve(), push_back(), size() plus string formatting.
  Observe: No allocation needs to happen inside the illustrated capture loop.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<int> log;
    const cpstd::size_t samplesPerBurst = 4;
    log.reserve(samplesPerBurst); // all storage is acquired before the burst
    Serial.print("Capacity reserved before capture: "); Serial.println(log.capacity());
    for (int sample = 0; sample < 4; ++sample) {
        const int reading = 420 + sample * 7;
        log.push_back(reading);
        Serial.print("Captured "); Serial.println(reading);
    }

    cpstd::string message("Recorded ");
    message += cpstd::to_string(static_cast<int>(log.size()));
    message += " samples without growing storage during capture.";
    Serial.println(message.c_str());
    Serial.println("If a burst can exceed this budget, reserve more before sampling.");
}

void loop() {
}
