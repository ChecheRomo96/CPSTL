#include <CPiterator.h>
#include <CPvector>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    const size_t sampleCount = 20;
    cpstd::vector<uint8_t> samples;
    samples.reserve(sampleCount);
    if (samples.capacity() < sampleCount) {
        printf("Not enough memory to capture samples.\n");
        return 1;
    }
    for (size_t i = 0; i < sampleCount; ++i) {
        samples.push_back(static_cast<uint8_t>(rand() % 256));
    }

    printf("Captured samples in time order:\n");
    printf("Forward: ");
    for (cpstd::vector<uint8_t>::iterator it = samples.begin(); it != samples.end(); ++it) {
        printf("%u ", static_cast<unsigned int>(*it));
    }
    printf("\nUndo/playback: ");
    for (cpstd::vector<uint8_t>::reverse_iterator it = samples.rbegin(); it != samples.rend(); ++it) {
        printf("%u ", static_cast<unsigned int>(*it));
    }
    printf("\nReverse iterators start at rbegin() and stop at rend().\n");
    return 0;
}
