#ifndef CPSTL_STRING_CLASS_H
#define CPSTL_STRING_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPiterator.h>
    #include <CPmemory.h>
    #include <utility/CPSTL_types.h>
    #include <utility/CPSTL_Move.h>
    



    #ifdef CPSTL_USING_STL
        #include <string>
        #include <stdexcept>
    #endif  


    #include "CPSTL_CharTraits.h"
    #include "CPSTL_basic_string.h"

    namespace cpstd{  

        using string = basic_string<char>;
        using wstring   = basic_string<wchar_t>;

        #ifdef CPSTL_ENABLE_UNICODE_STRINGS
            #if defined(__cpp_char8_t)
                using u8string = basic_string<char8_t>;
            #endif
            using u16string = basic_string<char16_t>;
            using u32string = basic_string<char32_t>;
        #endif
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Numeric conversions
        //
        // In STL mode these are the std functions (which throw on bad input).
        // Otherwise they never throw: when no number can be read they return 0
        // and set *idx to 0, and a value outside the result type saturates to
        // its minimum or maximum. *idx receives the number of characters used.

        int stoi (const cpstd::string& str, size_t* idx = nullptr, int base = 10);
        long stol (const cpstd::string& str, size_t* idx = nullptr, int base = 10);
        unsigned long stoul (const cpstd::string& str, size_t* idx = nullptr, int base = 10);
        long long stoll (const cpstd::string& str, size_t* idx = nullptr, int base = 10);
        unsigned long long stoull (const cpstd::string& str, size_t* idx = nullptr, int base = 10);
        float stof (const cpstd::string& str, size_t* idx = nullptr);
        double stod (const cpstd::string& str, size_t* idx = nullptr);
        long double stold (const cpstd::string& str, size_t* idx = nullptr);

        // Integers are written exactly; floating-point values use std::to_string's
        // fixed six-decimal format ("3.140000"), rounded to nearest.
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
    
#endif//CPSTL_STRING_CLASS_H