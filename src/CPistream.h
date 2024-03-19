#ifndef CPSTL_ISTREAM_H
#define CPSTL_ISTREAM_H

    #include <CPSTL_BuildSettings.h>
    #include <CPios.h>
    #include <CPostream.h>


    #include "streams/CPSTL_basic_istream.h"
    #include "streams/CPSTL_basic_iostream.h"


    namespace cpstd{
    #if __has_include(<istream>)
        
        using istream = std::istream;
        using wistream = std::wistream;

        using iostream = std::iostream;
        using wiostream = std::wiostream;


    #else

        using istream = cpstd::basic_istream<char>;
        using wistream = cpstd::basic_istream<wchar_t>;


        using iostream = cpstd::basic_iostream<char>;
        using wiostream = cpstd::basic_iostream<wchar_t>;

    #endif
    }


    

#endif//CPSTL_ISTREAM_H