#ifndef CPSTL_REVERSE_ITERATOR_H
#define CPSTL_REVERSE_ITERATOR_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    

    namespace cpstd {
    #if defined(CPSTL_USING_STL)
        template<typename T>
        using reverse_iterator = std::reverse_iterator<T>;
    #else
        template <typename Iterator>
        class reverse_iterator {
        public:
            using iterator_type = Iterator;
            using iterator_category = typename cpstd::iterator_traits<iterator_type>::iterator_category;
            using value_type = typename cpstd::iterator_traits<iterator_type>::value_type;
            using difference_type = typename cpstd::iterator_traits<iterator_type>::difference_type;
            using pointer = typename cpstd::iterator_traits<iterator_type>::pointer;
            using reference = typename cpstd::iterator_traits<iterator_type>::reference;

            reverse_iterator() = default;
            explicit reverse_iterator(iterator_type it) : current(it) {}

            value_type operator*() const {
                iterator_type tmp = current;
                return *(--tmp);
            }

            reverse_iterator& operator++() {
                --current;
                return *this;
            }

            reverse_iterator operator++(int) {
                reverse_iterator tmp = *this;
                --current;
                return tmp;
            }

            reverse_iterator& operator--() {
                ++current;
                return *this;
            }

            reverse_iterator operator--(int) {
                reverse_iterator tmp = *this;
                ++current;
                return tmp;
            }

            reference operator[](difference_type n) const {
                return current[-n - 1];
            }

            reverse_iterator& operator+=(difference_type n) {
                current -= n;
                return *this;
            }

            reverse_iterator operator+(difference_type n) const {
                reverse_iterator tmp = *this;
                tmp += n;
                return tmp;
            }

            reverse_iterator& operator-=(difference_type n) {
                current += n;
                return *this;
            }

            reverse_iterator operator-(difference_type n) const {
                reverse_iterator tmp = *this;
                tmp -= n;
                return tmp;
            }

            difference_type operator-(const reverse_iterator& other) const {
                return other.current - current;
            }

            iterator_type base() const { return current; }

            friend bool operator==(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return lhs.current == rhs.current;
            }

            friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return !(lhs == rhs);
            }

            friend bool operator<(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return lhs.current > rhs.current;
            }

            friend bool operator>(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return lhs.current < rhs.current;
            }

            friend bool operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return !(rhs < lhs);
            }

            friend bool operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return !(lhs < rhs);
            }

            friend reverse_iterator operator+(typename reverse_iterator::difference_type n, const reverse_iterator& it) {
                return it + n;
            }

            friend typename reverse_iterator::difference_type operator-(const reverse_iterator& lhs, const reverse_iterator& rhs) {
                return rhs.current - lhs.current;
            }

        private:
            iterator_type current;
        };
    #endif
    }
    
#endif//CPSTL_REVERSE_ITERATOR_H