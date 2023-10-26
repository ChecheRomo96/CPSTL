#include <gtest/gtest.h>
#include <CPvector>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_ElemetAccess, SubscriptArray) {

        cpstd::vector<uint8_t> myVector(5);
        ASSERT_EQ(myVector.size(),5);

        for(uint8_t i = 0; i < myVector.size(); i++ )
        {
            myVector[i] = i;
            ASSERT_EQ(myVector[i],i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_ElemetAccess, at) {

        cpstd::vector<uint8_t> myVector(5);
        ASSERT_EQ(myVector.size(),5);

        for(uint8_t i = 0; i < myVector.size(); i++ ){
            myVector[i] = i;
            ASSERT_EQ(myVector.at(i),i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_ElemetAccess, front) {

        cpstd::vector<uint8_t> myVector(5);
        ASSERT_EQ(myVector.size(),5);

        for(uint8_t i = 0; i < myVector.size(); i++ ){
            myVector[i] = i;
        }

        uint8_t count = 0;

        while( !myVector.empty() ){
            ASSERT_EQ(myVector.front(), count++);
            myVector.erase(0);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_ElemetAccess, back) {

        cpstd::vector<uint8_t> myVector(5);
        ASSERT_EQ(myVector.size(),5);

        for(size_t i = 0; i < myVector.size(); i++ ){
            myVector[i] = static_cast<uint8_t>(i);
        }

        uint8_t count = 4;

        while( !myVector.empty() ){
            ASSERT_EQ(myVector.back(), count--);
            myVector.pop_back();
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_ElemetAccess, data) {

        cpstd::vector<uint8_t> myVector(5);
        ASSERT_EQ(myVector.size(),5);

        for(uint8_t i = 0; i < myVector.size(); i++ ){
            myVector[i] = i;
            ASSERT_EQ((uint8_t)*(myVector.data()+i), i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////