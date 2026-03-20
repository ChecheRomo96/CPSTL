#ifndef CPSTL_ITERATOR_PRIMITIVES_H
#define CPSTL_ITERATOR_PRIMITIVES_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    

    
    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    
    namespace cpstd{
        #if defined(CPSTL_USING_STL)
            using input_iterator_tag = std::input_iterator_tag;
            using output_iterator_tag = std::output_iterator_tag;
            using forward_iterator_tag = std::forward_iterator_tag;
            using bidirectional_iterator_tag = std::bidirectional_iterator_tag;
            using random_access_iterator_tag = std::random_access_iterator_tag;
            using contiguous_iterator_tag  = std::contiguous_iterator_tag;

            template <class Category, class T, class Distance = cpstd::ptrdiff_t, class Pointer = T*, class Reference = T&> 
            using iterator = std::iterator<Category, T, Distance, Pointer, Reference>;

        #else
            struct input_iterator_tag {};
            struct output_iterator_tag {};
            struct forward_iterator_tag : public input_iterator_tag {};
            struct bidirectional_iterator_tag : public forward_iterator_tag {};
            struct random_access_iterator_tag : public bidirectional_iterator_tag {};
            struct contiguous_iterator_tag : public random_access_iterator_tag {};
            
            template <class Category, class T, class Distance = cpstd::ptrdiff_t, class Pointer = T*, class Reference = T&> 
            struct iterator {
                typedef T         value_type;
                typedef Distance  difference_type;
                typedef Pointer   pointer;
                typedef Reference reference;
                typedef Category  iterator_category;
            };
        #endif
    }

    #include "CPSTL_iterator_traits.h"

#endif //CPSTL_ITERATOR_PRIMITIVES_H