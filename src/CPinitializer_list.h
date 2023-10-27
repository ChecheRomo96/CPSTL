#ifndef CPSTL_INITIALIZER_LIST_H
#define CPSTL_INITIALIZER_LIST_H

    #include <CPSTL_BuildSettings.h>
    
    #if __has_include(<initializer_list>)
        #include <initializer_list>
    #endif
        
    #include <stddef.h>

    namespace std {

        #if __has_include(<initializer_list>)
            template<class T>
            using initializer_list = std::initializer_list<T>;
        #else

            template<class _E>
            class initializer_list
            };

          /**
           *  @brief  Return an iterator pointing to the first element of
           *          the initializer_list.
           *  @param  __ils  Initializer list.
           *  @relates initializer_list
           */
          template<class _Tp>
            constexpr const _Tp*
            begin(initializer_list<_Tp> __ils) noexcept
            { return __ils.begin(); }

          /**
           *  @brief  Return an iterator pointing to one past the last element
           *          of the initializer_list.
           *  @param  __ils  Initializer list.
           *  @relates initializer_list
           */
          template<class _Tp>
            constexpr const _Tp*
            end(initializer_list<_Tp> __ils) noexcept
            { return __ils.end(); }

        #endif

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
    }


            


#endif//CPSTL_INITIALIZER_LIST_H
