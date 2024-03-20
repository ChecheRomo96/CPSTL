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

        istream& ws(istream& is);
        
        template <class charT, class traits>
        basic_istream<charT,traits>& ws(basic_istream<charT,traits>& is){
        #if __has_include(<istream>)
            return std::ws(is);
        #else
            while (cpstd::isspace(is.peek(), is.getloc())){
                is.ignore();
            }
            return is;
        #endif
        }
    }


    

#endif//CPSTL_ISTREAM_H