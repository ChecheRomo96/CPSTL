#ifndef CROSS_PLATFORM_STL_BUILD_SETTINGS_H
#define CROSS_PLATFORM_STL_BUILD_SETTINGS_H

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CPString Version

        #ifndef CPSTL_VERSION
            #define CPSTL_VERSION "1.0.0"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Arduino IDE

        #if defined(Arduino_h)
            #include <Arduino.h>
            #include "CPSTL_UserSetup.h"
asfd
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
                #if !defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #define CPVECTOR_USING_C_ALLOCATION
                #endif

                #if defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                    #undef CPSTL_VECTOR_USING_CPP_ALLOCATION
                #endif

                #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                    #undef CPSTL_VECTOR_USING_CPP_ALLOCATION
                #endif

                #if defined(CPVECTOR_USING_STD_ALLOCATION)
                    #undef CPVECTOR_USING_STD_ALLOCATION
                #endif
            #endif

            #if defined(CPSTL_STRING_ENABLED)

                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    #undef CPSTL_STRING_USING_STD_ALLOCATION
                #endif

                #if defined(CPSTL_STRING_USING_CPP_ALLOCATION)
                    #undef CPSTL_STRING_USING_CPP_ALLOCATION
                #endif

                #if !defined(CPSTL_STRING_USING_C_ALLOCATION)
                    #define CPSTRING_USING_C_ALLOCATION
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

            #if !defined(CPSTRING_USING_STD_STRING) && !defined(CPSTRING_USING_C_STRING) && !defined(CPSTRING_USING_CPP_STRING)
                #define CPSTL_STRING_USING_STD_STRING
            #endif

            #if defined(CPSTRING_USING_STD_STRING)
                #include <vector>
            #elif defined(CPSTRING_USING_C_STRING)
                #include <cstring> 
            #elif defined(CPSTRING_USING_ARDUINO_STRING)
            #endif

        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PSoC Creator
    
        #if defined(PSOC_CREATOR)
            #include <cstring>
            #include <cstdint>
            #include <stdarg.h>

            #if !defined(CPSTRING_USING_STD_STRING) && !defined(CPSTRING_USING_C_STRING) && !defined(CPSTRING_USING_ARDUINO_STRING)
                #define CPSTRING_USING_C_STRING
            #endif
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Building as a target for a desktop system
    
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__APPLE__) || defined(linux)

            #include <cstdarg>
            #include <stdlib.h>
            
            #if defined(CPSTL_VECTOR_ENABLED)
                
                #if !defined(CPSTL_VECTOR_USING_STD_ALLOCATION) && !defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) && !defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #define CPSTL_VECTOR_USING_STD_ALLOCATION
                #endif
                
                #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                    #include <vector>
                #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                    #include <cstdlib>
                #endif
                
            #endif

            #if defined(CPSTL_STRING_ENABLED)
                
                #if !defined(CPSTRING_USING_STD_STRING) && !defined(CPSTRING_USING_C_STRING) && !defined(CPSTRING_USING_ARDUINO_STRING)
                    #define CPSTRING_USING_STD_STRING
                    #include <sstream> // Include the <sstream> header
                    #include <iostream>
                #endif

                #if defined(CPSTRING_USING_STD_STRING)
                    #include <vector>
                #elif defined(CPSTRING_USING_C_STRING)
                    #include <cstring>
                #endif
            #endif



        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    #if defined(__has_include) && __has_include(<vector>)
        #if !defined(CPSTL_USING_STL)
            #define CPSTL_USING_STL
        #endif
    #else
        #if defined(CPSTL_USING_STL)
            #undef CPSTL_USING_STL
        #endif
    #endif

#endif//CROSS_PLATFORM_STRING_BUILD_SETTINGS_H
