#include <CPSTL.h>


/*
  Goal: Configuration: inspect CPSTL build facts before comparing behaviour across boards.
  Interfaces: CPSTL_VERSION, CPSTL_CPLUSPLUS and cpstd::numeric_limits<T>::max().
  Observe: The serial report identifies the selected implementation and numeric range.
*/
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
    Serial.println("Use this report first after changing a board, compiler, or CPSTL build option.");
    Serial.println("Compare its output with the desktop tutorial before investigating a mismatch.");
}

void loop() {
}
