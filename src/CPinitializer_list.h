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

            template<class T>
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


            public:
                constexpr initializer_list(const_iterator __a, size_type __l)
                    : _M_array(__a), _M_len(__l) { }
                    
                constexpr initializer_list() noexcept
                    : _M_array(nullptr), _M_len(0) { }

                constexpr size_type size() const noexcept { return _M_len; }
                constexpr const_iterator begin() const noexcept { return _M_array; }
                constexpr const_iterator end() const noexcept { return _M_array + _M_len; }

                // Custom constructor to initialize with a brace-enclosed initializer list
                constexpr initializer_list(std::initializer_list<T> il) noexcept
                    : _M_array(il.begin()), _M_len(il.size()) { }
            };

            // Helper function to create initializer lists
            template<class T>
            constexpr initializer_list<T> make_initializer_list(const T* array, size_t size) {
                return initializer_list<T>(array, size);
            }

        #endif
    }


            


#endif//CPSTL_INITIALIZER_LIST_H
