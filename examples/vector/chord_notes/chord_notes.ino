#include <CPSTL.h>


/*
  Goal: Growable sequence: represent and extend a musical chord.
  Interfaces: vector initializer-list constructor, push_back(), size(), operator[].
  Observe: The initial three-note chord becomes a four-note voicing.
*/
void PrintChord(const cpstd::vector<int>& notes) {
    for (cpstd::size_t index = 0; index < notes.size(); ++index) {
        Serial.print(index == 0 ? "" : ", ");
        Serial.print(notes[index]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    // An initializer list makes a fixed musical idea readable at its source.
    cpstd::vector<int> cMajor = {60, 64, 67};
    Serial.println("C major (MIDI notes):");
    PrintChord(cMajor);

    // The collection is still editable after construction.
    cMajor.push_back(72);
    Serial.println("Add the octave for a four-note voicing:");
    PrintChord(cMajor);
    Serial.println("Change the literals above, upload, and hear/inspect the notes.");
}

void loop() {}
