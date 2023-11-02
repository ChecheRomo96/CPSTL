#if defined(ARDUINO)
    #include <Aunit.h>
    #include <aunit/contrib/gtest.h>
#endif

#if __has_include(<gtest/gtest.h>)
    #include <gtest/gtest.h>
#endif

#include <CPtype_traits.h>
#include <CPutility.h>
/*

struct A {
    int fn() { return 0; }
    int x;
};

enum MyEnum { Value1, Value2 };

union MyUnion {
    int a;
    float b;
};

int user_defined_function() { return 0; }


TEST(CPSTL_TypeTraitsTest, RemoveConst) {
    using NoConst = cpstd::remove_const<const int>::type;
    EXPECT_TRUE((cpstd::is_same_v<NoConst, int>));
    
    using RegularInt = cpstd::remove_const<int>::type;
    EXPECT_TRUE((cpstd::is_same_v<RegularInt, int>));

    using StdNoConst = cpstd::remove_const<const int>::type;
    EXPECT_TRUE((cpstd::is_same_v<NoConst, StdNoConst>));
}

TEST(CPSTL_TypeTraitsTest, IntegralConstant) {
    using MyConstant = cpstd::integral_constant<int, 42u>;
    EXPECT_EQ(MyConstant::value, 42);
}

TEST(CPSTL_TypeTraitsTest, IsSame) {
    EXPECT_TRUE((cpstd::is_same_v< float, cpstd::remove_const<const float>::type >));
}

TEST(CPSTL_TypeTraitsTest, IsArray) {
    EXPECT_TRUE((cpstd::is_array<int[]>::value));
    EXPECT_TRUE((cpstd::is_array<int[5]>::value));
    EXPECT_FALSE((cpstd::is_array<int>::value));
}

TEST(CPSTL_TypeTraitsTest, IsClass) {
    EXPECT_FALSE((cpstd::is_class<int>::value));
    EXPECT_TRUE((cpstd::is_class<class A>::value));
}

TEST(CPSTL_TypeTraitsTest, IsEnum) {
    EXPECT_TRUE((cpstd::is_enum<MyEnum>::value));
    EXPECT_FALSE((cpstd::is_enum<int>::value));
}

TEST(CPSTL_TypeTraitsTest, IsFloatingPoint) {
    EXPECT_TRUE((cpstd::is_floating_point<float>::value));
    EXPECT_FALSE((cpstd::is_floating_point<int>::value));
    EXPECT_TRUE((cpstd::is_floating_point<double>::value));
}

TEST(CPSTL_TypeTraitsTest, IsFunction) {
    EXPECT_FALSE((cpstd::is_function<int>::value));
    typedef void FunctionType();
    EXPECT_FALSE((cpstd::is_function<FunctionType*>::value));
    EXPECT_FALSE((cpstd::is_function<std::function<int()>>::value));
    EXPECT_TRUE((cpstd::is_function<decltype(user_defined_function)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsIntegral) {
    EXPECT_TRUE((cpstd::is_integral<int>::value));
    EXPECT_TRUE((cpstd::is_integral<long long>::value));
    EXPECT_FALSE((cpstd::is_integral<double>::value));
}

TEST(CPSTL_TypeTraitsTest, IsLValueReference) {
    EXPECT_FALSE((cpstd::is_lvalue_reference<int>::value));
    EXPECT_TRUE((cpstd::is_lvalue_reference<int&>::value));
    EXPECT_FALSE((cpstd::is_lvalue_reference<float>::value));
    EXPECT_TRUE((cpstd::is_lvalue_reference<float&>::value));
    EXPECT_FALSE((cpstd::is_lvalue_reference<double>::value));
    EXPECT_TRUE((cpstd::is_lvalue_reference<double&>::value));
    EXPECT_FALSE((cpstd::is_lvalue_reference<const int>::value));
    EXPECT_TRUE((cpstd::is_lvalue_reference<const int&>::value));
}

TEST(CPSTL_TypeTraitsTest, IsMemberFunctionPointer) {
    int(A::* pt)() = &A::fn;
    EXPECT_FALSE((cpstd::is_member_function_pointer<A*>::value));
    EXPECT_TRUE((cpstd::is_member_function_pointer<void(A::*)()>::value));
    EXPECT_TRUE((cpstd::is_member_function_pointer<decltype(pt)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsMemberObjectPointer) {
    int A::* pt2 = nullptr;
    EXPECT_FALSE((cpstd::is_member_object_pointer<decltype(nullptr)>::value));
    EXPECT_TRUE((cpstd::is_member_object_pointer<int A::*>::value));
    EXPECT_TRUE((cpstd::is_member_object_pointer<decltype(pt2)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsPointer) {
    int* ptr = nullptr;
    EXPECT_FALSE((cpstd::is_pointer<int>::value));
    EXPECT_TRUE((cpstd::is_pointer<int*>::value));
    EXPECT_TRUE((cpstd::is_pointer<decltype(ptr)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsRValueReference) {
    int x = 5;
    EXPECT_TRUE((cpstd::is_rvalue_reference<int&&>::value));
    int&& rvalue_ref = cpstd::move(x);
    EXPECT_TRUE((cpstd::is_rvalue_reference<decltype(rvalue_ref)>::value));
    int& lvalue_ref = x;
    EXPECT_FALSE((cpstd::is_rvalue_reference<decltype(lvalue_ref)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsUnion) {
    EXPECT_FALSE((cpstd::is_union<int>::value));
    EXPECT_FALSE((cpstd::is_union<float>::value));
    EXPECT_TRUE((cpstd::is_union<MyUnion>::value));
}

TEST(CPSTL_TypeTraitsTest, IsVoid) {
    EXPECT_TRUE((cpstd::is_void<void>::value));
    EXPECT_FALSE((cpstd::is_void<int>::value));
    EXPECT_FALSE((cpstd::is_void<decltype(nullptr)>::value));
}

*/