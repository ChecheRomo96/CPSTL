#ifndef CPSTL_STRING_UTILITIES_TO_STRING_H
#define CPSTL_STRING_UTILITIES_TO_STRING_H

    #include <CPSTL_BuildSettings.h>
    #include <CPstring.h>
    #include "../CPSTL_String.h"
    
    namespace cpstd {
        
        cpstd::string to_string( int val );
        cpstd::string to_string( long val );
        cpstd::string to_string( long long val );

        cpstd::string to_string( unsigned val );
        cpstd::string to_string( unsigned long val );
        cpstd::string to_string( unsigned long long val );

        cpstd::string to_string (float val);
        cpstd::string to_string (double val);
        cpstd::string to_string (long double val); 
    }
    

#endif//CPSTL_STRING_UTILITIES_TO_STRING_H