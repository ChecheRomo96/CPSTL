#include <CPalgorithm>
#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> readings;
    readings.push_back(18);
    readings.push_back(24);
    readings.push_back(31);
    const cpstd::vector<int>::iterator found = cpstd::find(readings.begin(), readings.end(), 24);
    printf("Selected reading at index: %ld\n", static_cast<long>(found - readings.begin()));
    return 0;
}
