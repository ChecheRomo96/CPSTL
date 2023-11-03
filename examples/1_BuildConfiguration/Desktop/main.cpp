#include <CPSTL.h>
#include <iostream>
#include <CPinitializer_list>
#include <functional>

int user_defined_function() {
    return 0;
}

struct A { void fn() {}; };
class B { void fn() {}; };
class ExampleClass {
public:
    int member_var;
    static int static_member_var;
};

union MyUnion {
    int a;
    float b;
};

enum ExampleEnum { C, D };

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
    std::cout << "Is a class a class? " << cpstd::is_class<B>::value << std::endl;
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

    // Test is_arithmetic
    std::cout << "Testing cpstd::is_arithmetic:" << std::endl;

    std::cout << "int: " << cpstd::is_arithmetic<int>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "float: " << cpstd::is_arithmetic<float>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "char: " << cpstd::is_arithmetic<char>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "bool: " << cpstd::is_arithmetic<bool>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "void: " << cpstd::is_arithmetic<void>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleClass: " << cpstd::is_arithmetic<class ExampleClass>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "int*: " << cpstd::is_arithmetic<int*>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleClass*: " << cpstd::is_arithmetic<ExampleClass*>::value << " // Expected: 0 (false)" << std::endl;

    std::cout << std::endl;

    // Test is_compound
    std::cout << "Testing cpstd::is_compound:" << std::endl;

    std::cout << "int: " << cpstd::is_compound<int>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "float: " << cpstd::is_compound<float>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "char: " << cpstd::is_compound<char>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "bool: " << cpstd::is_compound<bool>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "void: " << cpstd::is_compound<void>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleClass: " << cpstd::is_compound<ExampleClass>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "int*: " << cpstd::is_compound<int*>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "ExampleClass*: " << cpstd::is_compound<ExampleClass*>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "ExampleEnum: " << cpstd::is_compound<ExampleEnum>::value << " // Expected: 0 (false)" << std::endl;

    std::cout << std::endl;


    // Test is_fundamental
    std::cout << "Testing cpstd::is_fundamental:" << std::endl;

    std::cout << "int: " << cpstd::is_fundamental<int>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "float: " << cpstd::is_fundamental<float>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "char: " << cpstd::is_fundamental<char>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "bool: " << cpstd::is_fundamental<bool>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "void: " << cpstd::is_fundamental<void>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "ExampleClass: " << cpstd::is_fundamental<class ExampleClass>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "int*: " << cpstd::is_fundamental<int*>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleClass*: " << cpstd::is_fundamental<ExampleClass*>::value << " // Expected: 0 (false)" << std::endl;

    std::cout << std::endl;


    // Test is_member_pointer
    std::cout << "Testing cpstd::is_member_pointer:" << std::endl;

    std::cout << "int ExampleClass::*: " << cpstd::is_member_pointer<int ExampleClass::*>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "int ExampleClass::* (static): " << cpstd::is_member_pointer<decltype(&ExampleClass::static_member_var)>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "int ExampleClass::* (non-static): " << cpstd::is_member_pointer<decltype(&ExampleClass::member_var)>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "int: " << cpstd::is_member_pointer<int>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleClass: " << cpstd::is_member_pointer<ExampleClass>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "void: " << cpstd::is_member_pointer<void>::value << " // Expected: 0 (false)" << std::endl;

    std::cout << std::endl;

   

    // Test is_object
    std::cout << "Testing is_object:" << std::endl;

    int i = 5;
    int* ptr_i = &i;
    int& ref_i = i;
    ExampleClass obj;
    ExampleClass& ref_obj = obj;

    std::cout << "int: " << std::is_object<int>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "int*: " << std::is_object<int*>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "int&: " << std::is_object<int&>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleClass: " << std::is_object<ExampleClass>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "ExampleClass&: " << std::is_object<ExampleClass&>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "ExampleEnum: " << std::is_object<ExampleEnum>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "void: " << std::is_object<void>::value << " // Expected: 0 (false)" << std::endl;

    std::cout << std::endl;

    //Test is_reference
    std::cout << "Testing is_reference:" << std::endl;

    const int& const_ref_i = i;
    int&& rref_i = std::move(i); // rvalue reference
    const int&& const_rref_i = std::move(i); // const rvalue reference

    std::cout << "int: " << std::is_reference<int>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "int&: " << std::is_reference<int&>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "int&&: " << std::is_reference<int&&>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "const int&: " << std::is_reference<const int&>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "const int&&: " << std::is_reference<const int&&>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "ExampleClass&: " << std::is_reference<ExampleClass&>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "ExampleClass: " << std::is_reference<ExampleClass>::value << " // Expected: 0 (false)" << std::endl;

    std::cout << std::endl;


    // Test is_scalar
    std::cout << "Testing is_scalar:" << std::endl;
    std::cout << "int: " << std::is_scalar<int>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "float: " << std::is_scalar<float>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "char: " << std::is_scalar<char>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "bool: " << std::is_scalar<bool>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "void: " << std::is_scalar<void>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "std::nullptr_t: " << std::is_scalar<std::nullptr_t>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "enum: " << std::is_scalar<ExampleEnum>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "class: " << std::is_scalar<B>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "pointer to int: " << std::is_scalar<int*>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "pointer to member: " << std::is_scalar<int B::*>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "pointer to member function: " << std::is_scalar<void (B::*)()>::value << " // Expected: 1 (true)" << std::endl;
    std::cout << "reference to int: " << std::is_scalar<int&>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << "reference to class: " << std::is_scalar<B&>::value << " // Expected: 0 (false)" << std::endl;
    std::cout << std::endl;


    std::cout << "All tests completed successfully!" << std::endl;

    return 0;
}
