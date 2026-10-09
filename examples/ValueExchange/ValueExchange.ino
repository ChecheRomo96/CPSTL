#include <CPSTL.h>
#include <CPutility.h>

void setup() {
    Serial.begin(9600);
    int activeChannel = 1;
    int previousChannel = cpstd::exchange(activeChannel, 2);
    cpstd::swap(activeChannel, previousChannel);
    Serial.print("Active channel: ");
    Serial.print(activeChannel);
    Serial.print(", previous channel: ");
    Serial.println(previousChannel);
}

void loop() {}
