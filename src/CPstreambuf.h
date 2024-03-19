#ifndef CPSTL_STREAM_BUFFER_H
#define CPSTL_STREAM_BUFFER_H

    #include <CPSTL_BuildSettings.h>
    #include <streams/CPSTL_basic_streambuf.h>

    namespace cpstd{

        #if __has_include(<streambuf>)
            using streambuf = std::streambuf;
            using wstreambuf = std::wstreambuf;
        #else 
            using streambuf  = basic_streambuf<char>;
            using wstreambuf = basic_streambuf<wchar_t>;
        #endif
    }

#endif//CPSTL_STREAM_BUFFER_H