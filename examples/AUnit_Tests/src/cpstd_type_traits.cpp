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
    {
        using TypeWithConstInt = const int;
        using TypeWithoutConstInt = cpstd::remove_const<TypeWithConstInt>::type;
        ASSERT_TRUE((cpstd::is_same<TypeWithoutConstInt, int>::value));
    }

    // Test case 2: Type is const volatile float
    {
        using TypeWithConstVolatileFloat = const volatile float;
        using TypeWithoutConstVolatileFloat = cpstd::remove_const<TypeWithConstVolatileFloat>::type;
        ASSERT_TRUE((cpstd::is_same<TypeWithoutConstVolatileFloat, volatile float>::value));
    }

    // Test case 3: Type is const volatile char
    {
        using TypeWithConstVolatileChar = const volatile char;
        using TypeWithoutConstVolatileChar = cpstd::remove_const<TypeWithConstVolatileChar>::type;
        ASSERT_TRUE((cpstd::is_same<TypeWithoutConstVolatileChar, volatile char>::value));
    }

    // Test case 4: Type is int
    {
        using RegularInt = int;
        using TypeWithoutConstRegularInt = cpstd::remove_const<RegularInt>::type;
        ASSERT_TRUE((cpstd::is_same<TypeWithoutConstRegularInt, int>::value));
    }

    // Test case 5: Standard usage with const int
    {
        using TypeWithConstIntStandard = const int;
        using TypeWithoutConstIntStandard = cpstd::remove_const<TypeWithConstIntStandard>::type;
        ASSERT_TRUE((cpstd::is_same<TypeWithoutConstIntStandard, int>::value));
    }

    // Test case 6: Negative case - non-const int
    {
        using NonConstInt = int;
        using TypeWithoutConstNonConstInt = cpstd::remove_const<NonConstInt>::type;
        ASSERT_TRUE((cpstd::is_same<TypeWithoutConstNonConstInt, int>::value));
    }
}

TEST(CPSTL_TypeTraitsTest, IntegralConstant) {
    // Test case 1: Basic integral constant with value 42
    {
        using MyConstant = cpstd::integral_constant<int, 42>;
        ASSERT_EQ(MyConstant::value, 42);
    }

    #ifdef CPSTL_USING_STL
    // Test case 2: Integral constant at language limits
    {
        using MinInt = cpstd::integral_constant<int, std::numeric_limits<int>::min()>;
        ASSERT_EQ(MinInt::value, std::numeric_limits<int>::min());
    }
    #endif

    // Test case 3: Qualifier variations - const, volatile, and const-volatile combinations
    {
        using ConstMyConstant = const cpstd::integral_constant<int, 42>;
        using VolatileMyConstant = volatile cpstd::integral_constant<int, 42>;
        using ConstVolatileMyConstant = const volatile cpstd::integral_constant<int, 42>;

        ASSERT_TRUE((cpstd::is_same_v<const int, ConstMyConstant::value_type>));
        ASSERT_TRUE((cpstd::is_same_v<volatile int, VolatileMyConstant::value_type>));
        ASSERT_TRUE((cpstd::is_same_v<const volatile int, ConstVolatileMyConstant::value_type>));
    }

    // Test case 4: Negative scenarios - Non-conforming types
    {
        using MyOtherType = cpstd::integral_constant<int, 100>;
        ASSERT_FALSE((cpstd::is_same<MyOtherType, cpstd::integral_constant<int, 42>>::value));
    }
    
    #if defined(CPSTL_USING_STL)
    // Test case 5: Cross-verification - Compare with standard library traits
    {
        ASSERT_TRUE((cpstd::is_same<cpstd::integral_constant<int, 42>, std::integral_constant<int, 42>>::value));
    }
    #endif
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