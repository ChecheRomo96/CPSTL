#include <CPSTL.h>


/*
  Goal: Search: locate a reading without hand-writing an index loop.
  Interfaces: cpstd::find(), vector::begin(), end(), iterator subtraction.
  Observe: find() is always checked against end() before the result is used.
*/
void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Measurement lookup: find the first exact match.");
    cpstd::vector<int> readings;
    const int session[] = {18, 24, 31, 18, 27};
    const cpstd::size_t sampleCount = sizeof(session) / sizeof(session[0]);
    readings.reserve(sampleCount);
    if (readings.capacity() < sampleCount) {
        Serial.println("Not enough memory to store the session.");
        return;
    }
    Serial.print("Session: ");
    for (cpstd::size_t index = 0; index < sampleCount; ++index) {
        readings.push_back(session[index]);
        if (index != 0) Serial.print(", ");
        Serial.print(session[index]);
    }
    Serial.println();

    const int targetReading = 31;
    const cpstd::vector<int>::iterator found =
        cpstd::find(readings.begin(), readings.end(), targetReading);
    Serial.print("Looking for exact reading: ");
    Serial.println(targetReading);
    if (found == readings.end()) {
        Serial.println("No matching reading in this session.");
    } else {
        Serial.print("Matched reading: ");
        Serial.println(*found);
        Serial.print("Index (zero-based): ");
        Serial.println(static_cast<long>(found - readings.begin()));
        Serial.print("Sample number (one-based): ");
        Serial.println(static_cast<long>(found - readings.begin()) + 1);
    }
    Serial.println("find() stops at the first exact match; end() means no match.");
    Serial.println("Try 18 for the first match, or 99 for no match.");
}

void loop() {}
