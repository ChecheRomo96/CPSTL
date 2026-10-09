#include <CPlimits.h>

#include <stdio.h>

int main() {
    printf("Unsigned byte range: 0..%u\n", static_cast<unsigned>(cpstd::numeric_limits<unsigned char>::max()));
    return 0;
}
