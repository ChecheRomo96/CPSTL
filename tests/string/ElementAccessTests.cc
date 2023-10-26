#include <gtest/gtest.h>
#include <CPstring>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.
    
    TEST(CPSTL_String_ElementAccess, SubscriptArray_read) {
        cpstd::string myString("Hello");
        ASSERT_EQ(myString[0], 'H');
        ASSERT_EQ(myString[1], 'e');
        ASSERT_EQ(myString[2], 'l');
        ASSERT_EQ(myString[3], 'l');
        ASSERT_EQ(myString[4], 'o');
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, SubscriptArray_write) {

        cpstd::string myString("     ");

        myString[0] = 'H';
        myString[1] = 'e';
        myString[2] = 'l';
        myString[3] = 'l';
        myString[4] = 'o';


        ASSERT_EQ(myString[0], 'H');
        ASSERT_EQ(myString[1], 'e');
        ASSERT_EQ(myString[2], 'l');
        ASSERT_EQ(myString[3], 'l');
        ASSERT_EQ(myString[4], 'o');

    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, at) {

        cpstd::string myString("012345");

        ASSERT_EQ(myString.at(0), '0');
        ASSERT_EQ(myString.at(1), '1');
        ASSERT_EQ(myString.at(2), '2');
        ASSERT_EQ(myString.at(3), '3');
        ASSERT_EQ(myString.at(4), '4');
        ASSERT_EQ(myString.at(5), '5');

    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, at_const) {

        const cpstd::string myString("012345");

        ASSERT_EQ(myString.at(0), '0');
        ASSERT_EQ(myString.at(1), '1');
        ASSERT_EQ(myString.at(2), '2');
        ASSERT_EQ(myString.at(3), '3');
        ASSERT_EQ(myString.at(4), '4');
        ASSERT_EQ(myString.at(5), '5');

    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, back) {

        cpstd::string myString("1");
        ASSERT_EQ(myString.back(), '1');

        cpstd::string myString2("01");
        ASSERT_EQ(myString2.back(), '1');
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify thback the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrbacking the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, back_const) {

        const cpstd::string myString("1");
        ASSERT_EQ(myString.back(), '1');

        const cpstd::string myString2("01");
        ASSERT_EQ(myString2.back(), '1');
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, front) {

        cpstd::string myString("1");
        ASSERT_EQ(myString.front(), '1');

        cpstd::string myString2("01");
        ASSERT_EQ(myString2.front(), '0');
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify thfront the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrfronting the correctness
//! of the size() method.

    TEST(CPSTL_String_ElementAccess, front_const) {

        const cpstd::string myString("1");
        ASSERT_EQ(myString.front(), '1');

        const cpstd::string myString2("01");
        ASSERT_EQ(myString2.front(), '0');
    }
//
//////////////////////////////////////////////////////////////////////////////////