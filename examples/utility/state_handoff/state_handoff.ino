#include <CPSTL.h>
#include <CPutility.h>

// Replace active state with exchange, then trade values with swap.
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Replace active state with exchange, then trade values with swap.");
    int activeChannel = 1;
    int standbyChannel = 3;
    Serial.print("Initial active channel: "); Serial.println(static_cast<long>(activeChannel));
    Serial.print("Initial standby channel: "); Serial.println(static_cast<long>(standbyChannel));
    const int previousChannel = cpstd::exchange(activeChannel, 2);
    Serial.println("Operation: exchange(activeChannel, 2).");
    Serial.print("  Returned previous channel: "); Serial.println(static_cast<long>(previousChannel));
    Serial.print("  New active channel: "); Serial.println(static_cast<long>(activeChannel));
    Serial.println("Operation: swap(activeChannel, standbyChannel).");
    cpstd::swap(activeChannel, standbyChannel);
    Serial.print("  Active channel after swap: "); Serial.println(static_cast<long>(activeChannel));
    Serial.print("  Standby channel after swap: "); Serial.println(static_cast<long>(standbyChannel));
    Serial.println("exchange replaces one value and returns its old value; swap trades two values.");
}

void loop() {}
