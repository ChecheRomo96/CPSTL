#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::vector<int> steps;
    steps.push_back(10);
    steps.push_back(30);
    steps.insert(steps.begin() + 1, 20);
    steps.erase(steps.begin());
    Serial.print("Remaining steps: ");
    Serial.print(steps[0]);
    Serial.print(", ");
    Serial.println(steps[1]);
}

void loop() {}
