#ifndef CPSTL_ITERATOR_CLASS_H
#define CPSTL_ITERATOR_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    
    #include <CPiterator.h>

    namespace cpstd {

        // Conceptual representation of std::iterator as a base class
        template <class Category, class T, class Distance = cpstd::ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        struct iterator {
            using value_type = T;
            using difference_type = Distance;
            using pointer = Pointer;
            using reference = Reference;
            using iterator_category = Category;
        };

    #if defined(CPSTL_USING_STL)
        using input_iterator_tag = std::input_iterator_tag;
        using output_iterator_tag = std::output_iterator_tag;
        using forward_iterator_tag = std::forward_iterator_tag;
        using bidirectional_iterator_tag = std::bidirectional_iterator_tag;
        using random_access_iterator_tag = std::random_access_iterator_tag;

        template <class Category, class T, class Distance = cpstd::ptrdiff_t,
        class Pointer = T*, class Reference = T&>

        template<typename Iterator>
        using iterator_traits = std::iterator_traits<Iterator>;

        template <typename InputIt, typename Distance>
        void advance(InputIt& it, Distance n) {
            std::advance(it, n);
        }

        template <typename InputIt>
        auto distance(InputIt first, InputIt last) {
            return std::distance(first, last);
        }

        template <typename InputIt, typename Distance>
        InputIt next(InputIt it, Distance n) {
            return std::next(it, n);
        }

        template <typename BidirIt, typename Distance>
        BidirIt prev(BidirIt it, Distance n) {
            return std::prev(it, n);
        }

        template <typename Container>
        auto begin(Container& c) {
            return std::begin(c);
        }

        template <typename Container>
        auto end(Container& c) {
            return std::end(c);
        }

        template<typename T>
        using reverse_iterator = std::reverse_iterator<T>;


    #else
        struct input_iterator_tag {};
        struct output_iterator_tag {};

        struct forward_iterator_tag : public input_iterator_tag {};
        struct bidirectional_iterator_tag : public forward_iterator_tag {};
        struct random_access_iterator_tag : public bidirectional_iterator_tag {};

        template<typename Iterator>
        struct iterator_traits {
            using value_type = typename Iterator::value_type;
            using difference_type = typename Iterator::difference_type;
            using pointer = typename Iterator::pointer;
            using reference = typename Iterator::reference;
            using iterator_category = typename Iterator::iterator_category;
        };

        // Specialization for pointers
        template <typename T>
        struct iterator_traits<T*> {
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::random_access_iterator_tag;
        };

        template <typename InputIt, typename Distance>
        void advance(InputIt& it, Distance n) {
            if constexpr (cpstd::is_same_v<typename cpstd::iterator_traits<InputIt>::iterator_category, cpstd::random_access_iterator_tag>) {
               it += n;
            }
            else if constexpr (cpstd::is_same_v<typename cpstd::iterator_traits<InputIt>::iterator_category, cpstd::bidirectional_iterator_tag>) {
                if (n > 0) {
                    while (n > 0) {
                        ++it;
                        --n;
                    }
                }
                else {
                    while (n < 0) {
                        --it;
                        ++n;
                    }
                }
            }
            else if constexpr (cpstd::is_same_v<typename cpstd::iterator_traits<InputIt>::iterator_category, cpstd::forward_iterator_tag> || 
                cpstd::is_same_v<typename cpstd::iterator_traits<InputIt>::iterator_category, cpstd::input_iterator_tag>) {
                while (n > 0) {
                    ++it;
                    --n;
                }
            }
            else{
                while (n > 0) {
                    ++it;
                    --n;
                }
            }
        }

        template <typename InputIt>
        typename cpstd::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
            if constexpr (cpstd::is_same_v<typename cpstd::iterator_traits<InputIt>::iterator_category, cpstd::random_access_iterator_tag>) {
                return last - first;
            } 
            else {
                typename cpstd::iterator_traits<InputIt>::difference_type count = 0;
                while (first != last) {
                    ++first;
                    ++count;
                }
                return count;
            }
        }

        template <typename InputIt, typename Distance>
        InputIt next(InputIt it, Distance n) {
            advance(it, n);
            return it;
        }

        template <typename BidirIt, typename Distance>
        BidirIt prev(BidirIt it, Distance n) {
            advance(it, -n);
            return it;
        }

        template <class Container>
        typename Container::iterator begin(Container& cont) {
            return cont.begin();
        }

        template <class Container>
        typename Container::const_iterator begin(const Container& cont) {
            return cont.begin();
        }

        template <typename Container>
        typename Container::iterator end(Container& c) {
            return c.end();
        }

        template <typename Iterator>
        class reverse_iterator {
        public:
            using iterator_type = Iterator;
            using iterator_category = typename iterator_traits<Iterator>::iterator_category;
            using value_type = typename iterator_traits<Iterator>::value_type;
            using difference_type = typename iterator_traits<Iterator>::difference_type;
            using pointer = typename iterator_traits<Iterator>::pointer;
            using reference = typename iterator_traits<Iterator>::reference;

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

    #include "iterator/CPSTL_prefefined_iterators.h"

#endif//CPSTL_ITERATOR_CLASS_H
