#include <CPalgorithm>
#include <CPvector>

#include <stdio.h>

int main() {
    printf("Measurement lookup: find the first exact match.\n");
    cpstd::vector<int> readings;
    const int session[] = {18, 24, 31, 18, 27};
    const cpstd::size_t sampleCount = sizeof(session) / sizeof(session[0]);
    readings.reserve(sampleCount);
    if (readings.capacity() < sampleCount) {
        printf("Not enough memory to store the session.\n");
        return 1;
    }
    printf("Session: ");
    for (cpstd::size_t index = 0; index < sampleCount; ++index) {
        readings.push_back(session[index]);
        if (index != 0) printf(", ");
        printf("%d", session[index]);
    }
    printf("\n");

    const int targetReading = 31;
    const cpstd::vector<int>::iterator found =
        cpstd::find(readings.begin(), readings.end(), targetReading);
    printf("Looking for exact reading: %d\n", targetReading);
    if (found == readings.end()) {
        printf("No matching reading in this session.\n");
    } else {
        printf("Matched reading: %d\n", *found);
        printf("Index (zero-based): %ld\n",
               static_cast<long>(found - readings.begin()));
        printf("Sample number (one-based): %ld\n",
               static_cast<long>(found - readings.begin()) + 1);
    }
    printf("find() stops at the first exact match; end() means no match.\n");
    printf("Try 18 for the first match, or 99 for no match.\n");
    return 0;
}
