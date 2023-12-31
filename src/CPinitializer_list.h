#ifndef CPSTL_INITIALIZER_LIST_H
#define CPSTL_INITIALIZER_LIST_H

    #include <CPSTL_BuildSettings.h>
    
    #if __has_include(<initializer_list>)
        #include <initializer_list>
    #else
        #include <stddef.h>
        
        namespace std {

            template <typename T>
            class initializer_list {
            public:
                using value_type = T;
                using reference = const T&;
                using const_reference = const T&;
                using size_type = size_t;
                using const_iterator = const T*;

            private:
                const_iterator _M_array;
                size_type _M_len;

                constexpr initializer_list(const T* array, size_type size) noexcept
                  : _M_array(array), _M_len(size) {}

            public:
                constexpr initializer_list() noexcept
                  : _M_array(nullptr), _M_len(0) {}

                constexpr size_type size() const noexcept {
                  return _M_len;
                }
                constexpr const_iterator begin() const noexcept {
                  return _M_array;
                }
                constexpr const_iterator end() const noexcept {
                  return _M_array + _M_len;
                }
            };
        }

    #endif

    namespace cpstd {
        
        template<class T>
        using initializer_list = std::initializer_list<T>;
    }
        

#endif//CPSTL_INITIALIZER_LIST_H
