#include <CPutility.h>

#include <stdio.h>

int main() {
    int activeChannel = 1;
    int previousChannel = cpstd::exchange(activeChannel, 2);
    cpstd::swap(activeChannel, previousChannel);
    printf("Active channel: %d, previous channel: %d\n", activeChannel, previousChannel);
    return 0;
}
