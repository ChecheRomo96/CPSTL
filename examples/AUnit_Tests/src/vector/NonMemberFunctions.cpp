#include <Aunit.h>
#include <CPvector.h>
#include <aunit/contrib/gtest.h>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_Equal) {
        
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        cpstd::vector<uint8_t> myVector2 = {0,1,2,3,4};

        EXPECT_EQ(myVector == myVector2, 1);
        myVector2 = {0,1,2,3};
        EXPECT_EQ(myVector == myVector2, 0);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_NotEqual) {
        
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        cpstd::vector<uint8_t> myVector2 = {0,1,2,3,4};

        EXPECT_EQ(myVector != myVector2, 0);
        myVector2 = {0,1,2,3};
        EXPECT_EQ(myVector != myVector2, 1);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_LessThan) {
        
        cpstd::vector<uint8_t> myVector = {0,1,2,3};
        cpstd::vector<uint8_t> myVector2 = {0,1,2,3,4};

        EXPECT_EQ(myVector < myVector2, 1);
        myVector2 = {0,1,2,3};
        EXPECT_EQ(myVector < myVector2, 0);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_GreaterThan) {
        
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        cpstd::vector<uint8_t> myVector2 = {0,1,2,3};

        EXPECT_EQ(myVector > myVector2, 1);
        myVector2 = {0,1,2,3,4};
        EXPECT_EQ(myVector > myVector2, 0);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_LessOrEqualThan) {
        
        cpstd::vector<uint8_t> myVector = {0,1,2,3};
        cpstd::vector<uint8_t> myVector2 = {0,1,2,3,4};

        EXPECT_EQ(myVector <= myVector2, 1);
        myVector2 = {0,1,2,3};
        EXPECT_EQ(myVector <= myVector2, 1);
        myVector2 = {0,1,2};
        EXPECT_EQ(myVector <= myVector2, 0);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_GreaterOrEqualThan) {
        

        cpstd::vector<int> myVector = {0,1,2,3,4};
        cpstd::vector<int> myVector2 = {0,1,2,3};

        EXPECT_EQ(myVector >= myVector2, 1);
        myVector2 = {0,1,2,3,4};
        EXPECT_EQ(myVector >= myVector2, 1);
        myVector2 = {0,1,2,3,4,5};
        EXPECT_EQ(myVector >= myVector2, 0);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "emplace" functionality of the CPVector class.
//! The purpose of this test is to verify that the "emplace" method correctly
//! inserts elements into the vector at the specified position, increments its
//! size, and maintains the integrity of the inserted elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "emplace" method effectively inserts elements into the vector, increases
//! its size, and preserves the integrity of the inserted elements.



    TEST(CPSTL_Vector_NonMemberFunctions, swap) {
        
        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        cpstd::vector<uint8_t> myVector2 = {0,1,2,3};

        EXPECT_EQ(myVector.size(), 5);
        EXPECT_EQ(myVector2.size(), 4);

        cpstd::swap(myVector, myVector2);

        EXPECT_EQ(myVector.size(), 4);
        EXPECT_EQ(myVector2.size(), 5);

    }
//
//////////////////////////////////////////////////////////////////////////////////