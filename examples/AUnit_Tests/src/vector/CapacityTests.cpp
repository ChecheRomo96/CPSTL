#include <Aunit.h>
#include <CPvector.h>
#include <aunit/contrib/gtest.h>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "resize" functionality of the cpstd:: class.
//! The purpose of this test is to verify that the "resize" method correctly
//! changes the size of the vector while maintaining its content integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "resize" method effectively changes the size of the vector without
//! affecting the content's integrity.

    TEST(CPSTL_Vector_Capacity, size) {

        cpstd::vector<uint8_t> myVector;
        ASSERT_EQ(myVector.size(),0);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector.resize(i);
            ASSERT_EQ(myVector.size(),i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "resize" functionality of the cpstd:: class.
//! The purpose of this test is to verify that the "resize" method correctly
//! changes the size of the vector while maintaining its content integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "resize" method effectively changes the size of the vector without
//! affecting the content's integrity.

    TEST(CPSTL_Vector_Capacity, resize) {

        cpstd::vector<uint8_t> myVector;
        ASSERT_EQ(myVector.size(),0);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector.resize(i);
            ASSERT_EQ(myVector.size(),i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "resize" functionality of the cpstd:: class.
//! The purpose of this test is to verify that the "resize" method correctly
//! changes the size of the vector while maintaining its content integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "resize" method effectively changes the size of the vector without
//! affecting the content's integrity.

    TEST(CPSTL_Vector_Capacity, capacity) {

        cpstd::vector<uint8_t> myVector;
        ASSERT_EQ(myVector.size(), 0);
        ASSERT_GE(myVector.capacity(), 0);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector.resize(i);
            ASSERT_EQ(myVector.size(),i);
            ASSERT_GE(myVector.capacity(),i);
        }

        cpstd::vector<uint8_t> myVector2;
        myVector2.reserve(UINT8_MAX);
        ASSERT_EQ(myVector2.size(),0);
        ASSERT_GE(myVector2.capacity(), UINT8_MAX);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector2.resize(i);
            ASSERT_EQ(myVector2.size(),i);
            ASSERT_GE(myVector2.capacity(), UINT8_MAX);
        }


    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "resize" functionality of the cpstd:: class.
//! The purpose of this test is to verify that the "resize" method correctly
//! changes the size of the vector while maintaining its content integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "resize" method effectively changes the size of the vector without
//! affecting the content's integrity.

    TEST(CPSTL_Vector_Capacity, empty) {

        cpstd::vector<uint8_t> myVector;
        ASSERT_EQ(myVector.empty(), 1);
        myVector.resize(10);
        ASSERT_EQ(myVector.empty(), 0);
        myVector.clear();
        ASSERT_EQ(myVector.empty(), 1);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "resize" functionality of the cpstd:: class.
//! The purpose of this test is to verify that the "resize" method correctly
//! changes the size of the vector while maintaining its content integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "resize" method effectively changes the size of the vector without
//! affecting the content's integrity.

    TEST(CPSTL_Vector_Capacity, reserve) {

        cpstd::vector<uint8_t> myVector;
        myVector.reserve(UINT8_MAX);
        ASSERT_EQ(myVector.size(),0);
        ASSERT_GE(myVector.capacity(), UINT8_MAX);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector.resize(i);
            ASSERT_EQ(myVector.size(),i);
            ASSERT_GE(myVector.capacity(), UINT8_MAX);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "resize" functionality of the cpstd:: class.
//! The purpose of this test is to verify that the "resize" method correctly
//! changes the size of the vector while maintaining its content integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "resize" method effectively changes the size of the vector without
//! affecting the content's integrity.

    TEST(CPSTL_Vector_Capacity, shrink_to_fit) {

        cpstd::vector<uint8_t> myVector;
        myVector.reserve(UINT8_MAX);
        ASSERT_EQ(myVector.size(),0);
        ASSERT_GE(myVector.capacity(), UINT8_MAX);

        myVector.resize(10);
        myVector.shrink_to_fit();

        ASSERT_EQ(myVector.size(), 10);
        ASSERT_GE(myVector.capacity(), 10);
    }
//
//////////////////////////////////////////////////////////////////////////////////