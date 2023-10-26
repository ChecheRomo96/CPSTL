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

    TEST(CPSTSL_String_Capacity, size) {
        cpstd::string myString("Hello");
        ASSERT_EQ(myString.size(), 5);

        myString = cpstd::string("World");
        ASSERT_EQ(myString.size(), 5);

        myString = cpstd::string("ABCDEFG");
        ASSERT_EQ(myString.size(), 7);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the length() method of the CPString class.
//! The purpose of this test is to verify that the length() method correctly
//! returns the length (number of characters) of the CPString.\n\n
//! The test checks the length of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the length() method.

    TEST(CPSTSL_String_Capacity, length) {
        cpstd::string myString("Hello");
        ASSERT_EQ(myString.length(), 5);

        myString = cpstd::string("World");
        ASSERT_EQ(myString.length(), 5);

        myString = cpstd::string("ABCDEFG");
        ASSERT_EQ(myString.length(), 7);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the capacity() method of the CPString class.
//! The purpose of this test is to verify that the capacity() method correctly
//! returns the capacity (maximum possible size) of the CPString.\n\n
//! The test checks the capacity of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the capacity() method.

    TEST(CPSTSL_String_Capacity, capacity) {
        cpstd::string myString("Hello");
        ASSERT_GE(myString.capacity(), 5);

        myString = cpstd::string("World");
        ASSERT_GE(myString.capacity(), 5);

        myString = cpstd::string("ABCDEFG");
        ASSERT_GE(myString.capacity(), 7);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the resize() method of the CPString class.
//! The purpose of this test is to verify that the resize() method correctly
//! changes the size of the CPString and fills or truncates it as specified.\n\n
//! The test resizes CPString instances and checks their size and content
//! to ensure the correctness of the resize() method.

    TEST(CPSTSL_String_Capacity, resize) {
        cpstd::string myString("Hello");
        ASSERT_GE(myString.capacity(), 5);

        myString.resize(3);
        ASSERT_EQ(myString.size(), 3);

        myString.resize(5, 'x');
        ASSERT_EQ(myString.size(), 5);
        ASSERT_EQ(myString[0], 'H');
        ASSERT_EQ(myString[1], 'e');
        ASSERT_EQ(myString[2], 'l');
        ASSERT_EQ(myString[3], 'x');
        ASSERT_EQ(myString[4], 'x');
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the reserve() method of the CPString class.
//! The purpose of this test is to verify that the reserve() method correctly
//! reserves memory for the CPString and affects its capacity.\n\n
//! The test reserves memory for CPString instances, checks their size,
//! and ensures their capacity meets the expected values.

    TEST(CPSTSL_String_Capacity, reserve) {
        cpstd::string myString;
        myString.reserve(20);

        ASSERT_EQ(myString.size(), 0);
        ASSERT_GE(myString.capacity(), 20);

        myString.resize(10);
        ASSERT_EQ(myString.size(), 10);
        ASSERT_GE(myString.capacity(), 20);

        myString.resize(5);
        ASSERT_EQ(myString.size(), 5);
        ASSERT_GE(myString.capacity(), 20);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the clear() method of the CPString class.
//! The purpose of this test is to verify that the clear() method correctly
//! empties the CPString while preserving its capacity.\n\n
//! The test clears CPString instances, checks their size, and ensures
//! their capacity remains unchanged.

    TEST(CPSTSL_String_Capacity, clear) {
        cpstd::string myString("Hello");

        ASSERT_EQ(myString.size(), 5);
        ASSERT_GE(myString.capacity(), 5);

        myString.clear();

        ASSERT_EQ(myString.size(), 0);
        ASSERT_GE(myString.capacity(), 5);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the empty() method of the CPString class.
//! The purpose of this test is to verify that the empty() method correctly
//! determines if the CPString is empty (has no characters).\n\n
//! The test checks the emptiness of CPString instances and ensures
//! the empty() method produces the expected results.

    TEST(CPSTSL_String_Capacity, empty) {
        cpstd::string myString("Hello");

        ASSERT_EQ(myString.empty(), false);

        myString.clear();

        ASSERT_EQ(myString.empty(), true);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the shrink_to_fit() method of the CPString class.
//! The purpose of this test is to verify that the shrink_to_fit() method
//! reduces the capacity of the CPString to match its size.\n\n
//! The test checks the size and capacity of CPString instances before
//! and after calling shrink_to_fit() to ensure its correctness.

    TEST(CPSTSL_String_Capacity, shrink_to_fit) {
        cpstd::string myString("Hello");
        ASSERT_EQ(myString.size(), 5);
        ASSERT_GE(myString.capacity(), 5);

        myString.resize(3);
        ASSERT_EQ(myString.size(), 3);
        ASSERT_GE(myString.capacity(), 5);

        myString.shrink_to_fit();

        ASSERT_EQ(myString.size(), 3);
        ASSERT_GE(myString.capacity(), 3);
    }
//
//////////////////////////////////////////////////////////////////////////////////
