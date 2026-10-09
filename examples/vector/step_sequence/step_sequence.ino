#include <CPSTL.h>


/*
  Goal: Sequence editing: insert and erase control steps by position.
  Interfaces: vector::insert(), erase(), begin(), operator[].
  Observe: The serial trace makes each program edit visible.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    cpstd::vector<int> steps;
    steps.push_back(10); // warm-up
    steps.push_back(30); // run
    Serial.println("Original program: 10, 30");
    steps.insert(steps.begin() + 1, 20); // add calibration before run
    Serial.println("Insert calibration at position 1: 10, 20, 30");
    steps.erase(steps.begin()); // skip warm-up after the machine is ready
    Serial.print("Run now executes: ");
    for (cpstd::size_t index = 0; index < steps.size(); ++index) {
        Serial.print(index == 0 ? "" : ", "); Serial.print(steps[index]);
    }
    Serial.println("\ninsert/erase use iterators that name a position in the sequence.");
}

void loop() {}
