#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    cpstd::string status("Channel ");
    status += cpstd::to_string(2);
    status += " is ready";
    Serial.println(status.c_str());
}

void loop() {}
