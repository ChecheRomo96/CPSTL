#include <Aunit.h>
#include <CPvector>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    test(CPSTL_Vector_AssignmentTesting_cpstd_vector) {
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        assertEqual(myVector.size(),5);
        assertEqual(myVector.capacity(),5);

        cpstd::vector<uint8_t> myVector2 = myVector;
        assertEqual(myVector.size(),5);
        assertEqual(myVector.capacity(),5);
        assertEqual(myVector2.size(),5);
        assertEqual(myVector2.capacity(),5);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    test(CPSTL_Vector_AssignmentTesting_cpstd_vector_move) {
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        assertEqual(myVector.size(),5);
        assertEqual(myVector.capacity(),5);

        cpstd::vector<uint8_t> myVector2 = cpstd::move(myVector);
        assertEqual(myVector.size(),0);
        assertEqual(myVector.capacity(),0);
        assertEqual(myVector2.size(),5);
        assertEqual(myVector2.capacity(),5);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    test(CPSTL_Vector_AssignmentTesting_InitializerList) {
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        assertEqual(myVector.size(),5);
        assertEqual(myVector.capacity(),5);

        cpstd::vector<uint8_t> myVector2 = cpstd::move(myVector);
        assertEqual(myVector.size(),0);
        assertEqual(myVector.capacity(),0);
        assertEqual(myVector2.size(),5);
        assertEqual(myVector2.capacity(),5);
    }
//
//////////////////////////////////////////////////////////////////////////////////