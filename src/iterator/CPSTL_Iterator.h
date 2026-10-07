#ifndef CPSTL_ITERATOR_MODULE_H
#define CPSTL_ITERATOR_MODULE_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    

    
    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    
    #include "Primitives/CPSTL_iterator_primitives.h"
    #include "Primitives/CPSTL_iterator_class.h"
    #include "Primitives/CPSTL_iterator_traits.h"
    
    #include "CPSTL_iterator_functions.h"
    #include "CPSTL_predefined_iterators.h"

    namespace cpstd {

        #ifdef CPSTL_USING_STL

            using std::distance;
            using std::advance;
            using std::next;
            using std::prev;

        #else

            namespace detail {
                template <class It>
                typename cpstd::iterator_traits<It>::difference_type
                distance(It first, It last, cpstd::input_iterator_tag) {
                    typename cpstd::iterator_traits<It>::difference_type result = 0;
                    for (; first != last; ++first) {
                        ++result;
                    }
                    return result;
                }

                template <class It>
                typename cpstd::iterator_traits<It>::difference_type
                distance(It first, It last, cpstd::random_access_iterator_tag) {
                    return last - first;
                }

                template <class It, class Distance>
                void advance(It& it, Distance n, cpstd::input_iterator_tag) {
                    for (; n > 0; --n) {
                        ++it;
                    }
                }

                template <class It, class Distance>
                void advance(It& it, Distance n, cpstd::bidirectional_iterator_tag) {
                    for (; n > 0; --n) {
                        ++it;
                    }
                    for (; n < 0; ++n) {
                        --it;
                    }
                }

                template <class It, class Distance>
                void advance(It& it, Distance n, cpstd::random_access_iterator_tag) {
                    it += n;
                }
            }

            //! @brief Number of increments from `first` to `last` (constant time
            //! for random-access iterators).
            template <class It>
            typename cpstd::iterator_traits<It>::difference_type distance(It first, It last) {
                return detail::distance(first, last, typename cpstd::iterator_traits<It>::iterator_category());
            }

            //! @brief Moves `it` by `n` (negative only for bidirectional iterators).
            template <class It, class Distance>
            void advance(It& it, Distance n) {
                detail::advance(it, n, typename cpstd::iterator_traits<It>::iterator_category());
            }

            template <class It>
            It next(It it, typename cpstd::iterator_traits<It>::difference_type n = 1) {
                cpstd::advance(it, n);
                return it;
            }

            template <class It>
            It prev(It it, typename cpstd::iterator_traits<It>::difference_type n = 1) {
                cpstd::advance(it, -n);
                return it;
            }

        #endif

    }

#endif//CPSTL_ITERATOR_MODULE_H
