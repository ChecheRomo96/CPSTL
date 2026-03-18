#ifndef CPSTL_CHARTRAITS_CLASS_TPP
#define CPSTL_CHARTRAITS_CLASS_TPP

#include "CPSTL_CharTraits.h"

namespace cpstd {

#ifndef CPSTL_USING_STL

    template <typename CharT>
    bool char_traits<CharT>::eq(
        const typename char_traits<CharT>::char_type& c1,
        const typename char_traits<CharT>::char_type& c2
    ) {
        return c1 == c2;
    }

    template <typename CharT>
    bool char_traits<CharT>::lt(
        const typename char_traits<CharT>::char_type& c1,
        const typename char_traits<CharT>::char_type& c2
    ) {
        return c1 < c2;
    }

    template <typename CharT>
    cpstd::size_t char_traits<CharT>::length(
        const typename char_traits<CharT>::char_type* str
    ) {
        cpstd::size_t len = 0;
        while (*str != typename char_traits<CharT>::char_type()) {
            ++len;
            ++str;
        }
        return len;
    }

    template <typename CharT>
    void char_traits<CharT>::assign(
        typename char_traits<CharT>::char_type& c1,
        const typename char_traits<CharT>::char_type& c2
    ) {
        c1 = c2;
    }

    template <typename CharT>
    typename char_traits<CharT>::char_type* char_traits<CharT>::assign(
        typename char_traits<CharT>::char_type* dest,
        cpstd::size_t count,
        typename char_traits<CharT>::char_type ch
    ) {
        for (cpstd::size_t i = 0; i < count; ++i) {
            dest[i] = ch;
        }
        return dest;
    }

    template <typename CharT>
    typename char_traits<CharT>::int_type char_traits<CharT>::compare(
        const typename char_traits<CharT>::char_type* str1,
        const typename char_traits<CharT>::char_type* str2,
        cpstd::size_t count
    ) {
        for (cpstd::size_t i = 0; i < count; ++i) {
            if (lt(str1[i], str2[i])) return -1;
            if (lt(str2[i], str1[i])) return 1;
        }
        return 0;
    }

    template <typename CharT>
    const typename char_traits<CharT>::char_type* char_traits<CharT>::find(
        const typename char_traits<CharT>::char_type* s,
        cpstd::size_t count,
        const typename char_traits<CharT>::char_type& ch
    ) {
        for (cpstd::size_t i = 0; i < count; ++i) {
            if (eq(s[i], ch)) {
                return s + i;
            }
        }
        return 0;
    }

    template <typename CharT>
    typename char_traits<CharT>::char_type* char_traits<CharT>::move(
        typename char_traits<CharT>::char_type* dest,
        const typename char_traits<CharT>::char_type* src,
        cpstd::size_t count
    ) {
        if (dest == src || count == 0) {
            return dest;
        }

        if (dest < src) {
            for (cpstd::size_t i = 0; i < count; ++i) {
                dest[i] = src[i];
            }
        } else {
            for (cpstd::size_t i = count; i > 0; --i) {
                dest[i - 1] = src[i - 1];
            }
        }

        return dest;
    }

    template <typename CharT>
    typename char_traits<CharT>::char_type* char_traits<CharT>::copy(
        typename char_traits<CharT>::char_type* dest,
        const typename char_traits<CharT>::char_type* src,
        cpstd::size_t count
    ) {
        for (cpstd::size_t i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
        return dest;
    }

    template <typename CharT>
    typename char_traits<CharT>::int_type char_traits<CharT>::eof() {
        return static_cast<typename char_traits<CharT>::int_type>(-1);
    }

    template <typename CharT>
    typename char_traits<CharT>::int_type char_traits<CharT>::not_eof(
        const typename char_traits<CharT>::int_type& c
    ) {
        return eq_int_type(c, eof()) ? 0 : c;
    }

    template <typename CharT>
    typename char_traits<CharT>::char_type char_traits<CharT>::to_char_type(
        const typename char_traits<CharT>::int_type& c
    ) {
        return static_cast<typename char_traits<CharT>::char_type>(c);
    }

    template <typename CharT>
    typename char_traits<CharT>::int_type char_traits<CharT>::to_int_type(
        const typename char_traits<CharT>::char_type& ch
    ) {
        return static_cast<typename char_traits<CharT>::int_type>(ch);
    }

    template <typename CharT>
    bool char_traits<CharT>::eq_int_type(
        const typename char_traits<CharT>::int_type& c1,
        const typename char_traits<CharT>::int_type& c2
    ) {
        return c1 == c2;
    }

#endif

} // namespace cpstd

#endif // CPSTL_CHARTRAITS_CLASS_TPP