#include <CPstring>
#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> log;
    log.reserve(4);
    const cpstd::size_t capacity = log.capacity();
    for (int sample = 0; sample < 4; ++sample) {
        log.push_back(sample * 10);
    }

    cpstd::string message("Recorded ");
    message += cpstd::to_string(static_cast<int>(log.size()));
    message += " samples without growing storage.";
    printf("%s\n", message.c_str());
    printf("Capacity: %u\n", static_cast<unsigned>(capacity));
    return 0;
}
