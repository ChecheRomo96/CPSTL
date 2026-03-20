#ifndef CPSTL_REVERSE_ITERATOR_H
#define CPSTL_REVERSE_ITERATOR_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>

    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    #include "CPSTL_iterator.h"
    #include "Primitives/CPSTL_iterator_traits.h"

    namespace cpstd {

        #if defined(CPSTL_USING_STL)

            template<typename T>
            using reverse_iterator = std::reverse_iterator<T>;

        #else

            template <class Iterator>
            class reverse_iterator{
            public:
                typedef Iterator                                              iterator_type;
                typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
                typedef typename iterator_traits<Iterator>::value_type         value_type;
                typedef typename iterator_traits<Iterator>::difference_type    difference_type;
                typedef typename iterator_traits<Iterator>::pointer            pointer;
                typedef typename iterator_traits<Iterator>::reference          reference;

            protected:
                Iterator current;

            public:
                reverse_iterator() : current() {}

                explicit reverse_iterator(Iterator x) : current(x) {}

                template <class U>
                reverse_iterator(const reverse_iterator<U>& x) 
                    : current(x.base()) {}

                Iterator base() const {
                    return current;
                }

                reference operator*() const {
                    Iterator tmp = current;
                    --tmp;
                    return *tmp;
                }

                pointer operator->() const {
                    return &(operator*());
                }

                reference operator[](difference_type n) const {
                    return current[-n - 1];
                }

                reverse_iterator& operator++() {
                    --current;
                    return *this;
                }

                reverse_iterator operator++(int) {
                    reverse_iterator tmp(*this);
                    --current;
                    return tmp;
                }

                reverse_iterator& operator--() {
                    ++current;
                    return *this;
                }

                reverse_iterator operator--(int) {
                    reverse_iterator tmp(*this);
                    ++current;
                    return tmp;
                }

                reverse_iterator operator+(difference_type n) const {
                    return reverse_iterator(current - n);
                }

                reverse_iterator& operator+=(difference_type n) {
                    current -= n;
                    return *this;
                }

                reverse_iterator operator-(difference_type n) const {
                    return reverse_iterator(current + n);
                }

                reverse_iterator& operator-=(difference_type n) {
                    current += n;
                    return *this;
                }

            };

            template <class Iterator>
            bool operator==(const reverse_iterator<Iterator>& x,
                            const reverse_iterator<Iterator>& y) {
                return x.base() == y.base();
            }

            template <class Iterator>
            bool operator!=(const reverse_iterator<Iterator>& x,
                            const reverse_iterator<Iterator>& y) {
                return !(x == y);
            }

            template <class Iterator>
            bool operator<(const reverse_iterator<Iterator>& x,
                           const reverse_iterator<Iterator>& y) {
                return y.base() < x.base();
            }

            template <class Iterator>
            bool operator>(const reverse_iterator<Iterator>& x,
                           const reverse_iterator<Iterator>& y) {
                return y < x;
            }

            template <class Iterator>
            bool operator<=(const reverse_iterator<Iterator>& x,
                            const reverse_iterator<Iterator>& y) {
                return !(y < x);
            }

            template <class Iterator>
            bool operator>=(const reverse_iterator<Iterator>& x,
                            const reverse_iterator<Iterator>& y) {
                return !(x < y);
            }

            template <class Iterator>
            typename reverse_iterator<Iterator>::difference_type
            operator-(const reverse_iterator<Iterator>& x,
                      const reverse_iterator<Iterator>& y) {
                return y.base() - x.base();
            }
            
            template <class Iterator>
            reverse_iterator<Iterator>
            operator-(typename reverse_iterator<Iterator>::difference_type n,
                    const reverse_iterator<Iterator>& x) {
                return reverse_iterator<Iterator>(x.base() + n);
            }

            template <class Iterator>
            reverse_iterator<Iterator>
            operator+(typename reverse_iterator<Iterator>::difference_type n,
                      const reverse_iterator<Iterator>& x) {
                return reverse_iterator<Iterator>(x.base() - n);
            }

        #endif
    }

#endif // CPSTL_REVERSE_ITERATOR_H