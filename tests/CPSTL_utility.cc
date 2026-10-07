#include <gtest/gtest.h>

#include <CPutility>
#include <CPexception>
#include <CPinitializer_list>

#include <string.h>

#include "TestSupport.h"

using cpstl_test::Tracked;

namespace {
    int Kind(int&) { return 1; }
    int Kind(int&&) { return 2; }

    template <class T>
    int Forwarded(T&& value) { return Kind(cpstd::forward<T>(value)); }
}

TEST(UtilityTest, MoveAndForward) {
    int x = 0;
    EXPECT_EQ(Forwarded(x), 1);
    EXPECT_EQ(Forwarded(0), 2);
    EXPECT_EQ(Kind(cpstd::move(x)), 2);

    Tracked a(4);
    Tracked b(cpstd::move(a));
    EXPECT_EQ(b.value, 4);
    EXPECT_EQ(a.value, -1);
}

TEST(UtilityTest, SwapValuesAndArrays) {
    int a = 1;
    int b = 2;
    cpstd::swap(a, b);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);

    int left[3] = {1, 2, 3};
    int right[3] = {4, 5, 6};
    cpstd::swap(left, right);
    EXPECT_EQ(left[0], 4);
    EXPECT_EQ(right[2], 3);
}

TEST(UtilityTest, Exchange) {
    int value = 3;
    EXPECT_EQ(cpstd::exchange(value, 8), 3);
    EXPECT_EQ(value, 8);
}

TEST(UtilityTest, InitializerList) {
    cpstd::initializer_list<int> list = {1, 2, 3};
    EXPECT_EQ(list.size(), 3u);
    int sum = 0;
    for (int v : list) {
        sum += v;
    }
    EXPECT_EQ(sum, 6);
}

TEST(ExceptionTest, HierarchyAndMessages) {
    const cpstd::out_of_range range("index 9");
    const cpstd::logic_error& logic = range;
    const cpstd::exception& base = logic;
    EXPECT_EQ(strcmp(base.what(), "index 9"), 0);

    const cpstd::length_error length("too long");
    EXPECT_EQ(strcmp(length.what(), "too long"), 0);

    const cpstd::bad_alloc alloc;
    EXPECT_NE(alloc.what(), nullptr);
}
