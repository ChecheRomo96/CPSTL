#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> samples;
    samples.reserve(8);
    samples.push_back(12);
    samples.push_back(15);
    printf("Samples: %lu, reserved slots: %lu\n", static_cast<unsigned long>(samples.size()),
           static_cast<unsigned long>(samples.capacity()));
    return 0;
}
