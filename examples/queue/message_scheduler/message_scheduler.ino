#include <CPSTL.h>
#include <CPqueue.h>

// Process messages in arrival order (FIFO).
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Process messages in arrival order (FIFO).");
    cpstd::queue<int> messages;
    const int arrivals[] = {101, 205, 112};
    Serial.println("Incoming message IDs: 101, 205, 112.");
    for (cpstd::size_t i = 0; i < sizeof(arrivals) / sizeof(arrivals[0]); ++i) {
        const cpstd::size_t before = messages.size();
        messages.push(arrivals[i]);
        if (messages.size() != before + 1) { Serial.println("Not enough memory to enqueue a message."); return; }
    }
    Serial.println("Processing the oldest waiting message first:");
    while (!messages.empty()) {
        Serial.print("  Processing message ID: "); Serial.println(static_cast<long>(messages.front()));
        messages.pop();
        Serial.print("  Messages still waiting: "); Serial.println(static_cast<long>(messages.size()));
    }
    Serial.print("Queue empty after processing: "); Serial.println(messages.empty() ? "yes" : "no");
}

void loop() {}
