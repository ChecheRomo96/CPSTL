#ifndef CPSTL_USER_SETUP_H
#define CPSTL_USER_SETUP_H

    // Configuration for IDE builds that do not run CMake (Arduino IDE,
    // PSoC Creator). CMake builds set the same macros from their cache options
    // and never read this file.
    //
    // Modules: comment a line out to leave that container out of CPSTL.h.
    // The stack and queue adapters use cpstd::vector's implementation even
    // when CPSTL_VECTOR_ENABLED is not defined.

        #define CPSTL_VECTOR_ENABLED
        #define CPSTL_STRING_ENABLED
        #define CPSTL_STACK_ENABLED
        #define CPSTL_QUEUE_ENABLED

    // STL mode: forward every cpstd facility to std. Only for boards whose core
    // ships a C++ standard library (ESP32, RP2040 with the mbed core).

        #if defined(ESP32)
            #define CPSTL_USING_STL
        #endif

    // Allocation: leave undefined for the default C allocation (malloc/free,
    // including freestanding targets) or define exactly one of
    // CPSTL_USING_C_ALLOCATION, CPSTL_USING_CPP_ALLOCATION,
    // CPSTL_USING_STD_ALLOCATION.

#endif//CPSTL_USER_SETUP_H
