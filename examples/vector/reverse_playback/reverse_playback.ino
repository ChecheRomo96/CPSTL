#include <CPSTL.h>


/*
  Goal: Bidirectional traversal: replay a captured sequence from newest to oldest.
  Interfaces: vector::begin()/end() and rbegin()/rend().
  Observe: The same samples print in capture order and reverse order.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::vector<int> samples;
    samples.push_back(7);
    samples.push_back(11);
    samples.push_back(13);

    Serial.println("Recorded button states in time order:");
    Serial.print("Forward: ");
    for (cpstd::vector<int>::iterator it = samples.begin(); it != samples.end(); ++it) {
        Serial.print(*it);
        Serial.print(' ');
    }
    Serial.print("\nUndo/playback: ");
    for (cpstd::vector<int>::reverse_iterator it = samples.rbegin(); it != samples.rend(); ++it) {
        Serial.print(*it);
        Serial.print(' ');
    }
    Serial.println("\nReverse iterators start at rbegin() and stop at rend().");
}

void loop() {}
