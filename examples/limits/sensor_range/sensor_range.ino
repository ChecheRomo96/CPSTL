#include <CPSTL.h>
#include <CPlimits.h>


/*
  Goal: Numeric limits: choose a storage type from the actual target range.
  Interfaces: cpstd::numeric_limits<T>::max().
  Observe: The sketch shows why an ADC value may not fit in an unsigned byte.
*/
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    const int reading = 300;
    const int byteMaximum = cpstd::numeric_limits<unsigned char>::max();
    Serial.print("A byte stores 0.."); Serial.println(byteMaximum);
    Serial.print("Reading "); Serial.print(reading);
    Serial.println(reading > byteMaximum ? " needs a wider type." : " fits in a byte.");
    Serial.print("int maximum on this target: ");
    Serial.println(cpstd::numeric_limits<int>::max());
    Serial.println("numeric_limits documents the real target range instead of assuming it.");
}

void loop() {}
