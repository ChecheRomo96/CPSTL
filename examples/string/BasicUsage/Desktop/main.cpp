// cpstd::string: composing text, searching, and converting numbers without
// exceptions.

#include <CPstring>

#include <stdio.h>
#include <string.h>

int main() {
    cpstd::string greeting("Hello");
    greeting += ", ";
    greeting.append("world");
    greeting.push_back('!');
    printf("composed ............ \"%s\"\n", greeting.c_str());

    const cpstd::size_t comma = greeting.find(',');
    const cpstd::string first = greeting.substr(0, comma);
    printf("substr(0, find(',')) \"%s\"\n", first.c_str());

    cpstd::string patch = greeting;
    patch.replace(patch.find("world"), 5, "CPSTL");
    printf("replace ............. \"%s\"\n", patch.c_str());

    const cpstd::string number = cpstd::to_string(-1234);
    const cpstd::string ratio = cpstd::to_string(2.5);
    printf("to_string ........... \"%s\", \"%s\"\n", number.c_str(), ratio.c_str());

    cpstd::size_t used = 0;
    const int parsed = cpstd::stoi(cpstd::string("0x2A rest"), &used, 16);
    printf("stoi(\"0x2A rest\") ... %d (used %u characters)\n", parsed, static_cast<unsigned>(used));

    const bool ok = strcmp(greeting.c_str(), "Hello, world!") == 0 &&
                    strcmp(first.c_str(), "Hello") == 0 &&
                    strcmp(patch.c_str(), "Hello, CPSTL!") == 0 &&
                    strcmp(number.c_str(), "-1234") == 0 &&
                    strcmp(ratio.c_str(), "2.500000") == 0 &&
                    parsed == 42 && used == 4;
    printf("Self-check: %s\n", ok ? "ok" : "FAILED");
    return ok ? 0 : 1;
}
