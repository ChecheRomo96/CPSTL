#include <CPSTL.h>
#include <CPutility.h>


/*
  Goal: State transitions: replace or exchange channel values without ad-hoc temporaries.
  Interfaces: exchange() and swap().
  Observe: The output distinguishes replacement-with-history from an exchange.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    int activeChannel = 1;
    int previousChannel = cpstd::exchange(activeChannel, 2);
    Serial.print("Switch 1 -> 2. exchange() returned "); Serial.println(previousChannel);
    int standbyChannel = 3;
    cpstd::swap(activeChannel, standbyChannel);
    Serial.print("swap(active, standby): active="); Serial.print(activeChannel);
    Serial.print(", standby="); Serial.println(standbyChannel);
    Serial.println("exchange replaces and returns; swap exchanges two existing values.");
}

void loop() {}
