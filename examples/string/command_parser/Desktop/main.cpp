#include <CPSTL.h>
#include <stdio.h>

// Parse complete integer commands and explain rejected input.
int main() {
    printf("Parse complete integer commands and explain rejected input.\n");
    const cpstd::string commands[] = {"tempo=120", "transpose=-2", "broken", "=120", "tempo=", "tempo=fast", "tempo=12x"};
    for (cpstd::size_t item = 0; item < sizeof(commands) / sizeof(commands[0]); ++item) {
        const cpstd::string& command = commands[item];
        printf("Input: %s\n", command.c_str());
        const cpstd::size_t separator = command.find('=');
        if (separator == cpstd::string::npos) {
            printf("  Rejected: missing '='; expected name=integer.\n");
            continue;
        }
        if (separator == 0 || separator + 1 == command.size()) {
            printf("  Rejected: both the name and value must be present.\n");
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
            printf("  Rejected: the whole value must be an integer, with an optional sign.\n");
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
            printf("  Rejected: this command accepts values from -1000 through 1000.\n");
            continue;
        }
        const int value = cpstd::stoi(text);
        printf("  Parsed name: %s\n", name.c_str());
        printf("  Parsed integer value: %ld\n", static_cast<long>(value));
    }
    printf("Check structure, digits and the application range before converting with stoi().\n");
    return 0;
}
