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
                template <typename T>
        struct is_reference : cpstd::integral_constant<bool,
            cpstd::is_lvalue_reference<T>::value || cpstd::is_rvalue_reference<T>::value> {};

        template <typename T>
        struct is_member_pointer : cpstd::integral_constant<bool,
            cpstd::is_member_object_pointer<T>::value || cpstd::is_void<T>::value || cpstd::is_reference<T>::value> {};

        template <typename T>
        struct is_object : cpstd::integral_constant<bool,
            !cpstd::is_function<T>::value && !cpstd::is_void<T>::value && !cpstd::is_member_function_pointer<T>::value> {};

        template <typename T>
        struct is_scalar : cpstd::integral_constant<bool,
            cpstd::is_integral<T>::value || cpstd::is_floating_point<T>::value || cpstd::is_pointer<T>::value> {};

        template <typename T>
        struct is_fundamental : cpstd::integral_constant<bool,
            cpstd::is_integral<T>::value || cpstd::is_floating_point<T>::value || cpstd::is_void<T>::value ||
            cpstd::is_same<cpstd::nullptr_t, typename cpstd::remove_cv<T>::type>::value> {};

        template<class T>
        struct is_compound : cpstd::integral_constant <bool, !cpstd::is_fundamental<T>::value> {};

    #endif
    }

#endif//CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H