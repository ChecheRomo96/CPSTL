#ifndef CPSTL_UTILITY_H
#define CPSTL_UTILITY_H
    
    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>

    namespace cpstd{

        template <typename T>
        T&& forward(typename cpstd::remove_reference<T>::type& arg) noexcept {
            return static_cast<T&&>(arg);
        }

        /*template <typename T>
        T&& forward(typename cpstd::remove_reference<T>::type&& arg) noexcept {
            static_assert(!cpstd::is_lvalue_reference<T>::value,
                          "Cannot forward an rvalue as an lvalue.");
            return static_cast<T&&>(arg);
        }*/

        template <class T> 
        void swap (T& a, T& b){
        #if defined(CPSTL_USING_STL)
            std::swap(a,b);
        #else
            T c(cpstd::move(a)); 
            a = cpstd::move(b); 
            b = cpstd::move(c);
        #endif
        }

        template <class T, size_t N>
        void swap (T (&a)[N], T (&b)[N]){
            cpstd::swap(a,b);
        }


        template <typename T, typename U = T>
        T exchange(T& obj, U&& new_value) noexcept {
            T old_value = cpstd::move(obj);
            obj = cpstd::forward<U>(new_value);
            return old_value;
        }

    }


    #include <utility/CPSTL_Move.h>
    #include <utility/CPSTL_Iterator.h>

#endif//CPSTL_UTILITY_H