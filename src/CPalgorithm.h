#ifndef CROSS_PLATFORM_ALGORITHM_H
#define CROSS_PLATFORM_ALGORITHM_H

    #include <CPSTL_BuildSettings.h>
    #include <CPutility.h>

    #if defined(CPSTL_USING_STL)
        #include <algorithm>
    #endif

    //! @file CPalgorithm.h
    //! @brief A subset of `<algorithm>`: min, max, copy, copy_backward, fill,
    //! equal, find, iter_swap and sort.
    //!
    //! In STL mode these are the std functions. Otherwise `sort` is a heapsort:
    //! O(n log n) in the worst case, no recursion and no extra memory, which
    //! suits small stacks; like `std::sort` it is not stable.

    #ifdef min
        #undef min
    #endif
    #ifdef max
        #undef max
    #endif

    namespace cpstd {

    #if defined(CPSTL_USING_STL)

        using std::min;
        using std::max;
        using std::copy;
        using std::copy_backward;
        using std::fill;
        using std::equal;
        using std::find;
        using std::iter_swap;
        using std::sort;

    #else

        template <class T>
        constexpr const T& min(const T& a, const T& b) { return (b < a) ? b : a; }

        template <class T, class Compare>
        constexpr const T& min(const T& a, const T& b, Compare comp) { return comp(b, a) ? b : a; }

        template <class T>
        constexpr const T& max(const T& a, const T& b) { return (a < b) ? b : a; }

        template <class T, class Compare>
        constexpr const T& max(const T& a, const T& b, Compare comp) { return comp(a, b) ? b : a; }

        template <class InputIterator, class OutputIterator>
        OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
            for (; first != last; ++first, ++result) {
                *result = *first;
            }
            return result;
        }

        template <class BidirectionalIterator1, class BidirectionalIterator2>
        BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
                                             BidirectionalIterator2 result) {
            while (first != last) {
                *(--result) = *(--last);
            }
            return result;
        }

        template <class ForwardIterator, class T>
        void fill(ForwardIterator first, ForwardIterator last, const T& value) {
            for (; first != last; ++first) {
                *first = value;
            }
        }

        template <class InputIterator1, class InputIterator2>
        bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
            for (; first1 != last1; ++first1, ++first2) {
                if (!(*first1 == *first2)) {
                    return false;
                }
            }
            return true;
        }

        template <class InputIterator, class T>
        InputIterator find(InputIterator first, InputIterator last, const T& value) {
            for (; first != last; ++first) {
                if (*first == value) {
                    return first;
                }
            }
            return first;
        }

        template <class ForwardIterator1, class ForwardIterator2>
        void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
            cpstd::swap(*a, *b);
        }

        namespace detail {

            // Restores the max-heap property below `root` in heap[0, size).
            template <class RandomAccessIterator, class Size, class Compare>
            void sift_down(RandomAccessIterator heap, Size root, Size size, Compare& comp) {
                for (;;) {
                    Size child = root * 2 + 1;
                    if (child >= size) {
                        return;
                    }
                    if (child + 1 < size && comp(heap[child], heap[child + 1])) {
                        ++child;
                    }
                    if (!comp(heap[root], heap[child])) {
                        return;
                    }
                    cpstd::iter_swap(heap + root, heap + child);
                    root = child;
                }
            }

            struct less {
                template <class T>
                bool operator()(const T& a, const T& b) const { return a < b; }
            };
        }

        //! @brief Sorts `[first, last)` so `comp` holds between neighbours (heapsort).
        template <class RandomAccessIterator, class Compare>
        void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
            if (last - first < 2) {
                return;
            }
            const auto size = last - first;
            for (auto root = size / 2; root > 0; --root) {
                detail::sift_down(first, root - 1, size, comp);
            }
            for (auto end = size - 1; end > 0; --end) {
                cpstd::iter_swap(first, first + end);
                detail::sift_down(first, decltype(end)(0), end, comp);
            }
        }

        //! @brief Sorts `[first, last)` in ascending order with `operator<`.
        template <class RandomAccessIterator>
        void sort(RandomAccessIterator first, RandomAccessIterator last) {
            detail::less comp;
            cpstd::sort(first, last, comp);
        }

    #endif

    }

#endif//CROSS_PLATFORM_ALGORITHM_H
