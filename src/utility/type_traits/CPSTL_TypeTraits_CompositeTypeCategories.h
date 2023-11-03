#ifndef CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H
#define CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H

    #include <CPSTL_BuildSettings.h>
    #include "CPSTL_TypeTraits.h"
    
    namespace cpstd{
    #if defined(CPSTL_USING_STL)
        template <typename T>
        using is_arithmetic = cpstd::is_arithmetic<T>;

        template <typename T>
        using is_compound = cpstd::is_compound<T>;

        template <typename T>
        using is_fundamental = cpstd::is_fundamental<T>;

        template <typename T>
        using is_member_pointer = cpstd::is_member_pointer<T>;

        template <typename T>
        using is_object = cpstd::is_object<T>;

        template <typename T>
        using is_reference = cpstd::is_integral<T>;

        template <typename T>
        using is_scalar = cpstd::is_lvalue_reference<T>;
    #else 
        template<class T>
        struct is_compound : cpstd::integral_constant <bool, !cpstd::is_fundamental<T>::value> {};

        template <typename U>
        struct is_fundamental : cpstd::integral_constant<bool,
            cpstd::is_integral<U>::value || cpstd::is_floating_point<U>::value || cpstd::is_void<U>::value ||
            cpstd::is_same<cpstd::nullptr_t, typename cpstd::remove_cv<U>::type>::value> {};

        template <typename U>
        struct is_member_pointer : cpstd::integral_constant<bool,
            cpstd::is_member_object_pointer<U>::value || cpstd::is_void<U>::value || cpstd::is_reference<U>::value> {};

        template <typename U>
        struct is_object : cpstd::integral_constant<bool,
            !cpstd::is_function<U>::value && !cpstd::is_void<U>::value && !cpstd::is_member_function_pointer<U>::value> {};

        template <typename U>
        struct is_reference : cpstd::integral_constant<bool,
            cpstd::is_lvalue_reference<U>::value || cpstd::is_rvalue_reference<U>::value> {};

        template <typename U>
        struct is_scalar : cpstd::integral_constant<bool,
            cpstd::is_integral<U>::value || cpstd::is_floating_point<U>::value || cpstd::is_pointer<U>::value> {};
    #endif
    }

#endif//CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H