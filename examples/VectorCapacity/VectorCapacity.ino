#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::vector<int> samples;
    samples.reserve(8);
    samples.push_back(12);
    samples.push_back(15);
    Serial.print("Samples: ");
    Serial.print(samples.size());
    Serial.print(", reserved slots: ");
    Serial.println(samples.capacity());
}

void loop() {}
