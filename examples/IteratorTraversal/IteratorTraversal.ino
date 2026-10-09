#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::vector<int> samples;
    samples.push_back(7);
    samples.push_back(11);
    samples.push_back(13);

    Serial.print("Forward: ");
    for (cpstd::vector<int>::iterator it = samples.begin(); it != samples.end(); ++it) {
        Serial.print(*it);
        Serial.print(' ');
    }
    Serial.print(" reverse: ");
    for (cpstd::vector<int>::reverse_iterator it = samples.rbegin(); it != samples.rend(); ++it) {
        Serial.print(*it);
        Serial.print(' ');
    }
    Serial.println();
}

void loop() {}
