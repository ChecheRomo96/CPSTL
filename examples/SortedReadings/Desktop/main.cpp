#include <CPalgorithm>
#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> readings;
    readings.reserve(5);
    readings.push_back(42);
    readings.push_back(18);
    readings.push_back(31);
    readings.push_back(18);
    readings.push_back(27);
    cpstd::sort(readings.begin(), readings.end());

    printf("Sorted readings: ");
    for (cpstd::size_t index = 0; index < readings.size(); ++index) {
        printf(index == 0 ? "%d" : ", %d", readings[index]);
    }
    printf("\n");
    return 0;
}
