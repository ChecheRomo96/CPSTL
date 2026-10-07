#include <gtest/gtest.h>

#include <CPalgorithm>
#include <algorithm>
#include <CPvector>

#include "TestSupport.h"

TEST(AlgorithmTest, MinAndMax) {
    EXPECT_EQ(cpstd::min(3, 7), 3);
    EXPECT_EQ(cpstd::max(3, 7), 7);
    const int a = 5;
    const int b = 5;
    EXPECT_EQ(&cpstd::min(a, b), &a);  // ties return the first argument
    EXPECT_EQ(&cpstd::max(a, b), &a);
    auto greater = [](int x, int y) { return x > y; };
    EXPECT_EQ(cpstd::min(3, 7, greater), 7);
    EXPECT_EQ(cpstd::max(3, 7, greater), 3);
}

TEST(AlgorithmTest, CopyFillEqualFind) {
    const int source[] = {1, 2, 3, 4};
    int target[4] = {0, 0, 0, 0};
    EXPECT_EQ(cpstd::copy(source, source + 4, target), target + 4);
    EXPECT_TRUE(cpstd::equal(source, source + 4, target));

    int overlap[6] = {1, 2, 3, 4, 0, 0};
    cpstd::copy_backward(overlap, overlap + 4, overlap + 6);
    const int shifted[] = {1, 2, 1, 2, 3, 4};
    EXPECT_TRUE(cpstd::equal(overlap, overlap + 6, shifted));

    cpstd::fill(target, target + 4, 9);
    EXPECT_EQ(target[3], 9);
    EXPECT_EQ(cpstd::find(source, source + 4, 3), source + 2);
    EXPECT_EQ(cpstd::find(source, source + 4, 8), source + 4);
}

TEST(AlgorithmTest, SortsEveryPermutationOfSmallArrays) {
    // All 5040 permutations of 7 elements, plus duplicates.
    int values[7] = {0, 1, 2, 3, 4, 5, 6};
    int count = 0;
    do {
        int copy[7];
        cpstd::copy(values, values + 7, copy);
        cpstd::sort(copy, copy + 7);
        for (int i = 0; i < 7; ++i) {
            ASSERT_EQ(copy[i], i);
        }
        ++count;
    } while (std::next_permutation(values, values + 7));
    EXPECT_EQ(count, 5040);

    int duplicates[] = {3, 1, 3, 1, 2, 2, 0};
    cpstd::sort(duplicates, duplicates + 7);
    const int sorted[] = {0, 1, 1, 2, 2, 3, 3};
    EXPECT_TRUE(cpstd::equal(duplicates, duplicates + 7, sorted));
}

TEST(AlgorithmTest, SortsWithComparatorAndNonIntTypes) {
    cpstd::vector<double> v = {2.5, -1.0, 9.75, 0.5};
    cpstd::sort(v.begin(), v.end(), [](double a, double b) { return a > b; });
    EXPECT_DOUBLE_EQ(v[0], 9.75);
    EXPECT_DOUBLE_EQ(v[3], -1.0);

    cpstd::vector<cpstl_test::Tracked> t;
    for (int value : {4, 1, 3, 2}) {
        t.emplace_back(value);
    }
    cpstd::sort(t.begin(), t.end());
    EXPECT_EQ(t[0].value, 1);
    EXPECT_EQ(t[3].value, 4);

    int single = 1;
    cpstd::sort(&single, &single + 1);
    cpstd::sort(&single, &single);
    EXPECT_EQ(single, 1);
}

TEST(AlgorithmTest, SortsLargeInput) {
    cpstd::vector<int> v;
    unsigned seed = 12345u;
    for (int i = 0; i < 5000; ++i) {
        seed = seed * 1103515245u + 12345u;
        v.push_back(static_cast<int>(seed >> 16) % 1000);
    }
    cpstd::sort(v.begin(), v.end());
    for (cpstd::size_t i = 1; i < v.size(); ++i) {
        ASSERT_LE(v[i - 1], v[i]);
    }
}
