#include <CPSTL.h>


/*
  Goal: Capacity planning: allocate a capture budget before a time-sensitive loop.
  Interfaces: vector::reserve(), capacity(), size(), push_back().
  Observe: Capacity stays stable while the pre-budgeted burst is captured.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::vector<int> samples;
    const cpstd::size_t captureBudget = 8;
    samples.reserve(captureBudget); // Allocate before the timing-sensitive capture.
    Serial.print("Capture budget: "); Serial.println(captureBudget);
    Serial.print("Allocated capacity: "); Serial.println(samples.capacity());
    for (int sample = 0; sample < 8; ++sample) {
        samples.push_back(100 + sample * 3);
        Serial.print("Captured #"); Serial.print(sample);
        Serial.print("; size="); Serial.print(samples.size());
        Serial.print(", capacity="); Serial.println(samples.capacity());
    }
    Serial.println("Reserve the worst expected burst before entering a real ISR or loop.");
}

void loop() {}
