#ifndef CPSTL_IOS_H
#define CPSTL_IOS_H

    #include <CPSTL_BuildSettings.h>

    #include <streams/CPSTL_basic_ios.h>
    #include <streams/CPSTL_fpos.h>


    namespace cpstd{
        #ifndef CPSTL_USING_STL
            using ios = std::ios;
            using wios = std::wios;
        #else
            typedef basic_ios<char> ios;
            typedef basic_ios<wchar_t> wios;
        #endif

        enum class io_errc : uint8_t {
            stream = 1
        };
    }

#endif//CPSTL_IOS_H