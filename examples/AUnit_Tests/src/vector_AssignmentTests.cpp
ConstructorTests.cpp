#include <Aunit.h>
#include <CPvector.h>
#include <aunit/contrib/gtest.h>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the default constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the default constructor correctly
//! initializes an empty vector with a size of zero.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the default constructor effectively creates an empty vector with a size of zero.

    TEST(CPSTL_Vector_ConstructorTesting, Default) {
        cpstd::vector<uint8_t> myVector;
        ASSERT_EQ(myVector.size(),0);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the resize constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the resize constructor correctly
//! initializes a vector with the specified size.\n\n
//! The test is expected to pass if the assertion holds true, demonstrating that
//! the resize constructor effectively creates a vector with the specified size.


    TEST(CPSTL_Vector_ConstructorTesting, Resize) {
        cpstd::vector<uint8_t> myVector(20);
        ASSERT_EQ(myVector.size(),20);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the copy constructor of the cpstd::vector class.
//! The purpose of this test is to verify that the copy constructor correctly
//! initializes a new vector by copying the content of an existing vector.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the copy constructor effectively creates a new vector with content identical
//! to the original vector.

    TEST(CPSTL_Vector_ConstructorTesting, Copy) {
        cpstd::vector<uint8_t> myVector(20);
        ASSERT_EQ(myVector.size(),20);

        for(uint8_t i = 0; i < myVector.size(); i++){
            myVector[i] = i;
        }

        cpstd::vector<uint8_t> myVector2(myVector);

        for(uint8_t i = 0; i < myVector.size(); i++){
            ASSERT_EQ(myVector[i], myVector2[i]);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
// CopyConstructor2

    TEST(CPSTL_Vector_ConstructorTesting, Copy2) {

        uint8_t Data[UINT8_MAX] = {};

        for(uint8_t i = 0; i < UINT8_MAX; i++ ){
            Data[i] = i;
        }

        cpstd::vector<uint8_t> myVector(Data, UINT8_MAX);
        ASSERT_EQ(myVector.size(),UINT8_MAX);

        for(uint8_t i = 0; i < myVector.size(); i++){
            ASSERT_EQ(myVector[i], i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the copy constructor of the cpstd::vector class with a
//! range of data.
//! The purpose of this test is to verify that the copy constructor correctly
//! initializes a new vector by copying a range of data from an external array.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the copy constructor effectively creates a new vector with content identical
//! to the specified data range.

    TEST(CPSTL_Vector_ConstructorTesting, Move) {

        static const uint8_t values[] = {0, 1, 2};
        cpstd::vector<uint8_t> myVector(values, 3);
        ASSERT_EQ(myVector.size(),3);

        for(uint8_t i = 0; i < myVector.size(); i++){
            ASSERT_EQ(myVector[i], i);
        }

        cpstd::vector<uint8_t> myVec2 = cpstd::move(myVector);

        ASSERT_EQ(myVector.size(), 0);
        ASSERT_EQ(myVector.capacity(), 0);

        for (uint8_t i = 0; i < myVec2.size(); i++){
            ASSERT_EQ(myVec2[i], i);
        }

    }
//
//! @test
//! This test case assesses the copy constructor of the cpstd::vector class with a
//! range of data.
//! The purpose of this test is to verify that the copy constructor correctly
//! initializes a new vector by copying a range of data from an external array.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the copy constructor effectively creates a new vector with content identical
//! to the specified data range.

    #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
        TEST(CPSTL_Vector_ConstructorTesting, Move2) {

            std::vector<uint8_t> myVector = {0, 1, 2};

            cpstd::vector<uint8_t> myVec2 = cpstd::move(myVector);

            ASSERT_EQ(myVector.size(), 0);
            ASSERT_EQ(myVector.capacity(), 0);

            for (uint8_t i = 0; i < myVec2.size(); i++){
                ASSERT_EQ(myVec2[i], i);
            }
        }
    #endif
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the copy constructor of the cpstd::vector class with a
//! range of data.
//! The purpose of this test is to verify that the copy constructor correctly
//! initializes a new vector by copying a range of data from an external array.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the copy constructor effectively creates a new vector with content identical
//! to the specified data range.
    #if defined(CPSTL_USING_STL) || defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
        TEST(CPSTL_Vector_ConstructorTesting, InitializerList) {

            cpstd::vector<uint8_t> myVector = {0, 1, 2};

            ASSERT_EQ(myVector.size(), 3);
            ASSERT_EQ(myVector.capacity(), 3);

            for (uint8_t i = 0; i < myVector.size(); i++){
                ASSERT_EQ(myVector[i], i);
            }

        }
    #endif
//
//////////////////////////////////////////////////////////////////////////////////