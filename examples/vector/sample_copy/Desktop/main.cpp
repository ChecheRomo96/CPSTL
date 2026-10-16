#include <CPSTL.h>
#include <stdio.h>

// Copy a packet into an independent log.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    printf("%s: ", label);
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        printf(i == 0 ? "%d" : ", %d", values[i]);
    }
    printf("\n");
}

int main() {
    printf("Copy a packet into an independent log.\n");
    cpstd::vector<int> source = {3, 5, 8};
    if (source.size() != 3) { printf("Not enough memory for the packet.\n"); return 1; }
    cpstd::vector<int> destination;
    destination.reserve(source.size());
    if (destination.capacity() < source.size()) { printf("Not enough memory for the log.\n"); return 1; }
    PrintValues("Source packet", source);
    printf("Destination size before copy: %ld\n", static_cast<long>(destination.size()));
    cpstd::copy(source.begin(), source.end(), cpstd::back_inserter(destination));
    PrintValues("Destination after copy with back_inserter", destination);
    destination[0] = 99;
    PrintValues("Destination after changing its first sample to 99", destination);
    PrintValues("Source packet remains unchanged", source);
    printf("The copied vector owns independent storage.\n");
    return 0;
}
