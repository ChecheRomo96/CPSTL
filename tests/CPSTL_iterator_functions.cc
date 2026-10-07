#include <gtest/gtest.h>

#include <CPiterator.h>
#include <CPvector>

TEST(IteratorFunctionsTest, BeginEndOnArraysAndContainers) {
    int values[4] = {1, 2, 3, 4};
    EXPECT_EQ(cpstd::begin(values), values);
    EXPECT_EQ(cpstd::end(values), values + 4);

    cpstd::vector<int> v = {5, 6};
    EXPECT_EQ(*cpstd::begin(v), 5);
    EXPECT_EQ(cpstd::end(v) - cpstd::begin(v), 2);
}

TEST(IteratorFunctionsTest, DistanceAdvanceNextPrev) {
    int values[5] = {0, 1, 2, 3, 4};
    EXPECT_EQ(cpstd::distance(values, values + 5), 5);
    EXPECT_EQ(cpstd::distance(values + 4, values), -4);

    int* it = values;
    cpstd::advance(it, 3);
    EXPECT_EQ(*it, 3);
    cpstd::advance(it, -2);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*cpstd::next(values), 1);
    EXPECT_EQ(*cpstd::next(values, 4), 4);
    EXPECT_EQ(*cpstd::prev(values + 5), 4);
}

TEST(IteratorFunctionsTest, ReverseIterator) {
    int values[3] = {1, 2, 3};
    cpstd::reverse_iterator<int*> first(values + 3);
    cpstd::reverse_iterator<int*> last(values);
    EXPECT_EQ(*first, 3);
    EXPECT_EQ(first[2], 1);
    EXPECT_EQ(last - first, 3);
    ++first;
    EXPECT_EQ(*first, 2);
    EXPECT_EQ(first.base(), values + 2);
    EXPECT_TRUE(first != last);
    EXPECT_TRUE(first < last);
}

TEST(IteratorFunctionsTest, BackInserter) {
    cpstd::vector<int> v;
    auto out = cpstd::back_inserter(v);
    for (int i = 0; i < 3; ++i) {
        *out++ = i;
    }
    ASSERT_EQ(v.size(), 3u);
    EXPECT_EQ(v[2], 2);
}
