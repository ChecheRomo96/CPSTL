#include <CPSTL.h>
#include <CPqueue.h>
#include <stdio.h>

// Process messages in arrival order (FIFO).
int main() {
    printf("Process messages in arrival order (FIFO).\n");
    cpstd::queue<int> messages;
    const int arrivals[] = {101, 205, 112};
    printf("Incoming message IDs: 101, 205, 112.\n");
    for (cpstd::size_t i = 0; i < sizeof(arrivals) / sizeof(arrivals[0]); ++i) {
        const cpstd::size_t before = messages.size();
        messages.push(arrivals[i]);
        if (messages.size() != before + 1) { printf("Not enough memory to enqueue a message.\n"); return 1; }
    }
    printf("Processing the oldest waiting message first:\n");
    while (!messages.empty()) {
        printf("  Processing message ID: %ld\n", static_cast<long>(messages.front()));
        messages.pop();
        printf("  Messages still waiting: %ld\n", static_cast<long>(messages.size()));
    }
    printf("Queue empty after processing: %s\n", messages.empty() ? "yes" : "no");
    return 0;
}
