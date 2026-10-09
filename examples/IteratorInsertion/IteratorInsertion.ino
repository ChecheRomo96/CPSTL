#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::vector<int> source;
    source.push_back(3);
    source.push_back(5);
    cpstd::vector<int> destination;
    cpstd::copy(source.begin(), source.end(), cpstd::back_inserter(destination));
    Serial.print("Copied samples: ");
    Serial.println(destination.size());
}

void loop() {}
