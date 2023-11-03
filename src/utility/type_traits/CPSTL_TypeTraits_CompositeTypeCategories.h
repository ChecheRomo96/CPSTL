#ifndef CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H
#define CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H

    #include <CPSTL_BuildSettings.h>
    #include "CPSTL_TypeTraits.h"
    
    namespace cpstd{

    #if defined(CPSTL_USING_STL)

        template <typename T>
        using is_arithmetic = std::is_arithmetic<T>;

        template <typename T>
        using is_compound = std::is_compound<T>;

        template <typename T>
        using is_fundamental = std::is_fundamental<T>;

        template <typename T>
        using is_member_pointer = std::is_member_pointer<T>;

        template <typename T>
        using is_object = std::is_object<T>;

        template <typename T>
        using is_reference = std::is_integral<T>;

        template <typename T>
        using is_scalar = std::is_lvalue_reference<T>;

    #else 
        template <typename U>
        struct is_scalar {
            static const bool value =
                cpstd::is_integral<U>::value || cpstd::is_floating_point<U>::value || cpstd::is_pointer<U>::value;
        };


    #endif
    }

#endif//CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H