#include <CPSTL.h>
#include <CPexception.h>

// Reject an invalid sample index and report a recovery action.
void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Reject an invalid sample index and report a recovery action.");
    const int capturedSamples = 4;
    int requestedIndex = 6;
    Serial.print("Captured sample count: "); Serial.println(static_cast<long>(capturedSamples));
    Serial.println("Valid zero-based indices: 0 through 3.");
    Serial.print("Requested index: "); Serial.println(static_cast<long>(requestedIndex));
    if (requestedIndex < 0 || requestedIndex >= capturedSamples) {
        const cpstd::out_of_range diagnostic("requested sample is outside the capture");
        Serial.print("Request rejected: "); Serial.println(diagnostic.what());
        Serial.println("Recovery: request an index from 0 through 3; no buffer access was attempted.");
    }
    Serial.println("The diagnostic object carries a message; this example does not throw an exception.");
}

void loop() {}
