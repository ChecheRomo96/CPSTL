#ifndef CPSTL_ITERATOR_H
#define CPSTL_ITERATOR_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    

    namespace cpstd {
    #if defined(CPSTL_USING_STL)

        using input_iterator_tag = std::input_iterator_tag;
        using output_iterator_tag = std::output_iterator_tag;
        using forward_iterator_tag = std::forward_iterator_tag;
        using bidirectional_iterator_tag = std::bidirectional_iterator_tag;
        using random_access_iterator_tag = std::random_access_iterator_tag;


        template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        using iterator = std::iterator<Category, T, Distance, Pointer, Reference>;

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

    #else
        struct input_iterator_tag {};
        struct output_iterator_tag {};

        struct forward_iterator_tag : public input_iterator_tag {};
        struct bidirectional_iterator_tag : public forward_iterator_tag {};
        struct random_access_iterator_tag : public bidirectional_iterator_tag {};


        // Conceptual representation of std::iterator as a base class
        template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        struct iterator {
            using value_type = T;
            using difference_type = Distance;
            using pointer = Pointer;
            using reference = Reference;
            using iterator_category = Category;
          };

        template<typename Iterator>
        struct iterator_traits {
            using value_type = typename Iterator::value_type;
            using difference_type = typename Iterator::difference_type;
            using pointer = typename Iterator::pointer;
            using reference = typename Iterator::reference;
            using iterator_category = typename Iterator::iterator_category;
        };

        template <typename InputIt, typename Distance>
        void advance(InputIt& it, Distance n) {
            if constexpr (cpstd::is_same_v<typename cpstd::iterator_traits<InputIt>::iterator_category, cpstd::random_access_iterator_tag>) {
               it += n;
            }

            while (n > 0) {
                ++it;
                --n;
            }
            while (n < 0) {
                --it;
                ++n;
            }
        }

        template <typename InputIt>
        auto distance(InputIt first, InputIt last) {
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

        template <typename Container>
        typename Container::iterator begin(Container& c) {
            return c.begin();
        }

        template <typename Container>
        typename Container::iterator end(Container& c) {
            return c.end();
        }
    #endif
    }


#endif//CPSTL_ITERATOR_H
