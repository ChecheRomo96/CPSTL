#include <CPSTL.h>

// Extend a C major chord with an octave.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    Serial.print(label); Serial.print(": ");
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        if (i != 0) Serial.print(", ");
        Serial.print(values[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Extend a C major chord with an octave.");
    cpstd::vector<int> notes = {60, 64, 67};
    if (notes.size() != 3) { Serial.println("Not enough memory for the chord."); return; }
    notes.reserve(4);
    if (notes.capacity() < 4) { Serial.println("Not enough memory to extend the chord."); return; }
    PrintValues("Initial C major MIDI notes", notes);
    notes.push_back(72);
    PrintValues("After push_back(72), adding the octave", notes);
    Serial.print("Notes in the final chord: "); Serial.println(static_cast<long>(notes.size()));
    Serial.println("These are MIDI note numbers; this example prints them and does not play audio.");
}

void loop() {}
