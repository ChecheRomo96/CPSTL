#include <CPSTL.h>


/*
  Goal: Bidirectional traversal: replay a captured sequence from newest to oldest.
  Interfaces: vector::begin()/end() and rbegin()/rend().
  Observe: The same samples print in capture order and reverse order.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    const size_t sampleCount = 20;
    cpstd::vector<uint8_t> samples;
    samples.reserve(sampleCount);
    if (samples.capacity() < sampleCount) {
        Serial.println("Not enough memory to capture samples.");
        return;
    }
    for (size_t i = 0; i < sampleCount; ++i) {
        samples.push_back(static_cast<uint8_t>(random(256)));
    }

    Serial.println("Captured samples in time order:");
    Serial.print("Forward: ");
    for (cpstd::vector<uint8_t>::iterator it = samples.begin(); it != samples.end(); ++it) {
        Serial.print(*it);
        Serial.print(' ');
    }
    Serial.print("\nUndo/playback: ");
    for (cpstd::vector<uint8_t>::reverse_iterator it = samples.rbegin(); it != samples.rend(); ++it) {
        Serial.print(*it);
        Serial.print(' ');
    }
    Serial.println("\nReverse iterators start at rbegin() and stop at rend().");
}

void loop() {}
