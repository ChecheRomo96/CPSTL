#ifndef CPSTL_H
#define CPSTL_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPtype_traits.h>

    namespace cpstd {}

    #ifdef ARDUINO
        #include <Arduino.h>
    #endif

    #ifdef CPSTL_VECTOR_ENABLED
        #include <CPvector.h>
    #endif

    #ifdef CPSTL_STRING_ENABLED
        #include <CPstring.h>
    #endif

#endif//CPSTL_H