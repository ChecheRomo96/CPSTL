#ifndef CPSTL_UTILITY_H
#define CPSTL_UTILITY_H
    
    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>

    namespace cpstd{
    #if defined CPSTL_USING_STL
    #else
        template <typename T>
        T&& forward(typename cpstd::remove_reference<T>::type& arg) noexcept {
            return static_cast<T&&>(arg);
        }

        template <typename T>
        T&& forward(typename cpstd::remove_reference<T>::type&& arg) noexcept {
            static_assert(!cpstd::is_lvalue_reference<T>::value,
                          "Cannot forward an rvalue as an lvalue.");
            return static_cast<T&&>(arg);
        }
    #endif

        template <class T> 
        void swap (T& a, T& b){
          T c(cpstd::move(a)); 
          a = cpstd::move(b); 
          b = cpstd::move(c);
        }

        template <class T, size_t N> 
        void swap (T (&a)[N], T (&b)[N]){
            for (size_t i = 0; i<N; ++i){
                swap (a[i],b[i]);
            }
        }

    }


    #include <utility/CPSTL_Move.h>
    #include <utility/CPSTL_Iterator.h>

#endif//CPSTL_UTILITY_H