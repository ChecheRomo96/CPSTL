#ifndef CPSTL_VECTOR_H
#define CPSTL_VECTOR_H
    
    #include <CPSTL_BuildSettings.h>

    #include <utility/CPSTL_types.h>

    #if defined(CPSTL_VECTOR_ENABLED)

        #include "CPinitializer_list.h"

        #if defined (CPSTL_VECTOR_SORTING_ENABLED)
            #include "Sorting/CPVector_Sorting.h"
        #endif

        #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
            #include "CPSTL_Exceptions.h"
        #endif

        #include "vector/CPSTL_Vector.h"
    #endif

#endif//CPSTL_VECTOR_H