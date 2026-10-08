// Verifiable CPSTL container example for Arduino.
// Open the Serial Monitor at 9600 baud. The final line must report PASS.

#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<int> samples;
    samples.reserve(3);
    samples.push_back(4);
    samples.push_back(8);
    samples.push_back(15);

    cpstd::stack<int> history;
    history.push(4);
    history.push(8);
    history.push(15);
    const int historyTop = history.top();
    history.pop();

    cpstd::queue<int> work;
    work.push(16);
    work.push(23);
    work.push(42);
    work.pop();

    cpstd::string label = "samples";
    label += '-';
    label += cpstd::to_string(static_cast<int>(samples.size()));

    const bool passed = samples.size() == 3 && samples[1] == 8 &&
                        historyTop == 15 && history.top() == 8 && history.size() == 2 &&
                        work.front() == 23 && work.back() == 42 && work.size() == 2 &&
                        label == "samples-3";

    Serial.print("vector middle: ");
    Serial.println(samples[1]);
    Serial.print("stack after pop: ");
    Serial.println(history.top());
    Serial.print("queue front/back: ");
    Serial.print(work.front());
    Serial.print('/');
    Serial.println(work.back());
    Serial.print("string: ");
    Serial.println(label.c_str());
    Serial.print("CPSTL Arduino Containers: ");
    Serial.println(passed ? "PASS" : "FAIL");
}

void loop() {
}
