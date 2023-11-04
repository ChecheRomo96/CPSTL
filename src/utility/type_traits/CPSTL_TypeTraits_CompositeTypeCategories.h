#ifndef CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H
#define CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H

    #include <CPSTL_BuildSettings.h>
    #include "CPSTL_TypeTraits.h"
    
    namespace cpstd{
    #if defined(CPSTL_USING_STL)

        template <typename T> using is_reference = std::is_reference<T>;
        template <typename T> using is_member_pointer = std::is_member_pointer<T>;
        template <typename T> using is_object = std::is_object<T>;
        template <typename T> using is_scalar = std::is_scalar<T>;
        template <typename T> using is_fundamental = std::is_fundamental<T>;
        template <typename T> using is_compound = std::is_compound<T>;
        template <typename T> using is_arithmetic = std::is_arithmetic<T>;
    #else 
        template <typename T>
        struct is_reference : cpstd::integral_constant<bool,
            cpstd::is_lvalue_reference<T>::value || cpstd::is_rvalue_reference<T>::value> {};

        template <typename T>
        struct is_member_pointer : cpstd::integral_constant<bool,
            cpstd::is_member_object_pointer<T>::value || cpstd::is_member_function_pointer<T>::value> {};

        template <typename T>
        struct is_object : cpstd::integral_constant<bool,
            !cpstd::is_function<T>::value && !cpstd::is_void<T>::value && !cpstd::is_member_function_pointer<T>::value> {};

        template <typename T>
        struct is_scalar : cpstd::integral_constant<bool,
            cpstd::is_integral<T>::value || cpstd::is_floating_point<T>::value || cpstd::is_pointer<T>::value> {};

        template <typename T>
        struct is_fundamental : cpstd::integral_constant<bool,
            cpstd::is_integral<T>::value || cpstd::is_floating_point<T>::value || cpstd::is_void<T>::value ||
            cpstd::is_same<cpstd::nullptr_t, cpstd::remove_cv_t<T>>::value> {};

        template<class T>
        struct is_compound : cpstd::integral_constant <bool, !cpstd::is_fundamental<T>::value> {};

        template <typename T>
        struct is_arithmetic : cpstd::integral_constant<bool, cpstd::is_integral<T>::value || cpstd::is_floating_point<T>::value> {};

    #endif


        template <typename T> inline constexpr bool is_arithmetic_v = cpstd::is_arithmetic<T>::value;
        template <typename T> inline constexpr bool is_fundamental_v = cpstd::is_fundamental<T>::value;
        template <typename T> inline constexpr bool is_member_pointer_v = cpstd::is_member_pointer<T>::value;
        template <typename T> inline constexpr bool is_object_v = cpstd::is_object<T>::value;
        template <typename T> inline constexpr bool is_reference_v = cpstd::is_reference<T>::value;
        template <typename T> inline constexpr bool is_scalar_v = cpstd::is_scalar<T>::value;

    }

#endif//CPSTL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORIES_H