#ifndef CPSTL_BUILD_SETTINGS_H
#define CPSTL_BUILD_SETTINGS_H

    #if defined(_MSC_VER) && defined(_MSVC_LANG)
        #define CPSTL_CPLUSPLUS _MSVC_LANG
    #else
        #define CPSTL_CPLUSPLUS __cplusplus
    #endif

    #if CPSTL_CPLUSPLUS < 201103L
        #error "CPSTL requires C++11 or newer"
    #endif

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CPSTL Version

        #ifndef CPSTL_VERSION
            #define CPSTL_VERSION "1.1.3"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // IDE-driven builds (no CMake): pick modules and allocation in CPSTL_UserSetup.h

        #if defined(ARDUINO)
            #include <Arduino.h>
            #include "CPSTL_UserSetup.h"
        #endif

        #if defined(PSOC_CREATOR)
            #include "CPSTL_UserSetup.h"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Platform helpers

        #if defined(__AVR__) || defined(__avr__)
            #include <avr/pgmspace.h>
            #ifndef PROGMEM_MACRO
                #define PROGMEM_MACRO PROGMEM
            #endif
        #else
            #ifndef PROGMEM_MACRO
                #define PROGMEM_MACRO
            #endif
        #endif

        #ifndef INLINE_MACRO
            #define INLINE_MACRO
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // STL mode
    //
    // CPSTL_USING_STL turns every cpstd facility into an alias of its std
    // counterpart. It requires a hosted standard library, so it is rejected on
    // AVR, whose toolchain ships none.

        #if defined(CPSTL_USING_STL) && (defined(__AVR__) || defined(__avr__))
            #error "CPSTL_USING_STL needs a C++ standard library, which AVR-GCC does not provide"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Allocation mode used by cpstd::allocator (one of the three)
    //
    //   CPSTL_USING_C_ALLOCATION    malloc/free; works without operator new (AVR)
    //   CPSTL_USING_CPP_ALLOCATION  ::operator new(nothrow)/::operator delete
    //   CPSTL_USING_STD_ALLOCATION  std::allocator (hosted targets only)
    //
    // When none is chosen, use C allocation so freestanding targets need no
    // C++ runtime. STL mode always uses std::allocator.

        #if defined(CPSTL_USING_STL) && !defined(CPSTL_USING_STD_ALLOCATION)
            #undef CPSTL_USING_C_ALLOCATION
            #undef CPSTL_USING_CPP_ALLOCATION
            #define CPSTL_USING_STD_ALLOCATION
        #endif

        #if !defined(CPSTL_USING_C_ALLOCATION) && \
            !defined(CPSTL_USING_CPP_ALLOCATION) && \
            !defined(CPSTL_USING_STD_ALLOCATION)
            #define CPSTL_USING_C_ALLOCATION
        #endif

        #if (defined(CPSTL_USING_C_ALLOCATION) + defined(CPSTL_USING_CPP_ALLOCATION) + \
             defined(CPSTL_USING_STD_ALLOCATION)) != 1
            #error "Define exactly one of CPSTL_USING_C_ALLOCATION, CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_STD_ALLOCATION"
        #endif

        #if defined(CPSTL_USING_STD_ALLOCATION) && (defined(__AVR__) || defined(__avr__))
            #error "CPSTL_USING_STD_ALLOCATION needs std::allocator, which AVR-GCC does not provide"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Exceptions
    //
    // Without CPSTL_EXCEPTIONS_ENABLED, an allocation failure leaves the
    // container unchanged (see each container's documentation) instead of
    // throwing.

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif//CPSTL_BUILD_SETTINGS_H
