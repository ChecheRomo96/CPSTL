#ifndef CPSTL_STRING_H
#define CPSTL_STRING_H
    
    #include <CPSTL_BuildSettings.h>    
    
    #if defined (CPSTL_STRING_ENABLED)

        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            #include <string>
        #else
            #include <string.h> 
            #include <stdio.h>
        #endif

        #if defined(CPSTL_VECTOR_EXCEPTIONS_ENABLED) || defined(CPSTL_EXCEPTIONS_ENABLED)
            #include <CPexception>
        #endif

        #include "string/CPSTL_String.h"
        #include "string/Utilities/CPSTL_String_Utilities.h"
    #endif

#endif//CPSTL_STRING_H