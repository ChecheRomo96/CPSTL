#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::stack<int> undo;
    undo.push(10);
    undo.push(20);
    Serial.print("Undo action: ");
    Serial.println(undo.top());
    undo.pop();
    Serial.print("Current action: ");
    Serial.println(undo.top());
}

void loop() {}
