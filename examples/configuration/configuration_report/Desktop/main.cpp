// Prints how this CPSTL build is configured.

#include <CPSTL.h>

#include <stdio.h>

int main() {
    printf("CPSTL %s, C++ %ld\n", CPSTL_VERSION, static_cast<long>(CPSTL_CPLUSPLUS));

#if defined(CPSTL_USING_STL)
    printf("Mode ........... STL (cpstd names alias std)\n");
#else
    printf("Mode ........... CPSTL implementation\n");
#endif

#if defined(CPSTL_USING_C_ALLOCATION)
    printf("Allocation ..... C (malloc/free)\n");
#elif defined(CPSTL_USING_CPP_ALLOCATION)
    printf("Allocation ..... C++ (operator new, nothrow)\n");
#else
    printf("Allocation ..... std::allocator\n");
#endif

#if defined(CPSTL_VECTOR_ENABLED)
    printf("cpstd::vector .. enabled\n");
#endif
#if defined(CPSTL_STRING_ENABLED)
    printf("cpstd::string .. enabled\n");
#endif

    printf("Byte maximum ... %u\n",
           static_cast<unsigned>(cpstd::numeric_limits<unsigned char>::max()));
    return 0;
}
