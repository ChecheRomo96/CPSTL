#include <CPinitializer_list.h>
#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> chord = {60, 64, 67};
    printf("Chord notes: %lu\n", static_cast<unsigned long>(chord.size()));
    return 0;
}
