#ifndef CPSTL_ITERATOR_FUNCTIONS_H
#define CPSTL_ITERATOR_FUNCTIONS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>
    #include <CPiterator.h>

    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    namespace cpstd {

        #if defined(CPSTL_USING_STL)

            using std::begin;
            using std::end;
            
        #else

            template <class Container>
            auto begin(Container& cont) -> decltype(cont.begin()) {
                return cont.begin();
            }

            template <class Container>
            auto begin(const Container& cont) -> decltype(cont.begin()) {
                return cont.begin();
            }

            template <class T, size_t N>
            constexpr T* begin(T (&arr)[N]) noexcept {
                return arr;
            }

            template <class Container>
            auto end(Container& cont) -> decltype(cont.end()) {
                return cont.end();
            }

            template <class Container>
            auto end(const Container& cont) -> decltype(cont.end()) {
                return cont.end();
            }

            template <class T, size_t N>
            constexpr T* end(T (&arr)[N]) noexcept {
                return arr + N;
            }

        #endif

    } // namespace cpstd

#endif // CPSTL_ITERATOR_FUNCTIONS_H