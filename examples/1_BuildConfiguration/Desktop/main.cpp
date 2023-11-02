#include <CPSTL.h>
#include <iostream>
#include <CPinitializer_list>
#include <functional>

int user_defined_function() {
    return 0;
}

struct A { void fn() {}; };

union MyUnion {
    int a;
    float b;
};

int main(){
    std::cout<<"This project uses CPSTL version: "<<CPSTL_VERSION << std::endl << std::endl;
    

#ifdef CPSTL_VECTOR_ENABLED
    std::cout << "  cpstd::vector enabled" << std::endl;

    std::cout << std::endl;
#endif

#ifdef CPSTL_STRING_ENABLED
    std::cout << "  cpstd::string enabled" << std::endl;

    std::cout << std::endl;
#endif

    using NoConst = cpstd::remove_const<const int>::type;
    static_assert(cpstd::is_same_v<NoConst, int>, "remove_const failed for const int");
    std::cout << "Testing remove_const<const int> -> int - Passed" << std::endl;

    using RegularInt = cpstd::remove_const<int>::type;
    static_assert(cpstd::is_same_v<RegularInt, int>, "remove_const failed for int");
    std::cout << "Testing remove_const<int> -> int - Passed" << std::endl;

    using StdNoConst = std::remove_const<const int>::type;
    static_assert(cpstd::is_same_v<NoConst, StdNoConst>, "Mismatch between custom and std::remove_const");
    std::cout << "Testing omparison between custom and std::remove_const - Passed" << std::endl;

    std::cout << "Tests related to remove_const passed successfully!" << std::endl;
    std::cout << std::endl;

    using MyConstant = cpstd::integral_constant<int, 42u>;
    static_assert(MyConstant::value == 42, "Constant value mismatch");
    std::cout << "Testing integral_constant<int, 42> - Passed" << std::endl;

    std::cout << "Testing std::is_same_v<float, cpstd::remove_const<const float>::type> -> "
        << std::is_same_v<float, cpstd::remove_const<const float>::type> << std::endl;
    std::cout << std::endl;
   
    // Test is_array
    std::cout << "Testing is_array:" << std::endl;
    std::cout << "Is int[] an array? " << cpstd::is_array<int[]>::value << std::endl;
    std::cout << "Is int[5] an array? " << cpstd::is_array<int[5]>::value << std::endl;
    std::cout << "Is int not an array? " << cpstd::is_array<int>::value << std::endl;
    std::cout << std::endl;

    // Test is_class
    std::cout << "\nTesting is_class:" << std::endl;
    std::cout << "Is int a class? " << cpstd::is_class<int>::value << std::endl;
    std::cout << "Is a class a class? " << cpstd::is_class<class A>::value << std::endl;
    std::cout << std::endl;

    // Test is_enum
    enum MyEnum { Value1, Value2 };
    std::cout << "\nTesting is_enum:" << std::endl;
    std::cout << "Is MyEnum an enum? " << cpstd::is_enum<MyEnum>::value << std::endl;
    std::cout << "Is int an enum? " << cpstd::is_enum<int>::value << std::endl;
    std::cout << std::endl;

    // Test is_floating_point
    std::cout << "\nTesting is_floating_point:" << std::endl;
    std::cout << "Is float a floating point? " << cpstd::is_floating_point<float>::value << std::endl;
    std::cout << "Is int a floating point? " << cpstd::is_floating_point<int>::value << std::endl;
    std::cout << "Is double a floating point? " << cpstd::is_floating_point<double>::value << std::endl;
    std::cout << std::endl;

    // Test is_function
    std::cout << "\nTesting is_function:" << std::endl;
    std::cout << "Is int a function? " << cpstd::is_function<int>::value << std::endl;
    typedef void FunctionType();
    std::cout << "Is a function pointer a function? " << cpstd::is_function<FunctionType*>::value << std::endl;
    std::cout << "Is std::function a function? " << cpstd::is_function<std::function<int()>>::value << std::endl;
    std::cout << "Is decltype(user_defined_function) a function? " << cpstd::is_function<decltype(user_defined_function)>::value << std::endl;
    std::cout << std::endl;


    // Test is_integral
    std::cout << "\nTesting is_integral:" << std::endl;
    std::cout << "Is int an integral? " << cpstd::is_integral<int>::value << std::endl;
    std::cout << "Is long long an integral? " << cpstd::is_integral<long long>::value << std::endl;
    std::cout << "Is double an integral? " << cpstd::is_integral<double>::value << std::endl;
    std::cout << std::endl;

    // Test is_lvalue_reference
    std::cout << "Testing is_lvalue_reference:" << std::endl;
    std::cout << "Is int an lvalue reference type? " << cpstd::is_lvalue_reference<int>::value << std::endl;
    std::cout << "Is int& an lvalue reference type? " << cpstd::is_lvalue_reference<int&>::value << std::endl;
    std::cout << "Is float an lvalue reference type? " << cpstd::is_lvalue_reference<float>::value << std::endl;
    std::cout << "Is float& an lvalue reference type? " << cpstd::is_lvalue_reference<float&>::value << std::endl;
    std::cout << "Is double an lvalue reference type? " << cpstd::is_lvalue_reference<double>::value << std::endl;
    std::cout << "Is double& an lvalue reference type? " << cpstd::is_lvalue_reference<double&>::value << std::endl;
    std::cout << "Is const int an lvalue reference type? " << cpstd::is_lvalue_reference<const int>::value << std::endl;
    std::cout << "Is const int& an lvalue reference type? " << cpstd::is_lvalue_reference<const int&>::value << std::endl;
    std::cout << std::endl;

    // Test is_member_function_pointer
    void(A::* pt)() = &A::fn;
    std::cout << "Testing is_member_function_pointer:" << std::endl;
    std::cout << "A*: " << cpstd::is_member_function_pointer<A*>::value << std::endl;
    std::cout << "void(A::*)(): " << cpstd::is_member_function_pointer<void(A::*)()>::value << std::endl;
    std::cout << "decltype(pt): " << cpstd::is_member_function_pointer<decltype(pt)>::value << std::endl;
    std::cout << std::endl;

    // Test is_member_object_pointer
    int A::* pt2 = nullptr; // Null pointer for demonstration
    std::cout << std::boolalpha;
    std::cout << "is_member_object_pointer:" << std::endl;
    std::cout << "A*: " << std::is_member_object_pointer<decltype(nullptr)>::value << std::endl;
    std::cout << "int A::*: " << std::is_member_object_pointer<int A::*>::value << std::endl;
    std::cout << "decltype(pt): " << std::is_member_object_pointer<decltype(pt2)>::value << std::endl;
    std::cout << std::endl;

    // Test is_pointer
    int* ptr = nullptr;
    std::cout << "Testing is_pointer:" << std::endl;
    std::cout << "int: " << cpstd::is_pointer<int>::value << std::endl;
    std::cout << "int*: " << cpstd::is_pointer<int*>::value << std::endl;
    std::cout << "decltype(ptr): " << cpstd::is_pointer<decltype(ptr)>::value << std::endl;
    std::cout << std::endl;

    // Test is_rvalue_reference
    int x = 5;
    std::cout << "Testing is_rvalue_reference:" << std::endl;
    std::cout << "int&&: " << cpstd::is_rvalue_reference<int&&>::value << std::endl;
    
    int&& rvalue_ref = std::move(x);
    std::cout << "decltype(rvalue_ref): " << cpstd::is_rvalue_reference<decltype(rvalue_ref)>::value << std::endl;
    std::cout << "int: " << cpstd::is_rvalue_reference<int>::value << std::endl;
    
    int& lvalue_ref = x;
    std::cout << "int&: " << cpstd::is_rvalue_reference<decltype(lvalue_ref)>::value << std::endl;
    std::cout << std::endl;


    // Test is_union
    std::cout << "Testing is_union:" << std::endl;
    std::cout << "int: " << cpstd::is_union<int>::value << std::endl; // false
    std::cout << "float: " << cpstd::is_union<float>::value << std::endl; // false
    std::cout << "MyUnion: " << cpstd::is_union<MyUnion>::value << std::endl; // true
    std::cout << std::endl;

    // Test is_void
    std::cout << "Testing is_void:" << std::endl;
    std::cout << "void: " << cpstd::is_void<void>::value << std::endl;
    std::cout << "int: " << cpstd::is_void<int>::value << std::endl;
    std::cout << "decltype(nullptr): " << cpstd::is_void<decltype(nullptr)>::value << std::endl;
    std::cout << std::endl;



    std::cout << "All tests completed successfully!" << std::endl;

    return 0;
}
