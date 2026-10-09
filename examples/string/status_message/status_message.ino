#include <CPSTL.h>


/*
  Goal: Text composition: build one readable status line from live values.
  Interfaces: string::operator+=(), to_string(), c_str().
  Observe: Serial receives the composed C string only at the output boundary.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    const int channel = 2;
    const int millivolts = 3712;
    cpstd::string status("Channel ");
    status += cpstd::to_string(channel);
    status += " is ready; battery=";
    status += cpstd::to_string(millivolts);
    status += " mV";
    Serial.println(status.c_str());
    Serial.println("String += composes readable telemetry; c_str() passes it to Serial.");
}

void loop() {}
