#ifndef CPSTL_ITERATOR_CLASS_H
#define CPSTL_ITERATOR_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    

    
    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    
    namespace cpstd{
        #if defined(CPSTL_USING_STL)
            template <class Category, class T, class Distance = cpstd::ptrdiff_t, class Pointer = T*, class Reference = T&> 
            using iterator = std::iterator<Category, T, Distance, Pointer, Reference>;
        #else
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

#endif //CPSTL_ITERATOR_CLASS_H