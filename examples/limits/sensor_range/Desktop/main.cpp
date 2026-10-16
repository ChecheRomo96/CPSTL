#include <CPSTL.h>
#include <CPlimits.h>
#include <stdio.h>

// Check whether a simulated ADC reading fits its storage type.
int main() {
    printf("Check whether a simulated ADC reading fits its storage type.\n");
    const int reading = 300;
    const int byteMaximum = cpstd::numeric_limits<unsigned char>::max();
    printf("Candidate storage: unsigned char, minimum 0.\n");
    printf("Maximum value for that type: %ld\n", static_cast<long>(byteMaximum));
    printf("Simulated ADC reading: %ld\n", static_cast<long>(reading));
    printf("Does the reading fit? %s\n", reading <= byteMaximum ? "yes" : "no");
    printf("Maximum int on this target: %ld\n", static_cast<long>(cpstd::numeric_limits<int>::max()));
    printf("Check the range before converting; choose a wider type when the reading does not fit.\n");
    return 0;
}
