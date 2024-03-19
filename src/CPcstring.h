#ifndef CPSTL_C_STRING_H
#define CPSTL_C_STRING_H

    #include<CPSTL_BuildSettings.h>

    namespace cpstd{

        void* memset(void * ptr, int value, size_t num);
        const void * memchr(const void* ptr, int value, size_t num );
        void* memchr(void* ptr, int value, size_t num );


    }

#endif//CPSTL_C_STRING_H