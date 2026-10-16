#include <CPSTL.h>
#include <stdio.h>

// Extend a C major chord with an octave.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    printf("%s: ", label);
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        printf(i == 0 ? "%d" : ", %d", values[i]);
    }
    printf("\n");
}

int main() {
    printf("Extend a C major chord with an octave.\n");
    cpstd::vector<int> notes = {60, 64, 67};
    if (notes.size() != 3) { printf("Not enough memory for the chord.\n"); return 1; }
    notes.reserve(4);
    if (notes.capacity() < 4) { printf("Not enough memory to extend the chord.\n"); return 1; }
    PrintValues("Initial C major MIDI notes", notes);
    notes.push_back(72);
    PrintValues("After push_back(72), adding the octave", notes);
    printf("Notes in the final chord: %ld\n", static_cast<long>(notes.size()));
    printf("These are MIDI note numbers; this example prints them and does not play audio.\n");
    return 0;
}
