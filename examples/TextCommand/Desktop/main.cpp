#include <CPstring>

#include <stdio.h>

int main() {
    const cpstd::string command("tempo=120");
    const cpstd::size_t separator = command.find('=');
    const cpstd::string name = command.substr(0, separator);
    const int value = cpstd::stoi(command.substr(separator + 1));

    printf("Command: %s, value: %d\n", name.c_str(), value);
    return 0;
}
