#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::queue<int> messages;
    messages.push(101);
    messages.push(102);
    Serial.print("Processing message: ");
    Serial.println(messages.front());
    messages.pop();
    Serial.print("Next message: ");
    Serial.println(messages.front());
}

void loop() {}
