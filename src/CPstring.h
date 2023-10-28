#ifndef CPSTL_STRING_H
#define CPSTL_STRING_H
    
    #include <CPSTL_BuildSettings.h>    
    
    #if defined (CPSTL_STRING_ENABLED)

        #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_STRING_USING_CPP_ALLOCATION)
            #include <string>
            #include <string.h>
            #include <stdio.h>
            #include <stdlib.h>
            #include <math.h>
            #include <sstream>
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION) 
            #include <string.h> 
            #include <stdio.h>
            #include <stdlib.h>
            #include <math.h>
        #endif

        #if defined(CPSTL_VECTOR_EXCEPTIONS_ENABLED) || defined(CPSTL_EXCEPTIONS_ENABLED)
            #include <CPexception.h>
        #endif

        #include "string/CPSTL_String.h"
        #include "string/Utilities/CPSTL_String_Utilities.h"
    #endif

#endif//CPSTL_STRING_H