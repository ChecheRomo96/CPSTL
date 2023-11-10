#ifndef CPSTL_UTILITY_H
#define CPSTL_UTILITY_H
    
    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>

    namespace cpstd{
    #if defined CPSTL_USING_STL
    #else
        template <typename T>
        T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
            return static_cast<T&&>(arg);
        }

        template <typename T>
        T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
            static_assert(!std::is_lvalue_reference<T>::value,
                          "Cannot forward an rvalue as an lvalue.");
            return static_cast<T&&>(arg);
        }
    #endif
    }
    
    #include <utility/CPSTL_Move.h>
    #include <utility/CPSTL_Iterator.h>

#endif//CPSTL_UTILITY_H