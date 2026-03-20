#ifndef CPSTL_STRING_CLASS_H
#define CPSTL_STRING_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPiterator.h>
    #include <CPmemory.h>
    #include <utility/CPSTL_types.h>
    #include <utility/CPSTL_Move.h>
    

    #if defined(CPSTL_STRING_EXCEPTIONS_ENABLED) && defined(CPSTL_EXCEPTIONS_ENABLED)
        #include <CPexception.h>           
    #endif  


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
        // Convert from String functions

        int stoi (const cpstd::string&  str, size_t* idx = 0, int base = 10);
        int stoi (const cpstd::wstring& str, size_t* idx = 0, int base = 10);

        long stol (const cpstd::string&  str, size_t* idx = 0, int base = 10);
        long stol (const cpstd::wstring& str, size_t* idx = 0, int base = 10);

        unsigned long stoul (const cpstd::string&  str, size_t* idx = 0, int base = 10);
        unsigned long stoul (const cpstd::wstring& str, size_t* idx = 0, int base = 10);

        long long stoll (const cpstd::string&  str, size_t* idx = 0, int base = 10);
        long long stoll (const cpstd::wstring& str, size_t* idx = 0, int base = 10);

        unsigned long long stoull (const cpstd::string&  str, size_t* idx = 0, int base = 10);
        unsigned long long stoull (const cpstd::wstring& str, size_t* idx = 0, int base = 10);

        float stof (const cpstd::string&  str, size_t* idx = 0);
        float stof (const cpstd::wstring& str, size_t* idx = 0);

        double stod (const cpstd::string&  str, size_t* idx = 0);
        double stod (const cpstd::wstring& str, size_t* idx = 0);

        long double stold (const cpstd::string&  str, size_t* idx = 0);
        long double stold (const cpstd::wstring& str, size_t* idx = 0);


        // Convert to String functions
        
        cpstd::string to_string( int val );
        cpstd::string to_string( long val );
        cpstd::string to_string( long long val );

        cpstd::string to_string( unsigned val );
        cpstd::string to_string( unsigned long val );
        cpstd::string to_string( unsigned long long val );

        cpstd::string to_string (float val);
        cpstd::string to_string (double val);
        cpstd::string to_string (long double val); 
        

        cpstd::wstring to_wstring( int val );
        cpstd::wstring to_wstring( long val );
        cpstd::wstring to_wstring( long long val );

        cpstd::wstring to_wstring( unsigned val );
        cpstd::wstring to_wstring( unsigned long val );
        cpstd::wstring to_wstring( unsigned long long val );

        cpstd::wstring to_wstring (float val);
        cpstd::wstring to_wstring (double val);
        cpstd::wstring to_wstring (long double val); 
        

    }
    
#endif//CPSTL_STRING_CLASS_H