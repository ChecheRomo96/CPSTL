#include <CPSTL.h>
#include <CPstack.h>

// Restore previous brightness settings in reverse order (LIFO).
void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Restore previous brightness settings in reverse order (LIFO).");
    cpstd::stack<int> undo;
    int brightness = 10;
    Serial.print("Initial brightness: "); Serial.println(static_cast<long>(brightness));
    const int changes[] = {20, 40};
    for (cpstd::size_t i = 0; i < sizeof(changes) / sizeof(changes[0]); ++i) {
        const cpstd::size_t before = undo.size();
        undo.push(brightness);
        if (undo.size() != before + 1) { Serial.println("Not enough memory to save undo history."); return; }
        brightness = changes[i];
        Serial.print("Changed brightness to: "); Serial.println(static_cast<long>(brightness));
    }
    Serial.println("Undo saves the previous setting before each edit.");
    while (!undo.empty()) {
        brightness = undo.top();
        undo.pop();
        Serial.print("Undo restored brightness: "); Serial.println(static_cast<long>(brightness));
        Serial.print("  Remaining undo entries: "); Serial.println(static_cast<long>(undo.size()));
    }
    Serial.println("No older setting remains; top() is never called on an empty stack.");
}

void loop() {}
