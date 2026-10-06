// cpstd::sort on arrays and vectors, with and without a comparator.

#include <CPalgorithm>
#include <CPvector>

#include <stdio.h>

namespace {
    struct Note {
        const char* name;
        int midi;
    };

    struct ByPitch {
        bool operator()(const Note& a, const Note& b) const { return a.midi < b.midi; }
    };
}

int main() {
    int values[] = {42, 7, 19, 7, 3, 88, 0};
    const int count = static_cast<int>(sizeof(values) / sizeof(values[0]));
    cpstd::sort(values, values + count);
    printf("ascending ints:");
    for (int i = 0; i < count; ++i) {
        printf(" %d", values[i]);
    }
    printf("\n");

    cpstd::vector<Note> chord;
    chord.push_back(Note{"G4", 67});
    chord.push_back(Note{"C4", 60});
    chord.push_back(Note{"E4", 64});
    cpstd::sort(chord.begin(), chord.end(), ByPitch());
    printf("chord by pitch:");
    for (cpstd::size_t i = 0; i < chord.size(); ++i) {
        printf(" %s", chord[i].name);
    }
    printf("\n");

    bool ok = chord[0].midi == 60 && chord[2].midi == 67;
    for (int i = 1; i < count; ++i) {
        ok = ok && values[i - 1] <= values[i];
    }
    printf("smallest/largest: %d / %d\n", cpstd::min(values[0], values[count - 1]),
           cpstd::max(values[0], values[count - 1]));
    printf("Self-check: %s\n", ok ? "ok" : "FAILED");
    return ok ? 0 : 1;
}
