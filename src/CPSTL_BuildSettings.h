#ifndef CPSTL_BUILD_SETTINGS_H
#define CPSTL_BUILD_SETTINGS_H

    #if defined(_MSC_VER) && defined(_MSVC_LANG)
        #define CPSTL_CPLUSPLUS _MSVC_LANG
    #else
        #define CPSTL_CPLUSPLUS __cplusplus
    #endif


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CPSTL Version

        #ifndef CPSTL_VERSION
            #define CPSTL_VERSION "1.0.0"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Arduino IDE

        #if defined(ARDUINO)
            #include <Arduino.h>
            #include "CPSTL_UserSetup.h"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PSoC Creator

        #if defined(PSOC_CREATOR)
            #include "CPSTL_UserSetup.h"
        #endif

    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // AVR

        #if defined(__AVR__) || defined(__avr__)

            #include <avr/pgmspace.h>
            #include <stdarg.h>

            #ifndef PROGMEM_MACRO
                #define PROGMEM_MACRO PROGMEM
            #endif

            #if defined(CPSTL_VECTOR_ENABLED)

                // AVR: default vector allocation mode -> C allocation
                #if !defined(CPSTL_VECTOR_USING_STD_ALLOCATION) && \
                    !defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) && \
                    !defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #define CPSTL_VECTOR_USING_C_ALLOCATION
                #endif

                // Force-disable unsupported modes on AVR
                #if defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                    #undef CPSTL_VECTOR_USING_CPP_ALLOCATION
                    #define CPSTL_VECTOR_USING_C_ALLOCATION
                #endif

                #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                    #undef CPSTL_VECTOR_USING_STD_ALLOCATION
                    #define CPSTL_VECTOR_USING_C_ALLOCATION
                #endif
            #endif

            #if defined(CPSTL_STRING_ENABLED)

                // AVR: default string allocation mode -> C allocation
                #if !defined(CPSTL_STRING_USING_STD_ALLOCATION) && \
                    !defined(CPSTL_STRING_USING_CPP_ALLOCATION) && \
                    !defined(CPSTL_STRING_USING_C_ALLOCATION)
                    #define CPSTL_STRING_USING_C_ALLOCATION
                #endif

                // Force-disable unsupported modes on AVR
                #if defined(CPSTL_STRING_USING_CPP_ALLOCATION)
                    #undef CPSTL_STRING_USING_CPP_ALLOCATION
                    #define CPSTL_STRING_USING_C_ALLOCATION
                #endif

                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    #undef CPSTL_STRING_USING_STD_ALLOCATION
                    #define CPSTL_STRING_USING_C_ALLOCATION
                #endif
            #endif

        #else
            #ifndef PROGMEM_MACRO
                #define PROGMEM_MACRO
            #endif
        #endif

    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ESP32

        #if defined(ESP32)

            #include <cstdarg>

            #if defined(CPSTL_VECTOR_ENABLED)

                // ESP32: default vector allocation mode -> STL allocation
                #if !defined(CPSTL_VECTOR_USING_STD_ALLOCATION) && \
                    !defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) && \
                    !defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #define CPSTL_VECTOR_USING_STD_ALLOCATION
                #endif

                // Prefer STL allocation on ESP32
                #if defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                    #undef CPSTL_VECTOR_USING_CPP_ALLOCATION
                    #define CPSTL_VECTOR_USING_STD_ALLOCATION
                #endif

                #if defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #undef CPSTL_VECTOR_USING_C_ALLOCATION
                    #define CPSTL_VECTOR_USING_STD_ALLOCATION
                #endif
            #endif

            #if defined(CPSTL_STRING_ENABLED)

                // ESP32: default string allocation mode -> STL allocation
                #if !defined(CPSTL_STRING_USING_STD_ALLOCATION) && \
                    !defined(CPSTL_STRING_USING_CPP_ALLOCATION) && \
                    !defined(CPSTL_STRING_USING_C_ALLOCATION)
                    #define CPSTL_STRING_USING_STD_ALLOCATION
                #endif

                // Prefer STL allocation on ESP32
                #if defined(CPSTL_STRING_USING_CPP_ALLOCATION)
                    #undef CPSTL_STRING_USING_CPP_ALLOCATION
                    #define CPSTL_STRING_USING_STD_ALLOCATION
                #endif

                #if defined(CPSTL_STRING_USING_C_ALLOCATION)
                    #undef CPSTL_STRING_USING_C_ALLOCATION
                    #define CPSTL_STRING_USING_STD_ALLOCATION
                #endif
            #endif

        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PSoC Creator

        #if defined(PSOC_CREATOR)
            #include <cstring>
            #include <cstdint>
            #include <stdarg.h>

            #ifndef INLINE_MACRO
                #define INLINE_MACRO
            #endif
        #else
            #ifndef INLINE_MACRO
                #define INLINE_MACRO
            #endif
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Desktop targets

        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__APPLE__) || defined(__linux__)

            #include <cstdarg>
            #include <cstdlib>
            #include <cstring>
            #include <cstdint>

            #if defined(CPSTL_VECTOR_ENABLED)

                // Desktop default vector allocation mode
                #if !defined(CPSTL_VECTOR_USING_STD_ALLOCATION) && \
                    !defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) && \
                    !defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #define CPSTL_VECTOR_USING_STD_ALLOCATION
                #endif

                #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                    #include <vector>
                #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #include <cstdlib>
                #endif
            #endif

            #if defined(CPSTL_STRING_ENABLED)

                // Desktop default string allocation mode
                #if !defined(CPSTL_STRING_USING_STD_ALLOCATION) && \
                    !defined(CPSTL_STRING_USING_CPP_ALLOCATION) && \
                    !defined(CPSTL_STRING_USING_C_ALLOCATION)
                    #define CPSTL_STRING_USING_STD_ALLOCATION
                #endif

                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    #include <string>
                    #include <sstream>
                    #include <iostream>
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    #include <cstring>
                    #include <cstdlib>
                #endif
            #endif

        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Validation: vector allocation mode

        #if defined(CPSTL_VECTOR_ENABLED)

            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION) && defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                #error "CPSTL vector allocation mode conflict: STD and CPP allocation are both defined"
            #endif

            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION) && defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                #error "CPSTL vector allocation mode conflict: STD and C allocation are both defined"
            #endif

            #if defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) && defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                #error "CPSTL vector allocation mode conflict: CPP and C allocation are both defined"
            #endif

        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Validation: string allocation mode

        #if defined(CPSTL_STRING_ENABLED)

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION) && defined(CPSTL_STRING_USING_CPP_ALLOCATION)
                #error "CPSTL string allocation mode conflict: STD and CPP allocation are both defined"
            #endif

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION) && defined(CPSTL_STRING_USING_C_ALLOCATION)
                #error "CPSTL string allocation mode conflict: STD and C allocation are both defined"
            #endif

            #if defined(CPSTL_STRING_USING_CPP_ALLOCATION) && defined(CPSTL_STRING_USING_C_ALLOCATION)
                #error "CPSTL string allocation mode conflict: CPP and C allocation are both defined"
            #endif

        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // CPSTL_BUILD_SETTINGS_H