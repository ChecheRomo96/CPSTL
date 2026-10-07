#if defined(ARDUINO)
    #include <Aunit.h>
    #include <aunit/contrib/gtest.h>
#endif

#if __has_include(<gtest/gtest.h>)
    #include <gtest/gtest.h>
#endif

#include <CPtype_traits.h>
#include <CPSTL.h>

#if defined(CPSTL_USING_STL)
    #include <iterator>
#endif

namespace {

    struct InputIterator {
        typedef int                               value_type;
        typedef long                              difference_type;
        typedef int*                              pointer;
        typedef int&                              reference;
        typedef cpstd::input_iterator_tag         iterator_category;

        pointer ptr;

        InputIterator(pointer p = 0) : ptr(p) {}

        reference operator*() const { return *ptr; }
        InputIterator& operator++() { ++ptr; return *this; }
        InputIterator operator++(int) { InputIterator tmp(*this); ++ptr; return tmp; }

        bool operator==(const InputIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const InputIterator& other) const { return ptr != other.ptr; }
    };

    struct ForwardIterator {
        typedef int                               value_type;
        typedef long                              difference_type;
        typedef int*                              pointer;
        typedef int&                              reference;
        typedef cpstd::forward_iterator_tag       iterator_category;

        pointer ptr;

        ForwardIterator(pointer p = 0) : ptr(p) {}

        reference operator*() const { return *ptr; }
        ForwardIterator& operator++() { ++ptr; return *this; }
        ForwardIterator operator++(int) { ForwardIterator tmp(*this); ++ptr; return tmp; }

        bool operator==(const ForwardIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ForwardIterator& other) const { return ptr != other.ptr; }
    };

    struct BidirectionalIterator {
        typedef int                               value_type;
        typedef long                              difference_type;
        typedef int*                              pointer;
        typedef int&                              reference;
        typedef cpstd::bidirectional_iterator_tag iterator_category;

        pointer ptr;

        BidirectionalIterator(pointer p = 0) : ptr(p) {}

        reference operator*() const { return *ptr; }
        BidirectionalIterator& operator++() { ++ptr; return *this; }
        BidirectionalIterator operator++(int) { BidirectionalIterator tmp(*this); ++ptr; return tmp; }
        BidirectionalIterator& operator--() { --ptr; return *this; }
        BidirectionalIterator operator--(int) { BidirectionalIterator tmp(*this); --ptr; return tmp; }

        bool operator==(const BidirectionalIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const BidirectionalIterator& other) const { return ptr != other.ptr; }
    };

    struct RandomAccessIterator {
        typedef int                               value_type;
        typedef long                              difference_type;
        typedef int*                              pointer;
        typedef int&                              reference;
        typedef cpstd::random_access_iterator_tag iterator_category;

        pointer ptr;

        RandomAccessIterator(pointer p = 0) : ptr(p) {}

        reference operator*() const { return *ptr; }
        RandomAccessIterator& operator++() { ++ptr; return *this; }
        RandomAccessIterator operator++(int) { RandomAccessIterator tmp(*this); ++ptr; return tmp; }
        RandomAccessIterator& operator--() { --ptr; return *this; }
        RandomAccessIterator operator--(int) { RandomAccessIterator tmp(*this); --ptr; return tmp; }

        RandomAccessIterator operator+(difference_type n) const { return RandomAccessIterator(ptr + n); }
        RandomAccessIterator operator-(difference_type n) const { return RandomAccessIterator(ptr - n); }
        difference_type operator-(const RandomAccessIterator& other) const {
            return static_cast<difference_type>(ptr - other.ptr);
        }

        bool operator==(const RandomAccessIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const RandomAccessIterator& other) const { return ptr != other.ptr; }
    };

    struct ConstRandomAccessIterator {
        typedef int                               value_type;
        typedef long                              difference_type;
        typedef const int*                        pointer;
        typedef const int&                        reference;
        typedef cpstd::random_access_iterator_tag iterator_category;

        pointer ptr;

        ConstRandomAccessIterator(pointer p = 0) : ptr(p) {}

        reference operator*() const { return *ptr; }
        ConstRandomAccessIterator& operator++() { ++ptr; return *this; }
        ConstRandomAccessIterator operator++(int) { ConstRandomAccessIterator tmp(*this); ++ptr; return tmp; }
        ConstRandomAccessIterator& operator--() { --ptr; return *this; }
        ConstRandomAccessIterator operator--(int) { ConstRandomAccessIterator tmp(*this); --ptr; return tmp; }

        bool operator==(const ConstRandomAccessIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstRandomAccessIterator& other) const { return ptr != other.ptr; }
    };

} // namespace

TEST(CPSTL_IteratorTraitsTest, InputIteratorNestedTypes) {
    using Traits = cpstd::iterator_traits<InputIterator>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::difference_type, long>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::input_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, ForwardIteratorNestedTypes) {
    using Traits = cpstd::iterator_traits<ForwardIterator>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::difference_type, long>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::forward_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, BidirectionalIteratorNestedTypes) {
    using Traits = cpstd::iterator_traits<BidirectionalIterator>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::difference_type, long>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::bidirectional_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, RandomAccessIteratorNestedTypes) {
    using Traits = cpstd::iterator_traits<RandomAccessIterator>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::difference_type, long>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::random_access_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, ConstRandomAccessIteratorNestedTypes) {
    using Traits = cpstd::iterator_traits<ConstRandomAccessIterator>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::difference_type, long>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, const int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, const int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::random_access_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, RawPointerSpecialization) {
    using Traits = cpstd::iterator_traits<int*>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::random_access_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, ConstRawPointerSpecialization) {
    using Traits = cpstd::iterator_traits<const int*>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, const int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, const int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::random_access_iterator_tag>::value));
}

// std::iterator_traits strips volatile from value_type only since C++20, so
// STL mode is checked against the standard it forwards to.
#if !defined(CPSTL_USING_STL) || CPSTL_CPLUSPLUS >= 202002L
TEST(CPSTL_IteratorTraitsTest, VolatileRawPointerSpecialization) {
    using Traits = cpstd::iterator_traits<volatile int*>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, volatile int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, volatile int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::random_access_iterator_tag>::value));
}

TEST(CPSTL_IteratorTraitsTest, ConstVolatileRawPointerSpecialization) {
    using Traits = cpstd::iterator_traits<const volatile int*>;

    ASSERT_TRUE((cpstd::is_same<typename Traits::value_type, int>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::pointer, const volatile int*>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::reference, const volatile int&>::value));
    ASSERT_TRUE((cpstd::is_same<typename Traits::iterator_category, cpstd::random_access_iterator_tag>::value));
}
#endif

TEST(CPSTL_IteratorTraitsTest, InputIteratorUsage) {
    int values[3] = {10, 20, 30};
    InputIterator it(values);

    using Traits = cpstd::iterator_traits<InputIterator>;
    typename Traits::reference ref = *it;

    ASSERT_EQ(ref, 10);

    ++it;
    ASSERT_EQ(*it, 20);

    InputIterator old = it++;
    ASSERT_EQ(*old, 20);
    ASSERT_EQ(*it, 30);
}

TEST(CPSTL_IteratorTraitsTest, ForwardIteratorUsage) {
    int values[3] = {1, 2, 3};
    ForwardIterator it(values);

    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);

    ForwardIterator old = it++;
    ASSERT_EQ(*old, 2);
    ASSERT_EQ(*it, 3);
}

TEST(CPSTL_IteratorTraitsTest, BidirectionalIteratorUsage) {
    int values[3] = {4, 5, 6};
    BidirectionalIterator it(values + 1);

    ASSERT_EQ(*it, 5);

    ++it;
    ASSERT_EQ(*it, 6);

    --it;
    ASSERT_EQ(*it, 5);

    BidirectionalIterator old = it--;
    ASSERT_EQ(*old, 5);
    ASSERT_EQ(*it, 4);
}

TEST(CPSTL_IteratorTraitsTest, RandomAccessIteratorUsage) {
    int values[5] = {7, 8, 9, 10, 11};
    RandomAccessIterator it(values);

    ASSERT_EQ(*it, 7);
    ASSERT_EQ(*(it + 2), 9);
    ASSERT_EQ(*((it + 4) - 1), 10);
    ASSERT_EQ((it + 4) - it, 4);
}

TEST(CPSTL_IteratorTraitsTest, ConstRandomAccessIteratorUsage) {
    const int values[3] = {100, 200, 300};
    ConstRandomAccessIterator it(values);

    using Traits = cpstd::iterator_traits<ConstRandomAccessIterator>;
    typename Traits::reference ref = *it;

    ASSERT_EQ(ref, 100);
    ++it;
    ASSERT_EQ(*it, 200);
}

TEST(CPSTL_IteratorTraitsTest, RawPointerUsage) {
    int values[3] = {12, 13, 14};
    int* it = values;

    using Traits = cpstd::iterator_traits<int*>;
    typename Traits::pointer ptr = it;
    typename Traits::reference ref = *ptr;

    ASSERT_EQ(ref, 12);
    ++ptr;
    ASSERT_EQ(*ptr, 13);
}

TEST(CPSTL_IteratorTraitsTest, ConstRawPointerUsage) {
    const int values[3] = {21, 22, 23};
    const int* it = values;

    using Traits = cpstd::iterator_traits<const int*>;
    typename Traits::pointer ptr = it;
    typename Traits::reference ref = *ptr;

    ASSERT_EQ(ref, 21);
    ++ptr;
    ASSERT_EQ(*ptr, 22);
}

TEST(CPSTL_IteratorTraitsTest, DifferenceTypeCanBeUsed) {
    using Traits1 = cpstd::iterator_traits<RandomAccessIterator>;
    using Traits2 = cpstd::iterator_traits<int*>;

    typename Traits1::difference_type d1 = 5;
    typename Traits2::difference_type d2 = 7;

    ASSERT_EQ(d1, 5);
    ASSERT_EQ(d2, 7);
}

TEST(CPSTL_IteratorTraitsTest, CategoryInheritanceChecks) {
    ASSERT_EQ(
        true,
        (cpstd::is_base_of<
            cpstd::input_iterator_tag,
            cpstd::forward_iterator_tag
        >::value)
    );

    ASSERT_EQ(
        true,
        (cpstd::is_base_of<
            cpstd::forward_iterator_tag,
            cpstd::bidirectional_iterator_tag
        >::value)
    );

    ASSERT_EQ(
        true,
        (cpstd::is_base_of<
            cpstd::bidirectional_iterator_tag,
            cpstd::random_access_iterator_tag
        >::value)
    );
}

#if defined(CPSTL_USING_STL)

TEST(CPSTL_IteratorTraitsTest, CrossVerificationInputIteratorWithStd) {
    using CpTraits  = cpstd::iterator_traits<InputIterator>;
    using StdTraits = std::iterator_traits<InputIterator>;

    ASSERT_TRUE((cpstd::is_same<typename CpTraits::value_type, typename StdTraits::value_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::difference_type, typename StdTraits::difference_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::pointer, typename StdTraits::pointer>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::reference, typename StdTraits::reference>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::iterator_category, typename StdTraits::iterator_category>::value));
}

TEST(CPSTL_IteratorTraitsTest, CrossVerificationForwardIteratorWithStd) {
    using CpTraits  = cpstd::iterator_traits<ForwardIterator>;
    using StdTraits = std::iterator_traits<ForwardIterator>;

    ASSERT_TRUE((cpstd::is_same<typename CpTraits::value_type, typename StdTraits::value_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::difference_type, typename StdTraits::difference_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::pointer, typename StdTraits::pointer>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::reference, typename StdTraits::reference>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::iterator_category, typename StdTraits::iterator_category>::value));
}

TEST(CPSTL_IteratorTraitsTest, CrossVerificationBidirectionalIteratorWithStd) {
    using CpTraits  = cpstd::iterator_traits<BidirectionalIterator>;
    using StdTraits = std::iterator_traits<BidirectionalIterator>;

    ASSERT_TRUE((cpstd::is_same<typename CpTraits::value_type, typename StdTraits::value_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::difference_type, typename StdTraits::difference_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::pointer, typename StdTraits::pointer>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::reference, typename StdTraits::reference>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::iterator_category, typename StdTraits::iterator_category>::value));
}

TEST(CPSTL_IteratorTraitsTest, CrossVerificationRandomAccessIteratorWithStd) {
    using CpTraits  = cpstd::iterator_traits<RandomAccessIterator>;
    using StdTraits = std::iterator_traits<RandomAccessIterator>;

    ASSERT_TRUE((cpstd::is_same<typename CpTraits::value_type, typename StdTraits::value_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::difference_type, typename StdTraits::difference_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::pointer, typename StdTraits::pointer>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::reference, typename StdTraits::reference>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::iterator_category, typename StdTraits::iterator_category>::value));
}

TEST(CPSTL_IteratorTraitsTest, CrossVerificationRawPointerWithStd) {
    using CpTraits  = cpstd::iterator_traits<int*>;
    using StdTraits = std::iterator_traits<int*>;

    ASSERT_TRUE((cpstd::is_same<typename CpTraits::value_type, typename StdTraits::value_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::difference_type, typename StdTraits::difference_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::pointer, typename StdTraits::pointer>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::reference, typename StdTraits::reference>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::iterator_category, typename StdTraits::iterator_category>::value));
}

TEST(CPSTL_IteratorTraitsTest, CrossVerificationConstRawPointerWithStd) {
    using CpTraits  = cpstd::iterator_traits<const int*>;
    using StdTraits = std::iterator_traits<const int*>;

    ASSERT_TRUE((cpstd::is_same<typename CpTraits::value_type, typename StdTraits::value_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::difference_type, typename StdTraits::difference_type>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::pointer, typename StdTraits::pointer>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::reference, typename StdTraits::reference>::value));
    ASSERT_TRUE((cpstd::is_same<typename CpTraits::iterator_category, typename StdTraits::iterator_category>::value));
}

#endif
