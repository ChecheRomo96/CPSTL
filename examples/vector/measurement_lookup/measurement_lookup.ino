#include <CPSTL.h>


/*
  Goal: Search: locate a reading without hand-writing an index loop.
  Interfaces: cpstd::find(), vector::begin(), end(), iterator subtraction.
  Observe: find() is always checked against end() before the result is used.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::vector<int> readings;
    const int session[] = {18, 24, 31, 18, 27};
    for (cpstd::size_t index = 0; index < 5; ++index) readings.push_back(session[index]);

    const int alarmThreshold = 31;
    const cpstd::vector<int>::iterator found =
        cpstd::find(readings.begin(), readings.end(), alarmThreshold);
    Serial.print("Looking for threshold "); Serial.println(alarmThreshold);
    if (found == readings.end()) {
        Serial.println("No reading crossed the threshold in this session.");
    } else {
        Serial.print("Found at sample #");
        Serial.println(found - readings.begin());
    }
    Serial.println("Try another threshold: always compare find() with end().");
}

void loop() {}
