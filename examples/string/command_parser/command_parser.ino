#include <CPSTL.h>


/*
  Goal: Text parsing: turn a serial-style name=value command into fields safely.
  Interfaces: string::find(), npos, substr(), stoi().
  Observe: Malformed input is rejected before the string is sliced.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    const cpstd::string commands[] = {"tempo=120", "transpose=-2", "broken"};
    for (cpstd::size_t item = 0; item < 3; ++item) {
        const cpstd::string& command = commands[item];
        const cpstd::size_t separator = command.find('=');
        Serial.print("Input: "); Serial.println(command.c_str());
        if (separator == cpstd::string::npos) {
            Serial.println("  rejected: expected name=value");
            continue;
        }
        const cpstd::string name = command.substr(0, separator);
        const int value = cpstd::stoi(command.substr(separator + 1));
        Serial.print("  name="); Serial.print(name.c_str());
        Serial.print(", value="); Serial.println(value);
    }
    Serial.println("find() validates the separator before substr() slices the command.");
}

void loop() {
}
