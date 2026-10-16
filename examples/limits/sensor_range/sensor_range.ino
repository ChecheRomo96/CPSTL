#include <CPSTL.h>
#include <CPlimits.h>

// Check whether a simulated ADC reading fits its storage type.
void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Check whether a simulated ADC reading fits its storage type.");
    const int reading = 300;
    const int byteMaximum = cpstd::numeric_limits<unsigned char>::max();
    Serial.println("Candidate storage: unsigned char, minimum 0.");
    Serial.print("Maximum value for that type: "); Serial.println(static_cast<long>(byteMaximum));
    Serial.print("Simulated ADC reading: "); Serial.println(static_cast<long>(reading));
    Serial.print("Does the reading fit? "); Serial.println(reading <= byteMaximum ? "yes" : "no");
    Serial.print("Maximum int on this target: "); Serial.println(static_cast<long>(cpstd::numeric_limits<int>::max()));
    Serial.println("Check the range before converting; choose a wider type when the reading does not fit.");
}

void loop() {}
