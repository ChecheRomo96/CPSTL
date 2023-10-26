#ifndef CPSTL_H
#define CPSTL_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list>

    namespace cpstd {}

    #ifdef ARDUINO
        #include <Arduino.h>
    #endif

    #ifdef CPSTL_VECTOR_ENABLED
        #include <CPvector>
    #endif

    #ifdef CPSTL_STRING_ENABLED
        #include <CPstring>
        #include <stdarg.h>
        #include <cstdio.h>
    #endif

#endif//CPSTL_H