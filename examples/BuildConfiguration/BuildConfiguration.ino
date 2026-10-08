#include <CPSTL.h>

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }

    Serial.print("CPSTL version: ");
    Serial.println(CPSTL_VERSION);
    Serial.print("C++ language value: ");
    Serial.println(static_cast<long>(CPSTL_CPLUSPLUS));
#if defined(CPSTL_USING_STL)
    Serial.println("Vocabulary: standard library aliases");
#else
    Serial.println("Vocabulary: CPSTL portable implementation");
#endif
    Serial.print("Unsigned byte maximum: ");
    Serial.println(cpstd::numeric_limits<unsigned char>::max());
}

void loop() {
}
