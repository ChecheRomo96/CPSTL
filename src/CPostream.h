#ifndef CPSTL_OSTREAM_H
#define CPSTL_OSTREAM_H

    #include <CPSTL_BuildSettings.h>
    #include <CPios.h>


    #include "streams/CPSTL_basic_ostream.h"


    namespace cpstd{
    #if __has_include(<ostream>)
        using ostream = std::ostream;
        using wostream = std::wostream;
    #else
        using ostream = cpstd::basic_ostream<char>;
        using wostream = cpstd::basic_ostream<wchar_t>;
    #endif
    }

    

#endif//CPSTL_OSTREAM_H