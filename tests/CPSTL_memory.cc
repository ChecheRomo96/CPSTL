#include <gtest/gtest.h>

#include <CPmemory.h>
#include <CPfunctional.h>

#include "TestSupport.h"

using cpstl_test::Tracked;

namespace {
    struct Base {
        virtual ~Base() {}
        virtual int Id() const { return 1; }
    };
    struct Derived : Base {
        int Id() const override { return 2; }
    };
}

TEST(UniquePtrTest, OwnsAndReleases) {
    Tracked::Reset();
    {
        cpstd::unique_ptr<Tracked> p = cpstd::make_unique<Tracked>(5);
        ASSERT_TRUE(static_cast<bool>(p));
        EXPECT_EQ(p->value, 5);
        EXPECT_EQ((*p).value, 5);
        EXPECT_EQ(Tracked::Live, 1);

        cpstd::unique_ptr<Tracked> q(cpstd::move(p));
        EXPECT_FALSE(static_cast<bool>(p));
        EXPECT_EQ(Tracked::Live, 1);

        q.reset(new Tracked(6));
        EXPECT_EQ(Tracked::Live, 1);
        EXPECT_EQ(q->value, 6);

        Tracked* raw = q.release();
        EXPECT_FALSE(static_cast<bool>(q));
        delete raw;
        EXPECT_EQ(Tracked::Live, 0);

        q = cpstd::make_unique<Tracked>(7);
    }
    EXPECT_EQ(Tracked::Live, 0);
}

TEST(UniquePtrTest, ConvertsDerivedToBase) {
    cpstd::unique_ptr<Derived> derived(new Derived());
    cpstd::unique_ptr<Base> base(cpstd::move(derived));
    ASSERT_TRUE(static_cast<bool>(base));
    EXPECT_EQ(base->Id(), 2);
}

TEST(UninitializedTest, CopyAndMoveConstructInRawStorage) {
    Tracked::Reset();
    alignas(Tracked) unsigned char raw[3 * sizeof(Tracked)];
    Tracked* slots = reinterpret_cast<Tracked*>(raw);
    Tracked source[3] = {Tracked(1), Tracked(2), Tracked(3)};

    EXPECT_EQ(cpstd::uninitialized_copy(source, source + 3, slots), slots + 3);
    EXPECT_EQ(slots[2].value, 3);
    EXPECT_EQ(Tracked::Live, 6);
    for (int i = 0; i < 3; ++i) {
        slots[i].~Tracked();
    }

    cpstd::uninitialized_move(source, source + 3, slots);
    EXPECT_EQ(slots[0].value, 1);
    EXPECT_EQ(source[0].value, -1);  // moved from
    for (int i = 0; i < 3; ++i) {
        slots[i].~Tracked();
    }
    EXPECT_EQ(Tracked::Live, 3);
}

TEST(FunctionTest, StoresAndCopiesCallables) {
    cpstd::function<int(int)> empty;
    EXPECT_FALSE(static_cast<bool>(empty));

    int offset = 10;
    auto lambda = [offset](int x) { return x + offset; };
    cpstd::function<int(int)> f(lambda);  // lvalue: stored by copy
    ASSERT_TRUE(static_cast<bool>(f));
    EXPECT_EQ(f(5), 15);

    cpstd::function<int(int)> g = f;
    offset = 0;
    EXPECT_EQ(g(1), 11);

    cpstd::function<int(int)> h = [](int x) { return x * 2; };
    h = cpstd::move(g);
    EXPECT_EQ(h(2), 12);

    struct Counter {
        int calls = 0;
        int operator()() { return ++calls; }
    };
    cpstd::function<int()> counter = Counter();
    EXPECT_EQ(counter(), 1);
    EXPECT_EQ(counter(), 2);  // state lives in the stored copy

    h = nullptr;
    EXPECT_FALSE(static_cast<bool>(h));
}

namespace {
    int Twice(int x) { return 2 * x; }
}

TEST(FunctionTest, AcceptsFunctionPointersAndMoveOnlyArguments) {
    cpstd::function<int(int)> f(&Twice);
    EXPECT_EQ(f(21), 42);

    cpstd::function<int(int)> by_name(Twice);
    EXPECT_EQ(by_name(6), 12);

    cpstd::function<int(cpstd::unique_ptr<int>)> take =
        [](cpstd::unique_ptr<int> p) { return *p; };
    EXPECT_EQ(take(cpstd::make_unique<int>(9)), 9);
}
