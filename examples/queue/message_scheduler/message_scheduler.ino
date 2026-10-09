#include <CPSTL.h>


/*
  Goal: FIFO scheduling: process events in exactly their arrival order.
  Interfaces: queue::push(), front(), pop(), empty().
  Observe: The earliest message leaves the queue first.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::queue<int> messages;
    messages.push(101); // a sensor reported first
    messages.push(205); // then a button did
    messages.push(112);
    Serial.println("FIFO dispatcher:");
    while (!messages.empty()) {
        Serial.print("Processing message "); Serial.print(messages.front());
        Serial.print("; waiting="); Serial.println(messages.size() - 1);
        messages.pop();
    }
    Serial.println("queue::front() reads the oldest item; pop() removes it.");
}

void loop() {}
