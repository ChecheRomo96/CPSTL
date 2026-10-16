#include <CPSTL.h>
#include <stdio.h>

// Reserve storage before an eight-sample capture.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    printf("%s: ", label);
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        printf(i == 0 ? "%d" : ", %d", values[i]);
    }
    printf("\n");
}

int main() {
    printf("Reserve storage before an eight-sample capture.\n");
    cpstd::vector<int> samples;
    const cpstd::size_t captureBudget = 8;
    printf("Before reserve, size: %ld\n", static_cast<long>(samples.size()));
    printf("Before reserve, capacity: %ld\n", static_cast<long>(samples.capacity()));
    samples.reserve(captureBudget);
    if (samples.capacity() < captureBudget) { printf("Not enough memory for the capture budget.\n"); return 1; }
    const cpstd::size_t reserved = samples.capacity();
    printf("After reserve(8), size: %ld\n", static_cast<long>(samples.size()));
    printf("After reserve(8), capacity: %ld\n", static_cast<long>(reserved));
    printf("reserve() allocates space but does not create samples.\n");
    for (int sample = 0; sample < 8; ++sample) {
        const int reading = 100 + sample * 3;
        samples.push_back(reading);
        printf("Captured reading: %ld\n", static_cast<long>(reading));
        printf("  Stored samples: %ld\n", static_cast<long>(samples.size()));
        printf("  Available capacity: %ld\n", static_cast<long>(samples.capacity()));
    }
    PrintValues("Completed capture", samples);
    printf("Capacity unchanged during capture: %s\n", samples.capacity() == reserved ? "yes" : "no");
    return 0;
}
