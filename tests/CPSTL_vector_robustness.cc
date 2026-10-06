// Behaviour of cpstd::vector beyond the basic API: growth policy, element
// lifetimes, aliasing, types without a default constructor, ordering and, in
// the CPSTL implementation, allocation failure.

#include <gtest/gtest.h>

#include <CPvector>

#include "TestSupport.h"

using cpstl_test::NoDefault;
using cpstl_test::Tracked;

TEST(VectorGrowth, PushBackGrowsGeometrically) {
    cpstd::vector<int> v;
    int reallocations = 0;
    cpstd::size_t capacity = v.capacity();
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
        if (v.capacity() != capacity) {
            ++reallocations;
            capacity = v.capacity();
        }
    }
    ASSERT_EQ(v.size(), 1000u);
    EXPECT_LE(reallocations, 20);  // logarithmic, not one per element
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(v[static_cast<cpstd::size_t>(i)], i);
    }
}

TEST(VectorGrowth, ReserveAndShrinkToFit) {
    cpstd::vector<int> v;
    v.reserve(50);
    EXPECT_GE(v.capacity(), 50u);
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    v.push_back(2);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 2u);
    EXPECT_EQ(v[1], 2);
    v.clear();
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 0u);
}

TEST(VectorLifetime, EveryElementIsDestroyedOnce) {
    Tracked::Reset();
    {
        cpstd::vector<Tracked> v;
        for (int i = 0; i < 20; ++i) {
            v.emplace_back(i);
        }
        EXPECT_EQ(Tracked::Live, 20);
        v.erase(v.begin() + 3, v.begin() + 8);
        EXPECT_EQ(Tracked::Live, 15);
        v.insert(v.begin() + 2, 4, Tracked(99));
        EXPECT_EQ(Tracked::Live, 19);
        v.resize(5);
        EXPECT_EQ(Tracked::Live, 5);
        cpstd::vector<Tracked> copy(v);
        EXPECT_EQ(Tracked::Live, 10);
        copy = v;
        EXPECT_EQ(Tracked::Live, 10);
        v.pop_back();
        EXPECT_EQ(Tracked::Live, 9);
    }
    EXPECT_EQ(Tracked::Live, 0);
}

TEST(VectorAliasing, PushBackOfOwnElementDuringGrowth) {
    cpstd::vector<Tracked> v;
    v.emplace_back(7);
    v.shrink_to_fit();
    ASSERT_EQ(v.size(), v.capacity());
    v.push_back(v[0]);
    ASSERT_EQ(v.size(), 2u);
    EXPECT_EQ(v[1].value, 7);
}

TEST(VectorAliasing, InsertOfOwnElement) {
    cpstd::vector<int> v = {1, 2, 3, 4};
    v.insert(v.begin(), v[3]);
    ASSERT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 4);
    EXPECT_EQ(v[4], 4);

    v.insert(v.begin() + 1, 3, v[2]);  // v[2] == 2 moves while inserting
    ASSERT_EQ(v.size(), 8u);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 2);
    EXPECT_EQ(v[4], 1);
}

TEST(VectorAliasing, ResizeWithOwnElement) {
    cpstd::vector<int> v = {5};
    v.shrink_to_fit();
    v.resize(4, v[0]);
    ASSERT_EQ(v.size(), 4u);
    EXPECT_EQ(v[3], 5);
}

TEST(VectorInsert, EveryPositionAndCount) {
    // Inserting n elements at every position of every small vector exercises
    // both the in-place shift (with and without spare capacity) and growth.
    for (int size = 0; size <= 6; ++size) {
        for (int pos = 0; pos <= size; ++pos) {
            for (int n = 0; n <= 4; ++n) {
                for (int spare = 0; spare <= 5; spare += 5) {
                    cpstd::vector<int> v;
                    v.reserve(static_cast<cpstd::size_t>(size + spare));
                    for (int i = 0; i < size; ++i) {
                        v.push_back(i);
                    }
                    v.insert(v.begin() + pos, static_cast<cpstd::size_t>(n), -1);
                    ASSERT_EQ(v.size(), static_cast<cpstd::size_t>(size + n));
                    int expected = 0;
                    for (int i = 0; i < size + n; ++i) {
                        if (i >= pos && i < pos + n) {
                            EXPECT_EQ(v[static_cast<cpstd::size_t>(i)], -1);
                        } else {
                            EXPECT_EQ(v[static_cast<cpstd::size_t>(i)], expected++);
                        }
                    }
                }
            }
        }
    }
}

TEST(VectorInsert, RangeAndInitializerList) {
    cpstd::vector<int> v = {1, 5};
    const int values[] = {2, 3, 4};
    auto it = v.insert(v.begin() + 1, values, values + 3);
    EXPECT_EQ(*it, 2);
    v.insert(v.end(), {6, 7});
    ASSERT_EQ(v.size(), 7u);
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(v[static_cast<cpstd::size_t>(i)], i + 1);
    }
}

TEST(VectorInsert, EmplaceInMiddle) {
    cpstd::vector<Tracked> v;
    v.emplace_back(1);
    v.emplace_back(3);
    v.emplace(v.begin() + 1, 2);
    ASSERT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0].value, 1);
    EXPECT_EQ(v[1].value, 2);
    EXPECT_EQ(v[2].value, 3);
}

TEST(VectorTypes, ElementsWithoutDefaultConstructor) {
    cpstd::vector<NoDefault> v;
    for (int i = 0; i < 10; ++i) {
        v.emplace_back(i);
    }
    v.insert(v.begin(), NoDefault(-1));
    v.erase(v.begin() + 1);
    cpstd::vector<NoDefault> copy(v);
    ASSERT_EQ(copy.size(), 10u);
    EXPECT_EQ(copy[0].value, -1);
    EXPECT_EQ(copy[9].value, 9);
    v.resize(3, NoDefault(0));
    EXPECT_EQ(v.size(), 3u);
}

TEST(VectorTypes, VectorOfVectors) {
    cpstd::vector<cpstd::vector<int>> grid;
    for (int row = 0; row < 5; ++row) {
        cpstd::vector<int> line;
        for (int column = 0; column <= row; ++column) {
            line.push_back(column);
        }
        grid.push_back(cpstd::move(line));
    }
    grid.erase(grid.begin());
    ASSERT_EQ(grid.size(), 4u);
    EXPECT_EQ(grid[3].size(), 5u);
    EXPECT_EQ(grid[3][4], 4);
}

TEST(VectorComparison, LexicographicOrder) {
    const cpstd::vector<int> a = {1, 2, 3};
    const cpstd::vector<int> b = {1, 3};
    const cpstd::vector<int> c = {1, 2, 3, 0};
    const cpstd::vector<int> d = {2, 0};
    const cpstd::vector<int> e = {3, 1};

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a < c);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(d < e);
    EXPECT_FALSE(e < d);   // first element decides even if a later one is smaller
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(a == cpstd::vector<int>({1, 2, 3}));
    EXPECT_TRUE(a != b);
}

TEST(VectorIterators, ReverseTraversal) {
    cpstd::vector<int> v = {1, 2, 3};
    int expected = 3;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        EXPECT_EQ(*it, expected--);
    }
    EXPECT_EQ(expected, 0);
}

#if !defined(CPSTL_USING_STL)

using cpstl_test::BudgetScope;
using cpstl_test::FailingAllocator;

template <class T>
using FailingVector = cpstd::vector<T, FailingAllocator<T>>;

TEST(VectorAllocationFailure, OperationsLeaveTheVectorUnchanged) {
    BudgetScope scope(1);  // exactly one allocation succeeds
    FailingVector<int> v;
    v.push_back(1);
    ASSERT_EQ(v.size(), 1u);
    const cpstd::size_t capacity = v.capacity();

    v.push_back(2);  // needs a second allocation: no effect
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v.capacity(), capacity);
    EXPECT_EQ(v[0], 1);

    v.reserve(100);
    EXPECT_EQ(v.capacity(), capacity);
    v.resize(100);
    EXPECT_EQ(v.size(), 1u);
    v.insert(v.begin(), 5u, 9);
    EXPECT_EQ(v.size(), 1u);
    v.emplace(v.begin(), 3);
    EXPECT_EQ(v.size(), 1u);
    v.assign(10u, 4);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], 1);
}

TEST(VectorAllocationFailure, CopyYieldsEmptyAndAssignmentKeepsTarget) {
    BudgetScope scope(-1);
    FailingVector<Tracked> source;
    for (int i = 0; i < 4; ++i) {
        source.emplace_back(i);
    }
    FailingVector<Tracked> target;
    target.emplace_back(42);

    cpstl_test::AllocationBudget::Remaining = 0;
    FailingVector<Tracked> copy(source);
    EXPECT_TRUE(copy.empty());

    target = source;  // needs more storage than target has
    ASSERT_EQ(target.size(), 1u);
    EXPECT_EQ(target[0].value, 42);
}

TEST(VectorAllocationFailure, NothingLeaks) {
    Tracked::Reset();
    {
        BudgetScope scope(3);
        FailingVector<Tracked> v;
        for (int i = 0; i < 50; ++i) {
            v.emplace_back(i);  // fails once the budget is spent
        }
        EXPECT_GT(v.size(), 0u);
        EXPECT_LT(v.size(), 50u);
        EXPECT_EQ(Tracked::Live, static_cast<int>(v.size()));
    }
    EXPECT_EQ(Tracked::Live, 0);
    EXPECT_EQ(cpstl_test::AllocationBudget::Outstanding, 0);
}

#if !defined(CPSTL_USING_STD_ALLOCATION)
TEST(AllocatorTest, ReturnsNullOnOverflowAndZero) {
    cpstd::allocator<int> alloc;
    EXPECT_EQ(alloc.allocate(0), nullptr);
    EXPECT_EQ(alloc.allocate(alloc.max_size() + 1), nullptr);
    int* p = alloc.allocate(4);
    ASSERT_NE(p, nullptr);
    alloc.deallocate(p, 4);
    alloc.deallocate(nullptr, 0);
}
#endif

#endif
