#ifndef CPSTL_UTILITY_H
#define CPSTL_UTILITY_H
    
    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>

    #include <utility/CPSTL_Move.h>

    #if defined CPSTL_USING_STL
    #include <utility>
    #endif

    namespace cpstd{
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // forward 
            #if defined CPSTL_USING_STL
                using std::forward;
            #else
                template <typename T>
                constexpr T&& forward(typename cpstd::remove_reference<T>::type& arg) noexcept {
                    return static_cast<T&&>(arg);
                }

                template <typename T>
                constexpr T&& forward(typename cpstd::remove_reference<T>::type&& arg) noexcept {
                    static_assert(!cpstd::is_lvalue_reference<T>::value, "Can't forward an rvalue as an lvalue.");
                    return static_cast<T&&>(arg);
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


    #include <utility/CPSTL_Iterator.h>
    #include <utility/CPSTL_Move.h>

#endif//CPSTL_UTILITY_H