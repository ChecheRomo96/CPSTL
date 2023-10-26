#include <gtest/gtest.h>
#include <CPString.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "reserve" functionality of the CPString::string class.
//! The purpose of this test is to verify that the "reserve" method correctly
//! allocates memory to accommodate the specified capacity without affecting the
//! size of the string.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "reserve" method correctly allocates memory as specified without changing
//! the size of the string.

    TEST(BasicFunctionalityTesting, reserve) {

        CPString::string<uint8_t> myVector;
        ASSERT_EQ(myVector.size(),0);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector.resize(i);
            ASSERT_EQ(myVector.size(),i);
            ASSERT_GE(myVector.capacity(),i);
        }

        myVector.clear();
        ASSERT_EQ(myVector.size(),0);
        ASSERT_EQ(myVector.capacity(),0);

        myVector.reserve(UINT8_MAX);
        ASSERT_EQ(myVector.size(),0);
        ASSERT_GE(myVector.capacity(),UINT8_MAX);

        for(uint8_t i = 0; i < UINT8_MAX; i++ )
        {
            myVector.resize(i);
            ASSERT_EQ(myVector.size(),i);
            ASSERT_GE(myVector.capacity(),UINT8_MAX);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
