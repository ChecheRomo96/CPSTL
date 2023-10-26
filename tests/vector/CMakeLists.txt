add_executable( CPSTL_Vector_Constructor ConstructorTests.cc ) 
target_link_libraries( CPSTL_Vector_Constructor PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_Constructor)

add_executable( CPSTL_Vector_Assignment AssignmentTests.cc ) 
target_link_libraries( CPSTL_Vector_Assignment PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_Assignment)

add_executable( CPSTL_Vector_Capacity CapacityTests.cc ) 
target_link_libraries( CPSTL_Vector_Capacity PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_Capacity)

add_executable( CPSTL_Vector_ElementAccess ElementAccessTests.cc ) 
target_link_libraries( CPSTL_Vector_ElementAccess PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_ElementAccess)

add_executable( CPSTL_Vector_Modifiers ModifiersTests.cc ) 
target_link_libraries( CPSTL_Vector_Modifiers PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_Modifiers)

add_executable( CPSTL_Vector_NonMemberFunctions NonMemberFunctionsTests.cc ) 
target_link_libraries( CPSTL_Vector_NonMemberFunctions PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_NonMemberFunctions)




add_executable( CPSTL_Vector_DynamicAllocation DynamicAllocationTests.cc ) 
target_link_libraries( CPSTL_Vector_DynamicAllocation PUBLIC CPSTL PUBLIC GTest::gtest_main )
gtest_discover_tests(CPSTL_Vector_DynamicAllocation)