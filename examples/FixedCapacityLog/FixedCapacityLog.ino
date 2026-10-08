#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    cpstd::vector<int> log;
    log.reserve(4);
    for (int sample = 0; sample < 4; ++sample) {
        log.push_back(sample * 10);
    }

    cpstd::string message("Recorded ");
    message += cpstd::to_string(static_cast<int>(log.size()));
    message += " samples without growing storage.";
    Serial.println(message.c_str());
}

void loop() {
}
