#include <CPSTL.h>

// Parse complete integer commands and explain rejected input.
void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Parse complete integer commands and explain rejected input.");
    const cpstd::string commands[] = {"tempo=120", "transpose=-2", "broken", "=120", "tempo=", "tempo=fast", "tempo=12x"};
    for (cpstd::size_t item = 0; item < sizeof(commands) / sizeof(commands[0]); ++item) {
        const cpstd::string& command = commands[item];
        Serial.print("Input: "); Serial.println(command.c_str());
        const cpstd::size_t separator = command.find('=');
        if (separator == cpstd::string::npos) {
            Serial.println("  Rejected: missing '='; expected name=integer.");
            continue;
        }
        if (separator == 0 || separator + 1 == command.size()) {
            Serial.println("  Rejected: both the name and value must be present.");
            continue;
        }
        const cpstd::string name = command.substr(0, separator);
        const cpstd::string text = command.substr(separator + 1);
        cpstd::size_t digit = (text[0] == '-' || text[0] == '+') ? 1 : 0;
        bool valid = digit < text.size();
        for (; digit < text.size(); ++digit) {
            if (text[digit] < '0' || text[digit] > '9') valid = false;
        }
        if (!valid) {
            Serial.println("  Rejected: the whole value must be an integer, with an optional sign.");
            continue;
        }
        // Bound the magnitude before stoi so this works even on 16-bit targets.
        const cpstd::size_t start = (text[0] == '-' || text[0] == '+') ? 1 : 0;
        unsigned int magnitude = 0;
        for (digit = start; digit < text.size(); ++digit) {
            magnitude = magnitude * 10 + static_cast<unsigned int>(text[digit] - '0');
            if (magnitude > 1000) break;
        }
        if (magnitude > 1000) {
            Serial.println("  Rejected: this command accepts values from -1000 through 1000.");
            continue;
        }
        const int value = cpstd::stoi(text);
        Serial.print("  Parsed name: "); Serial.println(name.c_str());
        Serial.print("  Parsed integer value: "); Serial.println(static_cast<long>(value));
    }
    Serial.println("Check structure, digits and the application range before converting with stoi().");
}

void loop() {}
