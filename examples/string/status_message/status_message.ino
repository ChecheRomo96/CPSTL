#include <CPSTL.h>

// Compose a readable status message from simulated telemetry.
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Compose a readable status message from simulated telemetry.");
    const int channel = 2;
    const int millivolts = 3712;
    Serial.print("Simulated channel ID: "); Serial.println(static_cast<long>(channel));
    Serial.print("Simulated battery reading (mV): "); Serial.println(static_cast<long>(millivolts));
    cpstd::string status("Channel ");
    status += cpstd::to_string(channel);
    status += " is ready; battery=";
    status += cpstd::to_string(millivolts);
    status += " mV";
    Serial.print("Composed status: "); Serial.println(status.c_str());
    Serial.print("Message length (characters): "); Serial.println(static_cast<long>(status.size()));
    Serial.println("operator+= joins the text and numeric fields; c_str() supplies the printable string.");
}

void loop() {}
