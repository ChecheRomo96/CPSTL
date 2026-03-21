#ifndef CPSTL_TYPE_TRAITS_H
#define CPSTL_TYPE_TRAITS_H

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
}