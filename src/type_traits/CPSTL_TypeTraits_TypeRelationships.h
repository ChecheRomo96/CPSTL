#ifndef CPSTL_TYPE_RELATIONSHIPS_H
#define CPSTL_TYPE_RELATIONSHIPS_H

#include <CPSTL_BuildSettings.h>
#include <CPtype_traits.h>

#if defined(CPSTL_USING_STL)
    #include <type_traits>
#endif

namespace cpstd {

    // ============================================================
    // is_same (ya deberías tenerlo, pero lo dejo por consistencia)
    // ============================================================

    template <class T, class U>
    struct is_same : false_type {};

    template <class T>
    struct is_same<T, T> : true_type {};

    template <class T, class U>
    inline constexpr bool is_same_v = is_same<T, U>::value;

    // ============================================================
    // is_base_of
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class Base, class Derived>
    using is_base_of = std::is_base_of<Base, Derived>;

    template <class Base, class Derived>
    inline constexpr bool is_base_of_v = std::is_base_of_v<Base, Derived>;

#else

    template <class Base, class Derived>
    class is_base_of {
    private:
        static char test(Base*);
        static int  test(...);

        static Derived* get();

    public:
        static const bool value =
            sizeof(test(get())) == sizeof(char);
    };

    template <class Base, class Derived>
    inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;

#endif


    // ============================================================
    // is_convertible
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class From, class To>
    using is_convertible = std::is_convertible<From, To>;

    template <class From, class To>
    inline constexpr bool is_convertible_v = std::is_convertible_v<From, To>;

#else

    template <class To>
    void test_convert(To);

    template <class From, class To>
    class is_convertible {
    private:
        static char test(int);
        static int  test(...);

        static From get();

    public:
        static const bool value =
            sizeof(test_convert<To>(get()), char()) == sizeof(char);
    };

    template <class From, class To>
    inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

#endif


    // ============================================================
    // is_invocable (simplificado)
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class Fn, class... Args>
    using is_invocable = std::is_invocable<Fn, Args...>;

    template <class Fn, class... Args>
    inline constexpr bool is_invocable_v = std::is_invocable_v<Fn, Args...>;

#else

    template <class Fn, class... Args>
    class is_invocable {
    private:
        template <class F, class... A>
        static auto test(int) -> decltype(cpstd::declval<F>()(cpstd::declval<A>()...), true_type());

        template <class, class...>
        static false_type test(...);

    public:
        static const bool value = decltype(test<Fn, Args...>(0))::value;
    };

    template <class Fn, class... Args>
    inline constexpr bool is_invocable_v = is_invocable<Fn, Args...>::value;

#endif


    // ============================================================
    // is_nothrow_invocable (stub básico)
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class Fn, class... Args>
    using is_nothrow_invocable = std::is_nothrow_invocable<Fn, Args...>;

    template <class Fn, class... Args>
    inline constexpr bool is_nothrow_invocable_v = std::is_nothrow_invocable_v<Fn, Args...>;

#else

    template <class Fn, class... Args>
    struct is_nothrow_invocable : false_type {};

    template <class Fn, class... Args>
    inline constexpr bool is_nothrow_invocable_v = false;

#endif


    // ============================================================
    // is_nothrow_convertible (stub)
    // ============================================================

#if defined(CPSTL_USING_STL) && (__cplusplus >= 202002L)

    template <class From, class To> 
    using is_nothrow_convertible = std::is_nothrow_convertible<From, To>;

    template <class From, class To>
    inline constexpr bool is_nothrow_convertible_v = std::is_nothrow_convertible_v<From, To>;

#else

    template <class From, class To>
    struct is_nothrow_convertible : false_type {};

    template <class From, class To>
    inline constexpr bool is_nothrow_convertible_v = false;

#endif

} // namespace cpstd

#endif // CPSTL_TYPE_RELATIONSHIPS_H