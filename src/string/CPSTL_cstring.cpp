#include <CPcstring.h>

namespace cpstd{

    void* memset(void * ptr, int value, size_t num){
    #ifdef CPSTL_USING_STL
        return std::memset(ptr, value, num);
    #else
        unsigned char* p = static_cast<unsigned char*>(ptr);
        for (size_t i = 0; i < num; ++i) {
            p[i] = static_cast<unsigned char>(value);
        }
        return ptr;
    #endif
    }


    const void* memchr(const void* ptr, int value, size_t num ){
    #ifdef CPSTL_USING_STL
        return std::memchr(ptr, value, num);
    #else
        const unsigned char* p = static_cast<const unsigned char*>(ptr);
        for (size_t i = 0; i < num; ++i) {
            if (p[i] == static_cast<unsigned char>(value)) {
                return &p[i]; // Return a pointer to the first occurrence of the value
            }
        }
        return ptr;
    #endif
    }
    

    void * memchr(void * ptr, int value, size_t num ){
    #ifdef CPSTL_USING_STL
        return std::memchr(ptr, value, num);
    #else
        unsigned char* p = static_cast<unsigned char*>(ptr);
        for (size_t i = 0; i < num; ++i) {
            p[i] = static_cast<unsigned char>(value);
        }
        return ptr;
    #endif
    }
}
