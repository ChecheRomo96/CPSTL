#ifndef CPSTL_USER_SETUP_H
#define CPSTL_USER_SETUP_H


    #if defined(__AVR__) || defined(__avr__) || defined(PSOC_CREATOR)
        
        #define CPSTL_USING_C_ALLOCATION

        #define CPSTL_VECTOR_ENABLED
        #define CPSTL_VECTOR_USING_C_ALLOCATION

        #define CPSTL_STRING_ENABLED
        #define CPSTL_STRING_USING_C_ALLOCATION
    #endif


    #if defined(ESP32)
        
        #define CPSTL_USING_STL

        #define CPSTL_USING_STL_ALLOCATION

        #define CPSTL_VECTOR_ENABLED
        #define CPSTL_VECTOR_USING_STL_ALLOCATION

        #define CPSTL_STRING_ENABLED
        #define CPSTL_STRING_USING_STL_ALLOCATION
    #endif

#endif//CPSTL_USER_SETUP_H