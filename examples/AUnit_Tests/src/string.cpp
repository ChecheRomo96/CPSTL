#include <Aunit.h>
#include <CPstring.h>
#include <aunit/contrib/gtest.h>

#if defined(CPSTL_STRING_ENABLED)
    
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the CPString class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty string with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty string with a size of zero.

        TEST(CPSTL_String_Constructors, Default) {
            cpstd::string myString;
            ASSERT_EQ(myString.size(), 0);
            ASSERT_GE(myString.capacity(), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        TEST(CPSTL_String_Constructors, Substring) {
            cpstd::string myString("ABCDE");
            cpstd::string substring(myString, 1, 2);

            ASSERT_EQ(myString.size(), 5);
            ASSERT_GE(myString.capacity(), 5);
            ASSERT_EQ(substring.size(), 2);
            ASSERT_GE(substring.capacity(), 2);
            EXPECT_EQ(substring[0], 'B');
            EXPECT_EQ(substring[1], 'C');
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        TEST(CPSTL_String_Constructors, fill) {
            cpstd::string myString(10, 'a');

            ASSERT_EQ(myString.size(), 10);
            ASSERT_GE(myString.capacity(), 10);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        #ifdef CPSTRING_USING_STL
            TEST(CPSTL_String_Constructors, initializer_list) {
                cpstd::string myString = {'H', 'e', 'l', 'l', 'o'};

                ASSERT_EQ(myString.size(), 5);
                ASSERT_GE(myString.capacity(), 5);


                ASSERT_EQ(myString[0], 'H');
                ASSERT_EQ(myString[1], 'e');
                ASSERT_EQ(myString[2], 'l');
                ASSERT_EQ(myString[3], 'l');
                ASSERT_EQ(myString[4], 'o');
            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        TEST(CPSTL_String_Constructors, copy_CPString) {
            cpstd::string myString = {'H', 'e', 'l', 'l', 'o'};

            ASSERT_EQ(myString.size(), 5);
            ASSERT_GE(myString.capacity(), 5);

            ASSERT_EQ(myString[0], 'H');
            ASSERT_EQ(myString[1], 'e');
            ASSERT_EQ(myString[2], 'l');
            ASSERT_EQ(myString[3], 'l');
            ASSERT_EQ(myString[4], 'o');

            cpstd::string myCopy(myString);
            
            ASSERT_EQ(myCopy.size(), 5);
            ASSERT_GE(myCopy.capacity(), 5);

            ASSERT_EQ(myCopy[0], 'H');
            ASSERT_EQ(myCopy[1], 'e');
            ASSERT_EQ(myCopy[2], 'l');
            ASSERT_EQ(myCopy[3], 'l');
            ASSERT_EQ(myCopy[4], 'o');
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        TEST(CPSTL_String_Constructors, copy_C_String) {
            cpstd::string myString("Hello");
            
            ASSERT_EQ(myString.size(), 5);
            ASSERT_GE(myString.capacity(), 5);

            ASSERT_EQ(myString[0], 'H');
            ASSERT_EQ(myString[1], 'e');
            ASSERT_EQ(myString[2], 'l');
            ASSERT_EQ(myString[3], 'l');
            ASSERT_EQ(myString[4], 'o');


            myString = cpstd::string("Hello",3);
            
            ASSERT_EQ(myString.size(), 3);
            ASSERT_GE(myString.capacity(), 3);

            ASSERT_EQ(myString[0], 'H');
            ASSERT_EQ(myString[1], 'e');
            ASSERT_EQ(myString[2], 'l');
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        TEST(CPSTL_String_Constructors, copy_Char) {
            cpstd::string myString('H');
            
            ASSERT_EQ(myString.size(), 1);
            ASSERT_GE(myString.capacity(), 1);

            ASSERT_EQ(myString[0], 'H');
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the substring constructor and functionality
    //! of the CPString class.\n\n
    //! The purpose of this test is to verify that the substring constructor and
    //! functionality of CPString work as expected.
    //! To run this test, ensure that the CPString class and relevant constructors
    //! are properly implemented.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the substring constructor and functionality of the CPString class work as expected.\n\n

        #ifdef CPSTRING_USING_STL
            TEST(CPSTL_String_Constructors, copy_std_string) {
            std::string myString = {'H', 'e', 'l', 'l', 'o'};
            cpstd::string myCopy(myString);
            
            ASSERT_EQ(myCopy.size(), 5);
            ASSERT_GE(myCopy.capacity(), 5);

            ASSERT_EQ(myCopy[0], 'H');
            ASSERT_EQ(myCopy[1], 'e');
            ASSERT_EQ(myCopy[2], 'l');
            ASSERT_EQ(myCopy[3], 'l');
            ASSERT_EQ(myCopy[4], 'o');
            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! Test case for moving a CPString to another CPString using the standard move constructor.
    //!
    //! This test case constructs a CPString with the content "Hello" and verifies its properties and content.
    //! It then moves the content to another CPString using the standard move constructor and validates the
    //! properties of both CPStrings after the move.
    //!
    //! Test Steps:
    //! 1. Create a CPString with the content "Hello" and validate its size, capacity, and content.
    //! 2. Move the content to another CPString using the standard move constructor.
    //! 3. Validate the capacity and size of both CPStrings after the move.
    //! 4. Validate the content of the destination CPString after the move.

            TEST(CPSTL_String_Constructors, move_CPString) {
                cpstd::string myString = cpstd::string("Hello");

                ASSERT_EQ(myString.size(), 5);
                ASSERT_GE(myString.capacity(), 5);

                ASSERT_EQ(myString[0], 'H');
                ASSERT_EQ(myString[1], 'e');
                ASSERT_EQ(myString[2], 'l');
                ASSERT_EQ(myString[3], 'l');
                ASSERT_EQ(myString[4], 'o');

                cpstd::string myCopy(std::move(myString));

                ASSERT_GE(myString.capacity(), 0);
                ASSERT_GE(myCopy.capacity(), 5);

                ASSERT_EQ(myCopy.size(), 5);
                ASSERT_EQ(myString.size(), 0);

                ASSERT_EQ(myCopy[0], 'H');
                ASSERT_EQ(myCopy[1], 'e');
                ASSERT_EQ(myCopy[2], 'l');
                ASSERT_EQ(myCopy[3], 'l');
                ASSERT_EQ(myCopy[4], 'o');
            }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! Test case for moving a std::string to CPString using rvalues and the move constructor.
    //!
    //! This test case demonstrates the construction of a CPString by moving the content of a std::string
    //! (an rvalue) into it, taking advantage of the move constructor. It verifies the resulting CPString's
    //! properties and content.
    //!
    //! Note: This functionality is available when CPString is configured to use `std::string` as its
    //! internal variable. Ensure that the preprocessor macro CPSTRING_USING_STD_STRING_ALLOCATION is defined,
    //! and/or the CMake cache variable CPSTRING_ALLOCATION_METHOD is set to "std::string" to enable this feature.

        #if defined(CPSTRING_USING_STD_STRING)
            TEST(CPSTL_String_Constructors, move_std_string) {

                cpstd::string myString2(std::string("Hello"));

                ASSERT_EQ(myString2.size(), 5);
                ASSERT_GE(myString2.capacity(), 5);

                ASSERT_EQ(myString2[0], 'H');
                ASSERT_EQ(myString2[1], 'e');
                ASSERT_EQ(myString2[2], 'l');
                ASSERT_EQ(myString2[3], 'l');
                ASSERT_EQ(myString2[4], 'o');

            }
        #endif
    //
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
            ASSERT_EQ(myString.size(), (size_t) 5);

            myString = cpstd::string("World");
            ASSERT_EQ(myString.size(), (size_t) 5);

            myString = cpstd::string("ABCDEFG");
            ASSERT_EQ(myString.size(), (size_t) 7);
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
            ASSERT_EQ(myString.length(), (size_t) 5);

            myString = cpstd::string("World");
            ASSERT_EQ(myString.length(), (size_t) 5);

            myString = cpstd::string("ABCDEFG");
            ASSERT_EQ(myString.length(), (size_t) 7);
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
            ASSERT_GE(myString.capacity(), (size_t) 5);

            myString = cpstd::string("World");
            ASSERT_GE(myString.capacity(), (size_t) 5);

            myString = cpstd::string("ABCDEFG");
            ASSERT_GE(myString.capacity(), (size_t) 7);
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
            ASSERT_GE(myString.capacity(), (size_t) 5);

            myString.resize(3);
            ASSERT_EQ(myString.size(), (size_t) 3);

            myString.resize(5, 'x');
            ASSERT_EQ(myString.size(), (size_t) 5);
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

            ASSERT_EQ(myString.size(), (size_t) 0);
            ASSERT_GE(myString.capacity(), (size_t) 20);

            myString.resize(10);
            ASSERT_EQ(myString.size(), (size_t) 10);
            ASSERT_GE(myString.capacity(), (size_t) 20);

            myString.resize(5);
            ASSERT_EQ(myString.size(), (size_t) 5);
            ASSERT_GE(myString.capacity(), (size_t) 20);
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

            ASSERT_EQ(myString.size(), (size_t) 5);
            ASSERT_GE(myString.capacity(), (size_t) 5);

            myString.clear();

            ASSERT_EQ(myString.size(), (size_t) 0);
            ASSERT_GE(myString.capacity(), (size_t) 5);
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

            ASSERT_EQ(myString.empty(), (bool) false);

            myString.clear();

            ASSERT_EQ(myString.empty(), (bool) true);
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
            ASSERT_EQ(myString.size(), (size_t) 5);
            ASSERT_GE(myString.capacity(), (size_t) 5);

            myString.resize(3);
            ASSERT_EQ(myString.size(), (size_t) 3);
            ASSERT_GE(myString.capacity(), (size_t) 5);

            myString.shrink_to_fit();

            ASSERT_EQ(myString.size(), (size_t) 3);
            ASSERT_GE(myString.capacity(), (size_t) 3);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
#endif