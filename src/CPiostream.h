#ifndef CPIOSTREAM_H
#define CPIOSTREAM_H

    #include <CPSTL_BuildSettings.h>
    #include <CPistream.h>
    #include <CPostream.h>
    #include <CPstreambuf.h>

    #if __has_include(<istream>)
        #include <iostream>
    #endif

    namespace cpstd{

       

        using cin = std::basic_istream<char>;
        using cout = std::basic_ostream<char>;
        extern ostream cerr;
        extern ostream clog;

        extern wistream wcin;
        extern wostream wcout;
        extern wostream wcerr;
        extern wostream wclog;
    }


#endif//CPIOSTREAM_H