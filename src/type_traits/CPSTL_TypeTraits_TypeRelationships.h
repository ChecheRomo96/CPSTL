#ifndef CPSTL_TYPE_RELATIONSHIPS_H
#define CPSTL_TYPE_RELATIONSHIPS_H

#include <CPSTL_BuildSettings.h>
#include <CPtype_traits.h>

#if defined(CPSTL_USING_STL)
    #include <type_traits>
#endif

namespace cpstd {

    // ============================================================
    // is_same
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class T, class U>
    using is_same = std::is_same<T, U>;

#else

    template <class T, class U>
    struct is_same : false_type {};

    template <class T>
    struct is_same<T, T> : true_type {};

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class T, class U>
    constexpr bool is_same_v = is_same<T, U>::value;
#endif


    // ============================================================
    // is_base_of
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class Base, class Derived>
    using is_base_of = std::is_base_of<Base, Derived>;

#else

    template <class Base, class Derived>
    struct is_base_of {
    private:
        static true_type  test(Base*);
        static false_type test(...);

        static Derived* get();

    public:
        static const bool value = decltype(test(get()))::value;
        typedef integral_constant<bool, value> type;
    };

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class Base, class Derived>
    constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;
#endif


    // ============================================================
    // is_convertible
    // ============================================================

#if defined(CPSTL_USING_STL)

    template <class From, class To>
    using is_convertible = std::is_convertible<From, To>;

#else

    template <class From, class To>
    struct is_convertible {
    private:
        static From&& Declval() noexcept;
        static void TestConvertible(To);

        template <class F, class T>
        static auto test(int) -> decltype(
            TestConvertible(Declval()),
            true_type()
        );

        template <class, class>
        static false_type test(...);

    public:
        static const bool value = decltype(test<From, To>(0))::value;
        typedef integral_constant<bool, value> type;
    };

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class From, class To>
    constexpr bool is_convertible_v = is_convertible<From, To>::value;
#endif


    // ============================================================
    // is_invocable
    // Simplified fallback: direct-call syntax only.
    // Full std::invoke semantics are only guaranteed when STL support
    // and std::is_invocable are available.
    // ============================================================

#if defined(CPSTL_USING_STL) && (CPSTL_CPLUSPLUS >= 201703L)

    template <class Fn, class... Args>
    using is_invocable = std::is_invocable<Fn, Args...>;

#else

    template <class Fn, class... Args>
    struct is_invocable {
    private:
        template <class T>
        static T&& Declval() noexcept;

        template <class F, class... A>
        static auto test(int) -> decltype(
            Declval<F>()(Declval<A>()...),
            true_type()
        );

        template <class, class...>
        static false_type test(...);

    public:
        static const bool value = decltype(test<Fn, Args...>(0))::value;
        typedef integral_constant<bool, value> type;
    };

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class Fn, class... Args>
    constexpr bool is_invocable_v = is_invocable<Fn, Args...>::value;
#endif


    // ============================================================
    // is_nothrow_invocable
    // Simplified fallback: direct-call syntax only.
    // ============================================================

#if defined(CPSTL_USING_STL) && (CPSTL_CPLUSPLUS >= 201703L)

    template <class Fn, class... Args>
    using is_nothrow_invocable = std::is_nothrow_invocable<Fn, Args...>;

#else

    template <class Fn, class... Args>
    struct is_nothrow_invocable {
    private:
        template <class T>
        static T&& Declval() noexcept;

        template <class F, class... A>
        static integral_constant<
            bool,
            noexcept(Declval<F>()(Declval<A>()...))
        > test(int);

        template <class, class...>
        static false_type test(...);

        typedef decltype(test<Fn, Args...>(0)) result_type;

    public:
        static const bool value =
            result_type::value && is_invocable<Fn, Args...>::value;

        typedef integral_constant<bool, value> type;
    };

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class Fn, class... Args>
    constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Fn, Args...>::value;
#endif


    // ============================================================
    // is_nothrow_convertible
    // ============================================================

#if defined(CPSTL_USING_STL) && (CPSTL_CPLUSPLUS >= 202002L)

    template <class From, class To>
    using is_nothrow_convertible = std::is_nothrow_convertible<From, To>;

#else

    template <class From, class To>
    struct is_nothrow_convertible {
    private:
        static From&& Declval() noexcept;
        static void TestConvertible(To);

        static const bool convertible = is_convertible<From, To>::value;

    public:
        static const bool value =
            convertible &&
            noexcept(TestConvertible(Declval()));

        typedef integral_constant<bool, value> type;
    };

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class From, class To>
    constexpr bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;
#endif

} // namespace cpstd

#endif // CPSTL_TYPE_RELATIONSHIPS_H