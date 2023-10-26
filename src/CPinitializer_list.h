#ifndef CPSTL_INITIALIZER_LIST_H
#define CPSTL_INITIALIZER_LIST_H

    #include <CPSTL_BuildSettings.h>
    
    #if __has_include(<initializer_list>)
        #include <initializer_list>
    #endif
        
    #include <stddef.h>

    namespace cpstd {

        #if __has_include(<initializer_list>)
            template<class T>
            using initializer_list = std::initializer_list<T>;
        #else

            template<class T> class initializer_list
            {
            private:
                const T* array_ = nullptr;
                size_t len_ = 0;
         
                // The compiler can (and will) call a private constructor.
                // This constructor will get called when the compiler encounters a braced
                // list expression with elements of type T, like in f({t1, t2, t3}) and
                // an initializer_list<T> is expected by f function.
                constexpr initializer_list(const T* array, size_t len) : array_{array}, len_{len} {}
         
            public:
                constexpr initializer_list() = default;
         
                constexpr size_t size() const
                {
                    return len_;
                }
         
                constexpr const T* begin() const
                {
                    return array_;
                }
         
                constexpr const T* end() const
                {
                    return begin() + size();
                }
            };
        #endif
    }

    template<typename T>
    constexpr const T* begin(cpstd::initializer_list<T> il) noexcept 
    {
        return il.begin();
    }

    template<typename T>
    constexpr const T* end(cpstd::initializer_list<T> il) noexcept
    {
        return il.end();
    }


            


#endif//CPSTL_INITIALIZER_LIST_H
