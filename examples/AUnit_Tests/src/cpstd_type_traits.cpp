#if defined(ARDUINO)
    #include <Aunit.h>
    #include <aunit/contrib/gtest.h>
#endif

#if __has_include(<gtest/gtest.h>)
    #include <gtest/gtest.h>
#endif

#include <CPtype_traits.h>
#include <CPutility.h>

namespace {
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
}

TEST(CPSTL_TypeTraitsTest, RemoveConst) {
    // Test case 1: Type is const int
    using ConstInt = const int;
    using NoConst_Int = cpstd::remove_const<ConstInt>::type;
    ASSERT_TRUE((cpstd::is_same_v<NoConst_Int, int>));

    // Test case 2: Type is const float
    using ConstFloat = const float;
    using NoConst_Float = cpstd::remove_const<ConstFloat>::type;
    ASSERT_TRUE((cpstd::is_same_v<NoConst_Float, float>));

    // Test case 3: Type is const volatile char
    using ConstVolatileChar = const volatile char;
    using NoConstVolatile_Char = cpstd::remove_const<ConstVolatileChar>::type;
    ASSERT_TRUE((cpstd::is_same_v<NoConstVolatile_Char, volatile char>));

    // Test case 4: Type is int
    using RegularInt = int;
    using NoConst_RegularInt = cpstd::remove_const<RegularInt>::type;
    ASSERT_TRUE((cpstd::is_same_v<NoConst_RegularInt, int>));

    // Test case 5: Standard usage with const int
    using StdNoConst = cpstd::remove_const<const int>::type;
    ASSERT_TRUE((cpstd::is_same_v<NoConst_Int, StdNoConst));

    // Test case 6: Negative case - non-const int
    using NonConstInt = int;
    using NoConst_NonConstInt = cpstd::remove_const<NonConstInt>::type;
    ASSERT_TRUE((std::is_same<NoConst_NonConstInt, int>::value));
}

TEST(CPSTL_TypeTraitsTest, IntegralConstant) {
    using MyConstant = cpstd::integral_constant<int, 42u>;
    ASSERT_EQ(MyConstant::value, 42);
}

TEST(CPSTL_TypeTraitsTest, IsSame) {
    ASSERT_TRUE((cpstd::is_same_v< float, cpstd::remove_const<const float>::type >));
}

TEST(CPSTL_TypeTraitsTest, IsArray) {
    ASSERT_TRUE((cpstd::is_array<int[]>::value));
    ASSERT_TRUE((cpstd::is_array<int[5]>::value));
    ASSERT_FALSE((cpstd::is_array<int>::value));
}

TEST(CPSTL_TypeTraitsTest, IsClass) {
    ASSERT_FALSE((cpstd::is_class<int>::value));
    ASSERT_TRUE((cpstd::is_class<class A>::value));
}

TEST(CPSTL_TypeTraitsTest, IsEnum) {
    ASSERT_TRUE((cpstd::is_enum<MyEnum>::value));
    ASSERT_FALSE((cpstd::is_enum<int>::value));
}

TEST(CPSTL_TypeTraitsTest, IsFloatingPoint) {
    ASSERT_TRUE((cpstd::is_floating_point<float>::value));
    ASSERT_FALSE((cpstd::is_floating_point<int>::value));
    ASSERT_TRUE((cpstd::is_floating_point<double>::value));
}

TEST(CPSTL_TypeTraitsTest, IsFunction) {
    ASSERT_FALSE((cpstd::is_function<int>::value));
    typedef void FunctionType();
    ASSERT_FALSE((cpstd::is_function<FunctionType*>::value));
    //ASSERT_FALSE((cpstd::is_function<std::function<int()>>::value));
    ASSERT_TRUE((cpstd::is_function<decltype(user_defined_function)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsIntegral) {
    ASSERT_TRUE((cpstd::is_integral<int>::value));
    ASSERT_TRUE((cpstd::is_integral<long long>::value));
    ASSERT_FALSE((cpstd::is_integral<double>::value));
}

TEST(CPSTL_TypeTraitsTest, IsLValueReference) {
    ASSERT_FALSE((cpstd::is_lvalue_reference<int>::value));
    ASSERT_TRUE((cpstd::is_lvalue_reference<int&>::value));
    ASSERT_FALSE((cpstd::is_lvalue_reference<float>::value));
    ASSERT_TRUE((cpstd::is_lvalue_reference<float&>::value));
    ASSERT_FALSE((cpstd::is_lvalue_reference<double>::value));
    ASSERT_TRUE((cpstd::is_lvalue_reference<double&>::value));
    ASSERT_FALSE((cpstd::is_lvalue_reference<const int>::value));
    ASSERT_TRUE((cpstd::is_lvalue_reference<const int&>::value));
}

TEST(CPSTL_TypeTraitsTest, IsMemberFunctionPointer) {
    int(A::* pt)() = &A::fn;
    ASSERT_FALSE((cpstd::is_member_function_pointer<A*>::value));
    ASSERT_TRUE((cpstd::is_member_function_pointer<void(A::*)()>::value));
    ASSERT_TRUE((cpstd::is_member_function_pointer<decltype(pt)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsMemberObjectPointer) {
    int A::* pt2 = nullptr;
    ASSERT_FALSE((cpstd::is_member_object_pointer<decltype(nullptr)>::value));
    ASSERT_TRUE((cpstd::is_member_object_pointer<int A::*>::value));
    ASSERT_TRUE((cpstd::is_member_object_pointer<decltype(pt2)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsPointer) {
    int* ptr = nullptr;
    ASSERT_FALSE((cpstd::is_pointer<int>::value));
    ASSERT_TRUE((cpstd::is_pointer<int*>::value));
    ASSERT_TRUE((cpstd::is_pointer<decltype(ptr)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsRValueReference) {
    int x = 5;
    ASSERT_TRUE((cpstd::is_rvalue_reference<int&&>::value));
    int&& rvalue_ref = cpstd::move(x);
    ASSERT_TRUE((cpstd::is_rvalue_reference<decltype(rvalue_ref)>::value));
    int& lvalue_ref = x;
    ASSERT_FALSE((cpstd::is_rvalue_reference<decltype(lvalue_ref)>::value));
}

TEST(CPSTL_TypeTraitsTest, IsUnion) {
    ASSERT_FALSE((cpstd::is_union<int>::value));
    ASSERT_FALSE((cpstd::is_union<float>::value));
    ASSERT_TRUE((cpstd::is_union<MyUnion>::value));
}

TEST(CPSTL_TypeTraitsTest, IsVoid) {
    ASSERT_TRUE((cpstd::is_void<void>::value));
    ASSERT_FALSE((cpstd::is_void<int>::value));
    ASSERT_FALSE((cpstd::is_void<decltype(nullptr)>::value));
}