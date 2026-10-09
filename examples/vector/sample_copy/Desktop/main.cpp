#include <CPalgorithm>
#include <CPiterator.h>
#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> source;
    source.push_back(3);
    source.push_back(5);
    cpstd::vector<int> destination;
    cpstd::copy(source.begin(), source.end(), cpstd::back_inserter(destination));
    printf("Copied samples: %lu\n", static_cast<unsigned long>(destination.size()));
    return 0;
}
