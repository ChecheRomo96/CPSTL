#include <CPSTL.h>
#include <stdio.h>

// Compose a readable status message from simulated telemetry.
int main() {
    printf("Compose a readable status message from simulated telemetry.\n");
    const int channel = 2;
    const int millivolts = 3712;
    printf("Simulated channel ID: %ld\n", static_cast<long>(channel));
    printf("Simulated battery reading (mV): %ld\n", static_cast<long>(millivolts));
    cpstd::string status("Channel ");
    status += cpstd::to_string(channel);
    status += " is ready; battery=";
    status += cpstd::to_string(millivolts);
    status += " mV";
    printf("Composed status: %s\n", status.c_str());
    printf("Message length (characters): %ld\n", static_cast<long>(status.size()));
    printf("operator+= joins the text and numeric fields; c_str() supplies the printable string.\n");
    return 0;
}
