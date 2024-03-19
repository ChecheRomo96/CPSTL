#ifndef CPSTL_STRING_UTILITIES_TO_STRING_H
#define CPSTL_STRING_UTILITIES_TO_STRING_H

    #include <CPSTL_BuildSettings.h>
    #include <CPstring.h>

    namespace cpstd {

        
        ////////////////////////////////////////////////////////
        // to_string

            cpstd::string to_string( int val );
            cpstd::string to_string( long val );
            cpstd::string to_string( long long val );

            cpstd::string to_string( unsigned val );
            cpstd::string to_string( unsigned long val );
            cpstd::string to_string( unsigned long long val );

            cpstd::string to_string (float val);
            cpstd::string to_string (double val);
            cpstd::string to_string (long double val); 

        //
        ////////////////////////////////////////////////////////
        // to_wstring

            cpstd::wstring to_wstring( int val );
            cpstd::wstring to_wstring( long val );
            cpstd::wstring to_wstring( long long val );

            cpstd::wstring to_wstring( unsigned val );
            cpstd::wstring to_wstring( unsigned long val );
            cpstd::wstring to_wstring( unsigned long long val );

            cpstd::wstring to_wstring (float val);
            cpstd::wstring to_wstring (double val);
            cpstd::wstring to_wstring (long double val); 

        //
        ////////////////////////////////////////////////////////
        // stoi
        
            int stoi(const cpstd::string& str, size_t* pos = nullptr, int base = 10 );
            int stoi(const cpstd::wstring& str, size_t* pos = nullptr, int base = 10 );
        //
        ////////////////////////////////////////////////////////
        // stol
        
            long stol(const cpstd::string& str, size_t* pos = nullptr, int base = 10 );
            long stol(const cpstd::wstring& str, size_t* pos = nullptr, int base = 10 );
        //
        ////////////////////////////////////////////////////////
        // stoll
        
            long long stoll(const cpstd::string& str, size_t* pos = nullptr, int base = 10 );
            long long stoll(const cpstd::wstring& str, size_t* pos = nullptr, int base = 10 );
        //
        ////////////////////////////////////////////////////////
        



    }
    

#endif//CPSTL_STRING_UTILITIES_TO_STRING_H