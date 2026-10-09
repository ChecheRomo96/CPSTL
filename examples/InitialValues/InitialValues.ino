#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::vector<int> chord = {60, 64, 67};
    Serial.print("Chord notes: ");
    Serial.println(chord.size());
}

void loop() {}
