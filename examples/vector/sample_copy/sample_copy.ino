#include <CPSTL.h>


/*
  Goal: Algorithm composition: copy a sequence into a growable destination.
  Interfaces: cpstd::copy(), cpstd::back_inserter(), vector::push_back().
  Observe: copy() fills the destination without exposing its storage mechanics.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::vector<int> source;
    source.push_back(3); source.push_back(5); source.push_back(8);
    cpstd::vector<int> destination;
    destination.reserve(source.size());
    cpstd::copy(source.begin(), source.end(), cpstd::back_inserter(destination));
    Serial.print("Radio packet samples: ");
    for (cpstd::size_t i = 0; i < source.size(); ++i) { Serial.print(source[i]); Serial.print(' '); }
    Serial.print("\nCopied log: ");
    for (cpstd::size_t i = 0; i < destination.size(); ++i) { Serial.print(destination[i]); Serial.print(' '); }
    Serial.println("\nback_inserter lets copy() grow the destination through push_back().");
}

void loop() {}
