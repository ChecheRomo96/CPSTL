// cpstd::stack: the std::stack interface in both modes and, in the CPSTL
// implementation, the default cpstd::vector container and allocation failure.

#include <gtest/gtest.h>

#include <CPstack>

#include "TestSupport.h"

#if defined(CPSTL_STACK_ENABLED)

using cpstl_test::NoDefault;
using cpstl_test::Tracked;

TEST(Stack, MemberTypes) {
    using Stack = cpstd::stack<int>;
    EXPECT_TRUE((cpstd::is_same<Stack::value_type, int>::value));
    EXPECT_TRUE((cpstd::is_same<Stack::reference, int&>::value));
    EXPECT_TRUE((cpstd::is_same<Stack::const_reference, const int&>::value));
    EXPECT_TRUE((cpstd::is_same<Stack::size_type, Stack::container_type::size_type>::value));
}

TEST(Stack, PushTopPopIsLastInFirstOut) {
    cpstd::stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
    for (int i = 0; i < 100; ++i) {
        s.push(i);
        EXPECT_EQ(s.top(), i);
    }
    EXPECT_EQ(s.size(), 100u);
    for (int i = 99; i >= 0; --i) {
        ASSERT_FALSE(s.empty());
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

TEST(Stack, TopIsWritableAndConst) {
    cpstd::stack<int> s;
    s.push(1);
    s.top() = 5;
    const cpstd::stack<int>& view = s;
    EXPECT_EQ(view.top(), 5);
    EXPECT_EQ(view.size(), 1u);
    EXPECT_FALSE(view.empty());
}

TEST(Stack, EmplaceConstructsInPlace) {
    cpstd::stack<NoDefault> s;
    s.emplace(3);
    s.emplace(4);
    EXPECT_EQ(s.top().value, 4);
    s.pop();
    EXPECT_EQ(s.top().value, 3);
}

TEST(Stack, PushMovesRvalues) {
    Tracked::Reset();
    {
        cpstd::stack<Tracked> s;
        Tracked value(7);
        s.push(cpstd::move(value));
        EXPECT_EQ(value.value, -1);
        EXPECT_EQ(Tracked::Copies, 0);
        s.push(s.top());
        EXPECT_EQ(Tracked::Copies, 1);
        EXPECT_EQ(s.top().value, 7);
    }
    EXPECT_EQ(Tracked::Live, 0);
}

TEST(Stack, ConstructsFromContainer) {
    cpstd::stack<int>::container_type values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    cpstd::stack<int> copied(values);
    EXPECT_EQ(copied.size(), 3u);
    EXPECT_EQ(copied.top(), 3);
    EXPECT_EQ(values.size(), 3u);

    cpstd::stack<int> moved(cpstd::move(values));
    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved.top(), 3);
}

TEST(Stack, CopyMoveAndSwap) {
    cpstd::stack<int> a;
    a.push(1);
    a.push(2);
    cpstd::stack<int> b(a);
    EXPECT_TRUE(a == b);
    b.push(3);

    cpstd::stack<int> c(cpstd::move(b));
    EXPECT_EQ(c.size(), 3u);
    EXPECT_EQ(c.top(), 3);

    a.swap(c);
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(c.size(), 2u);
    swap(a, c);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(c.top(), 3);

    cpstd::stack<int> d;
    d = c;
    EXPECT_TRUE(d == c);
}

TEST(Stack, ComparisonsFollowTheContainer) {
    cpstd::stack<int> a;
    cpstd::stack<int> b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(a == b);
    b.pop();
    b.push(2);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a <= b && a >= b);
}

TEST(Stack, ElementsAreDestroyed) {
    Tracked::Reset();
    {
        cpstd::stack<Tracked> s;
        for (int i = 0; i < 10; ++i) {
            s.emplace(i);
        }
        EXPECT_EQ(Tracked::Live, 10);
        s.pop();
        s.pop();
        EXPECT_EQ(Tracked::Live, 8);
    }
    EXPECT_EQ(Tracked::Live, 0);
}

TEST(Stack, ReservedVectorContainerWorksInBothModes) {
    cpstd::vector<int> storage;
    storage.reserve(16);
    cpstd::stack<int, cpstd::vector<int> > s(cpstd::move(storage));
    for (int i = 0; i < 16; ++i) {
        s.push(i);
    }
    EXPECT_EQ(s.size(), 16u);
    EXPECT_EQ(s.top(), 15);
    s.pop();
    EXPECT_EQ(s.top(), 14);
}

#if !defined(CPSTL_USING_STL)

TEST(StackCpstl, DefaultContainerIsVector) {
    EXPECT_TRUE((cpstd::is_same<cpstd::stack<int>::container_type, cpstd::vector<int> >::value));
}

TEST(StackCpstl, PopOnEmptyHasNoEffect) {
    cpstd::stack<int> s;
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(StackCpstl, AllocationFailureLeavesStackUnchanged) {
    using Container = cpstd::vector<int, cpstl_test::FailingAllocator<int> >;
    {
        cpstl_test::BudgetScope budget(1);
        cpstd::stack<int, Container> s;
        s.push(1);  // first allocation succeeds
        EXPECT_EQ(s.size(), 1u);
        s.push(2);  // growth fails
        s.emplace(3);
        EXPECT_EQ(s.size(), 1u);
        EXPECT_EQ(s.top(), 1);
    }
    EXPECT_EQ(cpstl_test::AllocationBudget::Outstanding, 0);
}

#endif

#endif
