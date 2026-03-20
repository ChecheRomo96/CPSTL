#ifndef CPSTL_TYPE_RELATIONSHIPS_H
#define CPSTL_TYPE_RELATIONSHIPS_H

#include <CPSTL_BuildSettings.h>
#include <CPtype_traits.h>

#if defined(CPSTL_USING_STL)
#include <type_traits>
#endif

namespace cpstd {

    namespace detail {

        template <class T>
        T&& Declval() noexcept;

        template <class To>
        void TestConvertible(To);

    } // namespace detail

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

    namespace detail {

        template <class From, class To, class = void>
        struct is_convertible_impl : false_type {};

        template <class From, class To>
        struct is_convertible_impl<
            From,
            To,
            decltype(
                detail::TestConvertible<To>(detail::Declval<From>()),
                void()
                )
        > : true_type {
        };

    } // namespace detail

    template <class From, class To>
    struct is_convertible : detail::is_convertible_impl<From, To> {};

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

    namespace detail {

        template <class Fn, class... Args>
        struct is_invocable_impl {
        private:
            template <class F, class... A>
            static auto test(int) -> decltype(
                detail::Declval<F>()(detail::Declval<A>()...),
                true_type()
                );

            template <class, class...>
            static false_type test(...);

        public:
            typedef decltype(test<Fn, Args...>(0)) type;
            static const bool value = type::value;
        };

    } // namespace detail

    template <class Fn, class... Args>
    struct is_invocable
        : integral_constant<bool, detail::is_invocable_impl<Fn, Args...>::value> {
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

    namespace detail {

        template <class Fn, class... Args>
        struct is_nothrow_invocable_impl {
        private:
            template <class F, class... A>
            static integral_constant<
                bool,
                noexcept(detail::Declval<F>()(detail::Declval<A>()...))
            > test(int);

            template <class, class...>
            static false_type test(...);

        public:
            typedef decltype(test<Fn, Args...>(0)) type;
            static const bool value = type::value && is_invocable<Fn, Args...>::value;
        };

    } // namespace detail

    template <class Fn, class... Args>
    struct is_nothrow_invocable
        : integral_constant<bool, detail::is_nothrow_invocable_impl<Fn, Args...>::value> {
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

    namespace detail {

        template <class From, class To, bool = is_convertible<From, To>::value>
        struct is_nothrow_convertible_impl : false_type {};

        template <class From, class To>
        struct is_nothrow_convertible_impl<From, To, true>
            : integral_constant<
            bool,
            noexcept(detail::TestConvertible<To>(detail::Declval<From>()))
            > {
        };

    } // namespace detail

    template <class From, class To>
    struct is_nothrow_convertible
        : detail::is_nothrow_convertible_impl<From, To> {
    };

#endif

#if CPSTL_CPLUSPLUS >= 201402L
    template <class From, class To>
    constexpr bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;
#endif

} // namespace cpstd

#endif // CPSTL_TYPE_RELATIONSHIPS_H