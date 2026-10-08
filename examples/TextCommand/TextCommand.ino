#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    const cpstd::string command("tempo=120");
    const cpstd::size_t separator = command.find('=');
    const cpstd::string name = command.substr(0, separator);
    const int value = cpstd::stoi(command.substr(separator + 1));

    Serial.print("Command: ");
    Serial.print(name.c_str());
    Serial.print(", value: ");
    Serial.println(value);
}

void loop() {
}
