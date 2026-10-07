#ifndef CPSTL_BACK_INSERT_ITERATOR_H
#define CPSTL_BACK_INSERT_ITERATOR_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>
    #include <CPutility.h>

    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    #include "CPSTL_Iterator.h"

    namespace cpstd {
        #if defined(CPSTL_USING_STL)

            template<typename T>
            using back_insert_iterator = std::back_insert_iterator<T>;

            template <class Container>
            back_insert_iterator<Container> back_inserter(Container& x) {
                return std::back_inserter(x);
            }

        #else

            template <class Container>
            class back_insert_iterator {
            protected:
                Container& container;

            public:
                typedef cpstd::output_iterator_tag iterator_category;
                typedef void value_type;
                typedef void difference_type;
                typedef void pointer;
                typedef void reference;
                typedef Container container_type;

                explicit back_insert_iterator(Container& x) : container(x) {}

                back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
                    container.push_back(value);
                    return *this;
                }

                back_insert_iterator& operator=(typename Container::value_type&& value) {
                    container.push_back(cpstd::move(value));
                    return *this;
                }

                back_insert_iterator<Container>& operator*() {
                    return *this;
                }

                back_insert_iterator<Container>& operator++() {
                    return *this;
                }

                back_insert_iterator<Container> operator++(int) {
                    return *this;
                }
            };

            template <class Container>
            back_insert_iterator<Container> back_inserter(Container& x) {
                return back_insert_iterator<Container>(x);
            }

        #endif
    }

#endif //CPSTL_BACK_INSERT_ITERATOR_H