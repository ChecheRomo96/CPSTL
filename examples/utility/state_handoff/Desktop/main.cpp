#include <CPSTL.h>
#include <CPutility.h>
#include <stdio.h>

// Replace active state with exchange, then trade values with swap.
int main() {
    printf("Replace active state with exchange, then trade values with swap.\n");
    int activeChannel = 1;
    int standbyChannel = 3;
    printf("Initial active channel: %ld\n", static_cast<long>(activeChannel));
    printf("Initial standby channel: %ld\n", static_cast<long>(standbyChannel));
    const int previousChannel = cpstd::exchange(activeChannel, 2);
    printf("Operation: exchange(activeChannel, 2).\n");
    printf("  Returned previous channel: %ld\n", static_cast<long>(previousChannel));
    printf("  New active channel: %ld\n", static_cast<long>(activeChannel));
    printf("Operation: swap(activeChannel, standbyChannel).\n");
    cpstd::swap(activeChannel, standbyChannel);
    printf("  Active channel after swap: %ld\n", static_cast<long>(activeChannel));
    printf("  Standby channel after swap: %ld\n", static_cast<long>(standbyChannel));
    printf("exchange replaces one value and returns its old value; swap trades two values.\n");
    return 0;
}
