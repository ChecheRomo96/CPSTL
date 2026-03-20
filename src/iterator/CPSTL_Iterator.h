#ifndef CPSTL_ITERATOR_CLASS_H
#define CPSTL_ITERATOR_CLASS_H

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

        #else

            template<class It>
            typename cpstd::iterator_traits<It>::difference_type
            distance(It first, It last)
            {
                typedef typename cpstd::iterator_traits<It>::iterator_category category;
                typedef typename cpstd::iterator_traits<It>::difference_type difference_type;

                static_assert(
                    cpstd::is_base_of<cpstd::input_iterator_tag, category>::value,
                    "cpstd::distance requires at least an input iterator"
                );

                difference_type result = 0;
                while (first != last) {
                    ++first;
                    ++result;
                }
                return result;
            }

        #endif

    }

#endif//CPSTL_ITERATOR_CLASS_H
