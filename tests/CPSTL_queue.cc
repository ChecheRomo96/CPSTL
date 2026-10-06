// cpstd::queue: the std::queue interface in both modes and, in the CPSTL
// implementation, the default cpstd::vector container, pop_front detection
// and allocation failure.

#include <gtest/gtest.h>

#include <CPqueue>

#include "TestSupport.h"

#if defined(CPSTL_QUEUE_ENABLED)

using cpstl_test::NoDefault;
using cpstl_test::Tracked;

TEST(Queue, MemberTypes) {
    using Queue = cpstd::queue<int>;
    EXPECT_TRUE((cpstd::is_same<Queue::value_type, int>::value));
    EXPECT_TRUE((cpstd::is_same<Queue::reference, int&>::value));
    EXPECT_TRUE((cpstd::is_same<Queue::const_reference, const int&>::value));
    EXPECT_TRUE((cpstd::is_same<Queue::size_type, Queue::container_type::size_type>::value));
}

TEST(Queue, PushFrontPopIsFirstInFirstOut) {
    cpstd::queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
    for (int i = 0; i < 100; ++i) {
        q.push(i);
        EXPECT_EQ(q.front(), 0);
        EXPECT_EQ(q.back(), i);
    }
    EXPECT_EQ(q.size(), 100u);
    for (int i = 0; i < 100; ++i) {
        ASSERT_FALSE(q.empty());
        EXPECT_EQ(q.front(), i);
        EXPECT_EQ(q.back(), 99);
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

TEST(Queue, InterleavedPushAndPop) {
    cpstd::queue<int> q;
    int next = 0;
    int expected = 0;
    for (int round = 0; round < 20; ++round) {
        q.push(next++);
        q.push(next++);
        EXPECT_EQ(q.front(), expected);
        q.pop();
        ++expected;
    }
    EXPECT_EQ(q.size(), 20u);
    EXPECT_EQ(q.front(), expected);
    EXPECT_EQ(q.back(), next - 1);
}

TEST(Queue, FrontAndBackAreWritableAndConst) {
    cpstd::queue<int> q;
    q.push(1);
    q.push(2);
    q.front() = 10;
    q.back() = 20;
    const cpstd::queue<int>& view = q;
    EXPECT_EQ(view.front(), 10);
    EXPECT_EQ(view.back(), 20);
    EXPECT_EQ(view.size(), 2u);
    EXPECT_FALSE(view.empty());
}

TEST(Queue, EmplaceConstructsInPlace) {
    cpstd::queue<NoDefault> q;
    q.emplace(3);
    q.emplace(4);
    EXPECT_EQ(q.front().value, 3);
    EXPECT_EQ(q.back().value, 4);
    q.pop();
    EXPECT_EQ(q.front().value, 4);
}

TEST(Queue, PushMovesRvalues) {
    Tracked::Reset();
    {
        cpstd::queue<Tracked> q;
        Tracked value(7);
        q.push(cpstd::move(value));
        EXPECT_EQ(value.value, -1);
        EXPECT_EQ(Tracked::Copies, 0);
        const Tracked copy(8);
        q.push(copy);
        EXPECT_EQ(Tracked::Copies, 1);
        EXPECT_EQ(q.back().value, 8);
    }
    EXPECT_EQ(Tracked::Live, 0);
}

TEST(Queue, ConstructsFromContainer) {
    cpstd::queue<int>::container_type values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    cpstd::queue<int> copied(values);
    EXPECT_EQ(copied.size(), 3u);
    EXPECT_EQ(copied.front(), 1);
    EXPECT_EQ(copied.back(), 3);
    EXPECT_EQ(values.size(), 3u);

    cpstd::queue<int> moved(cpstd::move(values));
    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved.front(), 1);
}

TEST(Queue, CopyMoveAndSwap) {
    cpstd::queue<int> a;
    a.push(1);
    a.push(2);
    cpstd::queue<int> b(a);
    EXPECT_TRUE(a == b);
    b.push(3);

    cpstd::queue<int> c(cpstd::move(b));
    EXPECT_EQ(c.size(), 3u);
    EXPECT_EQ(c.back(), 3);

    a.swap(c);
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(c.size(), 2u);
    swap(a, c);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(c.back(), 3);

    cpstd::queue<int> d;
    d = c;
    EXPECT_TRUE(d == c);
}

TEST(Queue, ComparisonsFollowTheContainer) {
    cpstd::queue<int> a;
    cpstd::queue<int> b;
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
    b.back() = 2;
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a <= b && a >= b);
}

TEST(Queue, ElementsAreDestroyed) {
    Tracked::Reset();
    {
        cpstd::queue<Tracked> q;
        for (int i = 0; i < 10; ++i) {
            q.emplace(i);
        }
        EXPECT_EQ(Tracked::Live, 10);
        q.pop();
        q.pop();
        EXPECT_EQ(Tracked::Live, 8);
        EXPECT_EQ(q.front().value, 2);
    }
    EXPECT_EQ(Tracked::Live, 0);
}

#if !defined(CPSTL_USING_STL)

namespace {
    // Minimal sequence with pop_front, to check that queue prefers it over
    // erase(begin()).
    struct FrontPopping : cpstd::vector<int> {
        static int PopFronts;
        void pop_front() {
            ++PopFronts;
            erase(begin());
        }
    };
    int FrontPopping::PopFronts = 0;
}

TEST(QueueCpstl, DefaultContainerIsVector) {
    EXPECT_TRUE((cpstd::is_same<cpstd::queue<int>::container_type, cpstd::vector<int> >::value));
}

TEST(QueueCpstl, PopOnEmptyHasNoEffect) {
    cpstd::queue<int> q;
    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(QueueCpstl, UsesPopFrontWhenAvailable) {
    FrontPopping::PopFronts = 0;
    cpstd::queue<int, FrontPopping> q;
    q.push(1);
    q.push(2);
    q.pop();
    EXPECT_EQ(FrontPopping::PopFronts, 1);
    EXPECT_EQ(q.front(), 2);
}

TEST(QueueCpstl, PopKeepsCapacitySoReservedQueuesDoNotReallocate) {
    // The adapter's container is protected; a derived class may read it.
    struct Inspectable : cpstd::queue<int> {
        using cpstd::queue<int>::queue;
        cpstd::size_t Capacity() const { return c.capacity(); }
        const int* Data() const { return c.data(); }
    };
    cpstd::vector<int> storage;
    storage.reserve(8);
    Inspectable q(cpstd::move(storage));
    const int* data = nullptr;
    for (int round = 0; round < 100; ++round) {
        while (q.size() < 8) {
            q.push(round);
        }
        if (data == nullptr) {
            data = q.Data();
        }
        EXPECT_EQ(q.Data(), data);
        q.pop();
        q.pop();
    }
    EXPECT_EQ(q.size(), 6u);
    EXPECT_EQ(q.Capacity(), 8u);
}

TEST(QueueCpstl, AllocationFailureLeavesQueueUnchanged) {
    using Container = cpstd::vector<int, cpstl_test::FailingAllocator<int> >;
    {
        cpstl_test::BudgetScope budget(1);
        cpstd::queue<int, Container> q;
        q.push(1);  // first allocation succeeds
        EXPECT_EQ(q.size(), 1u);
        q.push(2);  // growth fails
        q.emplace(3);
        EXPECT_EQ(q.size(), 1u);
        EXPECT_EQ(q.front(), 1);
        EXPECT_EQ(q.back(), 1);
    }
    EXPECT_EQ(cpstl_test::AllocationBudget::Outstanding, 0);
}

#endif

#endif
