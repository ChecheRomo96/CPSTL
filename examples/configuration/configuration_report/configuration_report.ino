#include <CPSTL.h>


/*
  Goal: Configuration: inspect CPSTL build facts before comparing behaviour across boards.
  Interfaces: CPSTL_VERSION, CPSTL_CPLUSPLUS and cpstd::numeric_limits<T>::max().
  Observe: The serial report identifies the selected implementation and numeric range.
*/
void setup() {
    Serial.begin(115200);
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
#if defined(CPSTL_USING_C_ALLOCATION)
    Serial.println("Allocation: C (malloc/free)");
#elif defined(CPSTL_USING_CPP_ALLOCATION)
    Serial.println("Allocation: C++ (operator new, nothrow)");
#else
    Serial.println("Allocation: std::allocator");
#endif
#if defined(CPSTL_VECTOR_ENABLED)
    Serial.println("cpstd::vector: enabled");
#else
    Serial.println("cpstd::vector: disabled");
#endif
#if defined(CPSTL_STRING_ENABLED)
    Serial.println("cpstd::string: enabled");
#else
    Serial.println("cpstd::string: disabled");
#endif
    Serial.print("Unsigned byte maximum: ");
    Serial.println(cpstd::numeric_limits<unsigned char>::max());
    Serial.println("Use this report first after changing a board, compiler, or CPSTL build option.");
    Serial.println("Compare its output with the desktop tutorial before investigating a mismatch.");
}

void loop() {
}
