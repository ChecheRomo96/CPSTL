#include <gtest/gtest.h>
#include <CPvector>
#include <iostream>

using cpstd::initializer_list;

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    TEST(CPSTL_Vector_AssignmentTesting, cpstd_vector) {
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        ASSERT_EQ(myVector.size(),5);
        ASSERT_EQ(myVector.capacity(),5);

        cpstd::vector<uint8_t> myVector2 = myVector;
        ASSERT_EQ(myVector.size(),5);
        ASSERT_EQ(myVector.capacity(),5);
        ASSERT_EQ(myVector2.size(),5);
        ASSERT_EQ(myVector2.capacity(),5);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    TEST(CPSTL_Vector_AssignmentTesting, cpstd_vector_move) {
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        ASSERT_EQ(myVector.size(),5);
        ASSERT_EQ(myVector.capacity(),5);

        cpstd::vector<uint8_t> myVector2 = cpstd::move(myVector);
        ASSERT_EQ(myVector.size(),0);
        ASSERT_EQ(myVector.capacity(),0);
        ASSERT_EQ(myVector2.size(),5);
        ASSERT_EQ(myVector2.capacity(),5);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    TEST(CPSTL_Vector_AssignmentTesting, InitializerList) {
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        ASSERT_EQ(myVector.size(),5);
        ASSERT_EQ(myVector.capacity(),5);

        cpstd::vector<uint8_t> myVector2 = cpstd::move(myVector);
        ASSERT_EQ(myVector.size(),0);
        ASSERT_EQ(myVector.capacity(),0);
        ASSERT_EQ(myVector2.size(),5);
        ASSERT_EQ(myVector2.capacity(),5);
    }
//
//////////////////////////////////////////////////////////////////////////////////