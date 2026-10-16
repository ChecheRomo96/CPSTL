// Prints how this CPSTL build is configured.

#include <CPSTL.h>

#include <stdio.h>

int main() {
    printf("CPSTL version: %s\nC++ language value: %ld\n", CPSTL_VERSION, static_cast<long>(CPSTL_CPLUSPLUS));

#if defined(CPSTL_USING_STL)
    printf("Vocabulary: standard library aliases\n");
#else
    printf("Vocabulary: CPSTL portable implementation\n");
#endif

#if defined(CPSTL_USING_C_ALLOCATION)
    printf("Allocation: C (malloc/free)\n");
#elif defined(CPSTL_USING_CPP_ALLOCATION)
    printf("Allocation: C++ (operator new, nothrow)\n");
#else
    printf("Allocation: std::allocator\n");
#endif

#if defined(CPSTL_VECTOR_ENABLED)
    printf("cpstd::vector: enabled\n");
#else
    printf("cpstd::vector: disabled\n");
#endif
#if defined(CPSTL_STRING_ENABLED)
    printf("cpstd::string: enabled\n");
#else
    printf("cpstd::string: disabled\n");
#endif

    printf("Unsigned byte maximum: %u\n",
           static_cast<unsigned>(cpstd::numeric_limits<unsigned char>::max()));
    printf("Use this report first after changing a board, compiler, or CPSTL build option.\n");
    printf("Compare its output with the Arduino tutorial before investigating a mismatch.\n");
    return 0;
}
