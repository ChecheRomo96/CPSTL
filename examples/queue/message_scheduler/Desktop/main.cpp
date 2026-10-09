#include <CPqueue.h>

#include <stdio.h>

int main() {
    cpstd::queue<int> messages;
    messages.push(101);
    messages.push(102);
    printf("Processing message: %d\n", messages.front());
    messages.pop();
    printf("Next message: %d\n", messages.front());
    return 0;
}
