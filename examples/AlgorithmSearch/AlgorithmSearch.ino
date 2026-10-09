#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::vector<int> readings;
    readings.push_back(18);
    readings.push_back(24);
    readings.push_back(31);
    const cpstd::vector<int>::iterator found = cpstd::find(readings.begin(), readings.end(), 24);
    Serial.print("Selected reading at index: ");
    Serial.println(found - readings.begin());
}

void loop() {}
