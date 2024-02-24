#ifndef CPSTL_TYPE_TRAITS_TYPE_PROPERTIES_H
#define CPSTL_TYPE_TRAITS_TYPE_PROPERTIES_H

    #include <CPSTL_BuildSettings.h>
    #include "CPSTL_TypeTraits.h"
    
    namespace cpstd{
    #if defined(CPSTL_USING_STL)
        template <typename T> using is_abstract = std::is_abstract<T>;
        template <typename T> using is_const = std::is_const<T>;
        template <typename T> using is_empty = std::is_empty<T>;
        template <typename T> using is_literal_type = std::is_literal_type<T>;
        template <typename T> using is_pod = std::is_pod<T>;
        template <typename T> using is_polymorphic = std::is_polymorphic<T>;
        template <typename T> using is_standard_layout = std::is_standard_layout<T>;
        template <typename T> using is_trivial = std::is_trivial<T>;
        template <typename T> using is_trivially_copyable = std::is_trivially_copyable<T>;
        template <typename T> using is_unsigned = std::is_unsigned<T>;
        template <typename T> using is_volatile = std::is_volatile<T>;
    #else 

        
        template<typename T>
        struct is_const : cpstd::false_type {};

        template<typename T>
        struct is_const<const T> : cpstd::true_type {};

        
        template<typename T>
        struct is_unsigned {
            #if defined(__is_unsigned)
                static constexpr bool value = __is_unsigned(T);
            #else
                static constexpr bool value = ( T(0) < T(-1) );
            #endif
        };


    #endif
    }

#endif//CPSTL_TYPE_TRAITS_TYPE_PROPERTIES_H