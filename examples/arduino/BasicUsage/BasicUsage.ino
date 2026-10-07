// CPSTL on an Arduino board: cpstd::vector, cpstd::string, cpstd::sort and
// cpstd::function with the same interface as std. Open the Serial Monitor at
// 9600 baud to see the results.
//
// On AVR boards CPSTL allocates with malloc and never throws: when memory runs
// out, an operation has no effect and the container stays as it was.

#include <CPSTL.h>

namespace {
    bool Descending(int a, int b) { return a > b; }

    void PrintVector(const char* label, const cpstd::vector<int>& values) {
        Serial.print(label);
        for (cpstd::size_t i = 0; i < values.size(); ++i) {
            Serial.print(i == 0 ? " " : ", ");
            Serial.print(values[i]);
        }
        Serial.println();
    }
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<int> steps = {3, 1, 4, 1, 5};
    steps.push_back(9);
    steps.insert(steps.begin() + 2, 2);
    PrintVector("vector:", steps);

    cpstd::sort(steps.begin(), steps.end());
    PrintVector("sorted:", steps);
    cpstd::sort(steps.begin(), steps.end(), Descending);
    PrintVector("descending:", steps);

    cpstd::string name = "pattern";
    name += '-';
    name += cpstd::to_string(static_cast<int>(steps.size()));
    Serial.print("string: ");
    Serial.println(name.c_str());

    int total = 0;
    cpstd::function<void(int)> accumulate = [&total](int value) { total += value; };
    for (cpstd::size_t i = 0; i < steps.size(); ++i) {
        accumulate(steps[i]);
    }
    Serial.print("sum via cpstd::function: ");
    Serial.println(total);

    const bool passed = steps.size() == 7 && steps[0] == 9 &&
                        steps[6] == 1 && name == "pattern-7" && total == 25;
    Serial.print("CPSTL hardware smoke: ");
    Serial.println(passed ? "PASS" : "FAIL");
}

void loop() {
}
