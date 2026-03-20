#ifndef CPSTL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORIES_H
#define CPSTL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORIES_H

#include <CPSTL_BuildSettings.h>
#include "CPSTL_TypeTraits.h"

#if defined(CPSTL_USING_STL)
#include <type_traits>
#endif

namespace cpstd {

#if defined(CPSTL_USING_STL)

    template <typename T>
    using is_array = std::is_array<T>;

    template <typename T>
    using is_class = std::is_class<T>;

    template <typename T>
    using is_enum = std::is_enum<T>;

    template <typename T>
    using is_floating_point = std::is_floating_point<T>;

    template <typename T>
    using is_function = std::is_function<T>;

    template <typename T>
    using is_integral = std::is_integral<T>;

    template <typename T>
    using is_lvalue_reference = std::is_lvalue_reference<T>;

    template <typename T>
    using is_member_function_pointer = std::is_member_function_pointer<T>;

    template <typename T>
    using is_member_object_pointer = std::is_member_object_pointer<T>;

    template <typename T>
    using is_pointer = std::is_pointer<T>;

    template <typename T>
    using is_rvalue_reference = std::is_rvalue_reference<T>;

    template <typename T>
    using is_union = std::is_union<T>;

    template <typename T>
    using is_void = std::is_void<T>;

#if CPSTL_CPLUSPLUS >= 201402L
    template <typename T>
    constexpr bool is_array_v = is_array<T>::value;

    template <typename T>
    constexpr bool is_class_v = is_class<T>::value;

    template <typename T>
    constexpr bool is_enum_v = is_enum<T>::value;

    template <typename T>
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template <typename T>
    constexpr bool is_function_v = is_function<T>::value;

    template <typename T>
    constexpr bool is_integral_v = is_integral<T>::value;

    template <typename T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template <typename T>
    constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

    template <typename T>
    constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

    template <typename T>
    constexpr bool is_pointer_v = is_pointer<T>::value;

    template <typename T>
    constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

    template <typename T>
    constexpr bool is_union_v = is_union<T>::value;

    template <typename T>
    constexpr bool is_void_v = is_void<T>::value;
#endif

#else

    // ============================================================
    // is_array
    // ============================================================

    template <class T>
    struct is_array : cpstd::false_type {};

    template <class T>
    struct is_array<T[]> : cpstd::true_type {};

    template <class T, cpstd::size_t N>
    struct is_array<T[N]> : cpstd::true_type {};

    // ============================================================
    // is_class
    // ============================================================

    template <typename T>
    struct is_class : cpstd::bool_constant<__is_class(T)> {};

    // ============================================================
    // is_enum
    // ============================================================

    template <typename T>
    struct is_enum : cpstd::bool_constant<__is_enum(T)> {};

    // ============================================================
    // is_floating_point
    // ============================================================

    template <typename T>
    struct is_floating_point : cpstd::bool_constant<
        cpstd::is_same<typename cpstd::remove_cv<T>::type, float>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, double>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, long double>::value
    > {
    };

    // ============================================================
    // is_function
    // Simplified implementation
    // ============================================================

    template <typename T>
    struct is_function : cpstd::false_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args...)> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args..., ...)> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args...) const> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args..., ...) const> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args...) volatile> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args..., ...) volatile> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args...) const volatile> : cpstd::true_type {};

    template <typename Ret, typename... Args>
    struct is_function<Ret(Args..., ...) const volatile> : cpstd::true_type {};

    // ============================================================
    // is_integral
    // ============================================================

    template <typename T>
    struct is_integral : cpstd::bool_constant<
        cpstd::is_same<typename cpstd::remove_cv<T>::type, bool>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, char>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, signed char>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, unsigned char>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, short>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, unsigned short>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, int>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, unsigned int>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, long>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, unsigned long>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, long long>::value ||
        cpstd::is_same<typename cpstd::remove_cv<T>::type, unsigned long long>::value
    > {
    };

    // ============================================================
    // is_lvalue_reference
    // ============================================================

    template <typename T>
    struct is_lvalue_reference : cpstd::false_type {};

    template <typename T>
    struct is_lvalue_reference<T&> : cpstd::true_type {};

    // ============================================================
    // is_member_function_pointer
    // ============================================================

    template <typename T>
    struct is_member_function_pointer : cpstd::false_type {};

    template <typename T, typename C>
    struct is_member_function_pointer<T C::*>
        : cpstd::is_function<T> {
    };

    // ============================================================
    // is_member_object_pointer
    // ============================================================

    template <typename T>
    struct is_member_object_pointer : cpstd::false_type {};

    template <typename T, typename C>
    struct is_member_object_pointer<T C::*>
        : cpstd::bool_constant<!cpstd::is_function<T>::value> {
    };

    // ============================================================
    // is_pointer
    // ============================================================

    template <typename T>
    struct is_pointer_helper : cpstd::false_type {};

    template <typename T>
    struct is_pointer_helper<T*> : cpstd::true_type {};

    template <typename T>
    struct is_pointer
        : is_pointer_helper<typename cpstd::remove_cv<T>::type> {
    };

    // ============================================================
    // is_rvalue_reference
    // ============================================================

    template <typename T>
    struct is_rvalue_reference : cpstd::false_type {};

    template <typename T>
    struct is_rvalue_reference<T&&> : cpstd::true_type {};

    // ============================================================
    // is_union
    // ============================================================

    template <typename T>
    struct is_union : cpstd::bool_constant<__is_union(T)> {};

    // ============================================================
    // is_void
    // ============================================================

    template <typename T>
    struct is_void
        : cpstd::is_same<void, typename cpstd::remove_cv<T>::type> {
    };

    // ============================================================
    // _v helpers (C++14+ only)
    // ============================================================

#if CPSTL_CPLUSPLUS >= 201402L

    template <typename T>
    constexpr bool is_array_v = is_array<T>::value;

    template <typename T>
    constexpr bool is_class_v = is_class<T>::value;

    template <typename T>
    constexpr bool is_enum_v = is_enum<T>::value;

    template <typename T>
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template <typename T>
    constexpr bool is_function_v = is_function<T>::value;

    template <typename T>
    constexpr bool is_integral_v = is_integral<T>::value;

    template <typename T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

    template <typename T>
    constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

    template <typename T>
    constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

    template <typename T>
    constexpr bool is_pointer_v = is_pointer<T>::value;

    template <typename T>
    constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

    template <typename T>
    constexpr bool is_union_v = is_union<T>::value;

    template <typename T>
    constexpr bool is_void_v = is_void<T>::value;

#endif

#endif

} // namespace cpstd

#endif // CPSTL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORIES_H