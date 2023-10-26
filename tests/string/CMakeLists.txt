add_executable( CPSTL_String_Constructor ConstructorTests.cc ) 
target_link_libraries( CPSTL_String_Constructor PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_String_Constructor)

add_executable( CPSTL_String_Capacity CapacityTests.cc ) 
target_link_libraries( CPSTL_String_Capacity PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_String_Capacity)

add_executable( CPSTL_String_ElementAccess ElementAccessTests.cc ) 
target_link_libraries( CPSTL_String_ElementAccess PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_String_ElementAccess)

add_executable( CPSTL_String_Modifiers ModifiersTests.cc ) 
target_link_libraries( CPSTL_String_Modifiers PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_String_Modifiers)

add_executable( CPSTL_String_StringOperations StringOperationsTests.cc ) 
target_link_libraries( CPSTL_String_StringOperations PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_String_StringOperations)

add_executable( CPSTL_String_NonMemberFunctions NonMemberFunctionsTests.cc ) 
target_link_libraries( CPSTL_String_NonMemberFunctions PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_String_NonMemberFunctions)