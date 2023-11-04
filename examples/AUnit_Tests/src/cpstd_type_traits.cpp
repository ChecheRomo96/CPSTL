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
        // Approach 1: Directly specifying qualifiers in the integral_constant type
        using ConstMyConstant = cpstd::integral_constant<const int, 42>;
        using VolatileMyConstant = cpstd::integral_constant<volatile int, 42>;
        using ConstVolatileMyConstant = cpstd::integral_constant<const volatile int, 42>;

        ASSERT_TRUE((cpstd::is_same_v<const int, ConstMyConstant::value_type>));
        ASSERT_TRUE((cpstd::is_same_v<volatile int, VolatileMyConstant::value_type>));
        ASSERT_TRUE((cpstd::is_same_v<const volatile int, ConstVolatileMyConstant::value_type>));

        // Approach 2: Applying qualifiers during usage with integral_constant
        using ConstMyConstant2 = cpstd::integral_constant<int, 42>;
        using VolatileMyConstant2 = cpstd::integral_constant<int, 42>;
        using ConstVolatileMyConstant2 = cpstd::integral_constant<int, 42>;

        ASSERT_TRUE((cpstd::is_same_v<const int, const ConstMyConstant2::value_type>));
        ASSERT_TRUE((cpstd::is_same_v<volatile int, volatile VolatileMyConstant2::value_type>));
        ASSERT_TRUE((cpstd::is_same_v<const volatile int, const volatile ConstVolatileMyConstant2::value_type>));
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
    // Test case 1: Basic type identity check
    {
        ASSERT_TRUE((cpstd::is_same_v<int, int>));
    }

    // Test case 2: Comparing different non-const types
    {
        ASSERT_FALSE((cpstd::is_same_v<int, float>));
    }

    // Test case 3: Const type comparison
    {
        ASSERT_TRUE((cpstd::is_same_v<const int, const int>));
        ASSERT_FALSE((cpstd::is_same_v<int, const int>));
    }

    // Test case 4: Volatile type comparison
    {
        ASSERT_TRUE((cpstd::is_same_v<volatile int, volatile int>));
        ASSERT_FALSE((cpstd::is_same_v<int, volatile int>));
    }

    // Test case 5: Const-volatile type comparison
    {
        ASSERT_TRUE((cpstd::is_same_v<const volatile int, const volatile int>));
        ASSERT_FALSE((cpstd::is_same_v<int, const volatile int>));
    }

    // Test case 6: Type comparison with remove_cv
    {
        ASSERT_TRUE((cpstd::is_same_v<int, cpstd::remove_cv<const int>::type>));
        ASSERT_TRUE((cpstd::is_same_v<int, cpstd::remove_cv<volatile int>::type>));
        ASSERT_TRUE((cpstd::is_same_v<int, cpstd::remove_cv<const volatile int>::type>));
        ASSERT_TRUE((cpstd::is_same_v<int, cpstd::remove_cv<int>::type>));
    }

    // Test case 7: Negative scenarios - Non-conforming types
    {
        ASSERT_FALSE((cpstd::is_same_v<int, float>));
        ASSERT_FALSE((cpstd::is_same_v<float, double>));
        ASSERT_FALSE((cpstd::is_same_v<char, short>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 8: Cross-verification - Compare with standard library traits
    {
        ASSERT_TRUE((cpstd::is_same<cpstd::remove_cv<const int>::type, std::remove_cv<const int>::type>::value));
        ASSERT_TRUE((cpstd::is_same<cpstd::remove_cv<int>::type, std::remove_cv<int>::type>::value));
        ASSERT_FALSE((cpstd::is_same<cpstd::remove_cv<int>::type, std::remove_cv<const int>::type>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsArray) {
    // Test case 1: Basic array type identification
    {
        int array[5];
        ASSERT_TRUE((cpstd::is_array_v<decltype(array)>));
    }

    // Test case 2: Non-array types
    {
        int non_array = 10;
        ASSERT_FALSE((cpstd::is_array_v<decltype(non_array)>));

        // Non-array types passed directly
        ASSERT_FALSE((cpstd::is_array_v<int>));
        ASSERT_FALSE((cpstd::is_array_v<float>));
    }

    // Test case 3: Array type with const qualifiers
    {
        const double const_array[10];
        ASSERT_TRUE((cpstd::is_array_v<decltype(const_array)>));
    }

    // Test case 4: Array type with volatile qualifiers
    {
        volatile char volatile_array[3];
        ASSERT_TRUE((cpstd::is_array_v<decltype(volatile_array)>));
    }

    // Test case 5: Array type with const-volatile qualifiers
    {
        const volatile long cv_array[7];
        ASSERT_TRUE((cpstd::is_array_v<decltype(cv_array)>));
    }

    // Test case 6: Pointer types and references
    {
        int* ptr_array = new int[8];
        int& ref_array = *ptr_array;
        ASSERT_FALSE((cpstd::is_array_v<decltype(ptr_array)>));
        ASSERT_FALSE((cpstd::is_array_v<decltype(ref_array)>));
    }

    // Test case 7: Negative scenarios - Non-conforming types
    {
        ASSERT_FALSE((cpstd::is_array_v<int>));
        ASSERT_FALSE((cpstd::is_array_v<float>));
        ASSERT_FALSE((cpstd::is_array_v<const char>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 8: Cross-verification - Compare with standard library traits
    {
        int std_array[5];
        ASSERT_TRUE((cpstd::is_array<decltype(std_array)>::value == std::is_array<decltype(std_array)>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsClass) {
    // Test case 1: Basic class type identification
    {
        class MyClass {};
        ASSERT_TRUE((cpstd::is_class_v<MyClass>));
    }

    // Test case 2: Non-class types
    {
        struct MyStruct {};
        class MyClass {};
        enum MyEnum { A, B, C };
        ASSERT_FALSE((cpstd::is_class_v<int>));
        ASSERT_FALSE((cpstd::is_class_v<MyEnum>));
        ASSERT_FALSE((cpstd::is_class_v<float>));
        ASSERT_TRUE((cpstd::is_class_v<MyStruct>));
    }

    // Test case 3: Pointer types and references
    {
        class MyClass {};
        MyClass* ptr = nullptr;
        ASSERT_FALSE((cpstd::is_class_v<decltype(ptr)>));

        MyClass& ref = *ptr;
        ASSERT_FALSE((cpstd::is_class_v<decltype(ref)>));
    }

    // Test case 4: Inheritance scenarios
    {
        class BaseClass {};
        class DerivedClass : public BaseClass {};
        ASSERT_TRUE((cpstd::is_class_v<BaseClass>));
        ASSERT_TRUE((cpstd::is_class_v<DerivedClass>));
    }

    // Test case 5: Negative scenarios - Non-conforming types
    {
        union MyUnion { int x; float y; };
        ASSERT_FALSE((cpstd::is_class_v<MyUnion>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 6: Cross-verification - Compare with standard library traits
    {
        class StdClass {};
        ASSERT_TRUE((cpstd::is_class<StdClass>::value == std::is_class<StdClass>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsEnum) {
    // Test case 1: Basic enum type identification
    {
        enum MyEnum { A, B, C };
        ASSERT_TRUE((cpstd::is_enum_v<MyEnum>));
    }

    // Test case 2: Non-enum types
    {
        struct MyStruct {};
        class MyClass {};
        ASSERT_FALSE((cpstd::is_enum_v<int>));
        ASSERT_FALSE((cpstd::is_enum_v<MyStruct>));
        ASSERT_FALSE((cpstd::is_enum_v<MyClass>));
        ASSERT_FALSE((cpstd::is_enum_v<float>));
    }

    // Test case 3: Pointer types and references
    {
        enum MyEnum { A, B, C };
        MyEnum* ptr = nullptr;
        ASSERT_FALSE((cpstd::is_enum_v<decltype(ptr)>));

        MyEnum& ref = *ptr;
        ASSERT_FALSE((cpstd::is_enum_v<decltype(ref)>));
    }

    // Test case 4: Negative scenarios - Non-conforming types
    {
        union MyUnion { int x; float y; };
        ASSERT_FALSE((cpstd::is_enum_v<MyUnion>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 5: Cross-verification - Compare with standard library traits
    {
        enum StdEnum { X, Y, Z };
        ASSERT_TRUE((cpstd::is_enum<StdEnum>::value == std::is_enum<StdEnum>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsFloatingPoint) {
    // Test case 1: Basic floating-point type identification
    {
        ASSERT_TRUE((cpstd::is_floating_point_v<float>));
        ASSERT_TRUE((cpstd::is_floating_point_v<double>));
        ASSERT_TRUE((cpstd::is_floating_point_v<long double>));
    }

    // Test case 2: Non-floating-point types
    {
        ASSERT_FALSE((cpstd::is_floating_point_v<int>));
        ASSERT_FALSE((cpstd::is_floating_point_v<unsigned int>));
        ASSERT_FALSE((cpstd::is_floating_point_v<long>));
        ASSERT_FALSE((cpstd::is_floating_point_v<char>));
    }

    // Test case 3: Negative scenarios - Non-conforming types
    {
        union MyUnion { int x; float y; };
        ASSERT_FALSE((cpstd::is_floating_point_v<MyUnion>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 4: Cross-verification - Compare with standard library traits
    {
        ASSERT_TRUE((cpstd::is_floating_point<double>::value == std::is_floating_point<double>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsFunction) { 
    // Test case 1: Basic function type identification
    {
        using FunctionPointer = decltype(&user_defined_function); // Function pointer
        ASSERT_FALSE((cpstd::is_function_v<FunctionPointer>)); // Function pointers are not considered functions
        ASSERT_TRUE((cpstd::is_function_v<decltype(user_defined_function)>)); // Function pointers are not considered functions
    }

    // Test case 2: Non-function types
    {
        struct Functor { // Class with overloaded operator()
            void operator()() const {}
        };

        auto lambda = []() {}; // Lambda function

        ASSERT_FALSE((cpstd::is_function_v<int>));
        ASSERT_FALSE((cpstd::is_function_v<Functor>));
        ASSERT_FALSE((cpstd::is_function_v<decltype(lambda)>));
    }

    // Test case 3: Negative scenarios - Non-conforming types
    {
        union MyUnion { int x; float y; };
        ASSERT_FALSE((cpstd::is_function_v<MyUnion>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 4: Cross-verification - Compare with standard library traits
    {
        ASSERT_TRUE((cpstd::is_function<decltype(user_defined_function)>::value == std::is_function<decltype(user_defined_function)>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsIntegral) {
    // Test case 1: Basic integral type identification
    {
        ASSERT_TRUE((cpstd::is_integral_v<int>));
        ASSERT_TRUE((cpstd::is_integral_v<unsigned int>));
        ASSERT_TRUE((cpstd::is_integral_v<long>));
        ASSERT_TRUE((cpstd::is_integral_v<unsigned long>));
        ASSERT_TRUE((cpstd::is_integral_v<short>));
        ASSERT_TRUE((cpstd::is_integral_v<unsigned short>));
        ASSERT_TRUE((cpstd::is_integral_v<char>));
        ASSERT_TRUE((cpstd::is_integral_v<unsigned char>));
        ASSERT_TRUE((cpstd::is_integral_v<bool>));
    }

    // Test case 2: Non-integral types
    {
        ASSERT_FALSE((cpstd::is_integral_v<float>));
        ASSERT_FALSE((cpstd::is_integral_v<double>));
        ASSERT_FALSE((cpstd::is_integral_v<long double>));
    }

    // Test case 3: Negative scenarios - Non-conforming types
    {
        union MyUnion { int x; float y; };
        ASSERT_FALSE((cpstd::is_integral_v<MyUnion>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 4: Cross-verification - Compare with standard library traits
    {
        ASSERT_TRUE((cpstd::is_integral<unsigned long>::value == std::is_integral<unsigned long>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsLValueReference) {
    // Test case 1: Basic lvalue reference type identification
    {
        int x = 5;
        int& ref = x;
        ASSERT_TRUE((cpstd::is_lvalue_reference_v<decltype(ref)>));
    }

    // Test case 2: Non-lvalue reference types
    {
        ASSERT_FALSE((cpstd::is_lvalue_reference_v<int>));
        ASSERT_FALSE((cpstd::is_lvalue_reference_v<int*>));
    }

    // Test case 3: Negative scenarios - Non-conforming types
    {
        struct MyStruct {};
        ASSERT_FALSE((cpstd::is_lvalue_reference_v<MyStruct>));
        union MyUnion { int x; float y; };
        ASSERT_FALSE((cpstd::is_lvalue_reference_v<MyUnion>));
    }

    #if defined(CPSTL_USING_STL)
    // Test case 4: Cross-verification - Compare with standard library traits
    {
        int x = 5;
        int& ref = x;
        ASSERT_TRUE((cpstd::is_lvalue_reference_v<decltype(ref)> == std::is_lvalue_reference<decltype(ref)>::value));
    }
    #endif
}

TEST(CPSTL_TypeTraitsTest, IsMemberFunctionPointer) {
    // Test case 1: Basic member function pointer identification
    {
        class MyClass {
            void memberFunc() {}
        };
        ASSERT_TRUE((is_member_function_pointer<decltype(&MyClass::memberFunc)>::value));
    }

    // Test case 2: Non-member function pointer types
    {
        class MyClass {};
        ASSERT_FALSE((is_member_function_pointer<MyClass>::value));
        ASSERT_FALSE((is_member_function_pointer<int>::value));
        ASSERT_FALSE((is_member_function_pointer<void>::value));
    }

    // Test case 3: Cross-verification - Compare with standard library traits
    #if defined(CPSTL_USING_STL)
    {
        class StdClass {
            void memberFunc() {}
        };
        ASSERT_TRUE((is_member_function_pointer<decltype(&StdClass::memberFunc)>::value == std::is_member_function_pointer<decltype(&StdClass::memberFunc)>::value));
    }
    #endif
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