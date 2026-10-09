#include <CPSTL.h>
#include <CPexception.h>


/*
  Goal: Exception vocabulary: describe a failed bounds check without throwing on an embedded target.
  Interfaces: cpstd::out_of_range::what().
  Observe: A rejected index produces a diagnostic and a recovery instruction.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    const int requestedIndex = 6;
    const int capturedSamples = 4;
    if (requestedIndex >= capturedSamples) {
        // Embedded code can carry a standard-style diagnostic without throwing it.
        const cpstd::out_of_range diagnostic("requested sample is outside the capture");
        Serial.print("Read #"); Serial.print(requestedIndex); Serial.print(": ");
        Serial.println(diagnostic.what());
        Serial.println("Recover by asking for an index from 0 through 3.");
    }
    Serial.println("The exception object is a message vocabulary; this sketch does not throw.");
}

void loop() {}
