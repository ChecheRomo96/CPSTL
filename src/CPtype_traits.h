#ifndef CPSTL_TYPE_TRAITS_H
#define CPSTL_TYPE_TRAITS_H
    
    #include <CPSTL_BuildSettings.h>
    #include <utility/CPSTL_types.h>
    

    namespace cpstd{
    #if defined(CPSTL_USING_STL)
        template <typename T, typename U>
        using is_same = std::is_same<T, U>;

        template <typename T, typename U> inline constexpr bool is_same_v = cpstd::is_same<T, U>::value;

        template <typename T> using remove_const = std::remove_const<T>;

        template <typename T> using remove_reference = std::remove_reference<T>;

        template <typename T> using remove_cv = std::remove_cv<T>;
        template <typename T> using remove_cv_t = typename cpstd::remove_cv<T>::type;


        template <typename T> using remove_const = std::remove_const<T>;

        template <typename T> using remove_volatile = std::remove_volatile<T>;

        template <bool B, typename T = void> using enable_if = std::enable_if<B , T>;
        template <bool B, typename T = void> using enable_if_t = typename cpstd::enable_if<B,T>::type;
    #else
        template <typename T> struct remove_reference { using type = T; };
        template <typename T> struct remove_reference<T&> { using type = T; };
        template <typename T> struct remove_reference<T&&> { using type = T; };

        template <typename T, typename U> struct is_same{ static constexpr bool value = false; };
        template <typename T> struct is_same<T, T> { static constexpr bool value = true; };
        template <typename T, typename U> INLINE_MACRO  constexpr bool is_same_v = cpstd::is_same<T, U>::value;

        template <typename T> struct remove_const { using type = T; };
        template <typename T> struct remove_const<const T> { using type = T; };

        template <typename T> struct remove_cv                     { using type = T; };
        template <typename T> struct remove_cv<const T>            { using type = T; };
        template <typename T> struct remove_cv<volatile T>         { using type = T; };
        template <typename T> struct remove_cv<const volatile T>   { using type = T; };
        template <typename T> using remove_cv_t = typename cpstd::remove_cv<T>::type;

        template <typename T> struct remove_volatile { typedef T type; };
        template <typename T> struct remove_volatile<volatile T> { typedef T type; };


        template <bool B, typename T = void> struct enable_if {};
        template <typename T> struct enable_if<true, T> { using type = T; };
        template <bool B, typename T = void> using enable_if_t = typename cpstd::enable_if<B,T>::type;
    #endif
    }
    
    #include <utility/type_traits/CPSTL_TypeTraits.h>

#endif//CPSTL_TYPE_TRAITS_H