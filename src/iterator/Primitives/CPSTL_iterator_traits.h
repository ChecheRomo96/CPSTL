#ifndef CPSTL_ITERATOR_TRAITS_H
#define CPSTL_ITERATOR_TRAITS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    

    
    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    namespace cpstd {
        #if defined(CPSTL_USING_STL)
            template<typename T>
            using iterator_traits = std::iterator_traits<T>;
        #else
            template<class Iterator>
            struct iterator_traits {
                typedef typename Iterator::difference_type   difference_type;
                typedef typename Iterator::value_type        value_type;
                typedef typename Iterator::pointer           pointer;
                typedef typename Iterator::reference         reference;
                typedef typename Iterator::iterator_category iterator_category;
            };

            template<class T>
            struct iterator_traits<T*> {
                typedef cpstd::ptrdiff_t                  difference_type;
                typedef T                                 value_type;
                typedef T*                                pointer;
                typedef T&                                reference;
                typedef cpstd::random_access_iterator_tag iterator_category;
            };

            template<class T>
            struct iterator_traits<const T*> {
                typedef cpstd::ptrdiff_t                  difference_type;
                typedef T                                 value_type;
                typedef const T*                          pointer;
                typedef const T&                          reference;
                typedef cpstd::random_access_iterator_tag iterator_category;
            };
        #endif
    }

#endif //CPSTL_ITERATOR_TRAITS_H