#include <CPSTL.h>


/*
  Goal: LIFO history: undo the most recently recorded setting first.
  Interfaces: stack::push(), top(), pop(), empty().
  Observe: The last brightness value is restored first.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::stack<int> undo;
    undo.push(10); // brightness was 10
    undo.push(20); // user changed it to 20
    undo.push(40); // then to 40
    Serial.println("Undo returns changes in reverse order:");
    while (!undo.empty()) {
        Serial.print("Restore brightness "); Serial.println(undo.top());
        undo.pop();
    }
    Serial.println("Always check empty() before top() or pop().");
}

void loop() {}
