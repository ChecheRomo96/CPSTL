#include <CPSTL.h>
#include <CPexception.h>

void setup() {
    Serial.begin(9600);
    const cpstd::out_of_range diagnostic("sample index is outside the buffer");
    Serial.print("Diagnostic: ");
    Serial.println(diagnostic.what());
}

void loop() {}
