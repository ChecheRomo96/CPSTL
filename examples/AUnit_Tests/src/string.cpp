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
            ASSERT_EQ(substring[0], 'B');
            ASSERT_EQ(substring[1], 'C');
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

                cpstd::string myCopy(cpstd::move(myString));

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
    ////////////////////////////////////////////////////////////////////////////////////! @test
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
    ////////////////////////////////////////////////////////////////////////////////////! @test
    //! This test case assesses the size() method of the CPString class.
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_Modifiers, append) {
            
            { // cpstd::string
                cpstd::string a,b,c;

                a = "Hello";
                b = " ";
                c = "World";

                cpstd::string myString;
                myString.append(a);
                myString.append(b);
                myString.append(c);

                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }  

            #if defined(CPSTRING_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                { // std::string
                    std::string a,b,c;

                    a = "Hello";
                    b = " ";
                    c = "World";

                    cpstd::string myString;
                    myString.append(a);
                    myString.append(b);
                    myString.append(c);

                    ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
                }
            #endif

            { // substring
                cpstd::string a,b,c;

                a = "Hello, everyone";
                b = "The World Cup is captivating";
                c = "This is a CPVector Unit Test";

                cpstd::string myString;
                myString.append(a,0,5); //Extract "Hello" from a
                myString.append(c,4,1); //Extract ' ' from c
                myString.append(b,4,5); //Extract "World" from b

                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            } 

            { // C String
                cpstd::string myString;
                char buff[] = "Hello";
                myString.append(buff);
                ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
            }

            { // buffer
                cpstd::string myString;
                char buff[] = "Hello";
                myString.append(buff,2);
                ASSERT_EQ( strcmp(myString.c_str(), "He"), 0);
            }

            { // fill
                cpstd::string myString;
                myString.append(5,'*');
                ASSERT_EQ( strcmp(myString.c_str(), "*****"), 0);
            }

            { // Initializer list
                cpstd::string myString;
                myString.append({'H','e','l','l','o'});
                ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
            }

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

        TEST(CPSTL_String_Modifiers, push_back) {
            
            cpstd::string myString;

            myString.reserve(10);

            ASSERT_GE(myString.capacity(), 10);
            ASSERT_EQ(myString.size(), 0);

            for(uint8_t i = 0; i < 10; i++){
                myString.push_back((char)('0'+i));
            }

            ASSERT_GE(myString.capacity(), 10);
            ASSERT_EQ(myString.size(), 10);
            ASSERT_EQ( strcmp(myString.c_str(), "0123456789"), 0);
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

        TEST(CPSTL_String_Modifiers, assign) {
            
            { // cpstd::string
                cpstd::string a,b,c;

                a = "Hello";
                b = " ";
                c = "World";

                cpstd::string myString;
                myString.append(a);
                myString.append(b);
                myString.append(c);

                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                myString.assign(a);
                ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
            }   

            #if defined(CPSTRING_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                { // std::string
                    std::string a,b,c;

                    a = "Hello";
                    b = " ";
                    c = "World";

                    cpstd::string myString;
                    myString.append(a);
                    myString.append(b);
                    myString.append(c);

                    ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                    myString.assign(a);
                    ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
                }
            #endif

            { // substring
                cpstd::string a,b,c;

                a = "Hello, everyone";
                b = "The World Cup is captivating";
                c = "This is a CPVector Unit Test";

                cpstd::string myString;
                myString.append(a,0,5); //Extract "Hello" from a
                myString.append(c,4,1); //Extract ' ' from c
                myString.append(b,4,5); //Extract "World" from b

                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                myString.assign(a);
                ASSERT_EQ( strcmp(myString.c_str(), "Hello, everyone"), 0);
            }

            { // C String
                cpstd::string myString("Hello World");
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                char buff[] = "Hello";
                myString.assign(buff);
                ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
            }

            { // buffer
                cpstd::string myString("Hello World");
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                char buff[] = "Hello";
                myString.assign(buff,2);
                ASSERT_EQ( strcmp(myString.c_str(), "He"), 0);
            }

            { // fill
                cpstd::string myString("Hello World");
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                myString.assign(5,'*');
                ASSERT_EQ( strcmp(myString.c_str(), "*****"), 0);
            }

            { // move
                cpstd::string myString("Hello World");
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                cpstd::string myString2;
                ASSERT_EQ( strcmp(myString2.c_str(), ""), 0);

                myString2.assign(cpstd::move(myString));
                ASSERT_EQ( strcmp(myString.c_str(), ""), 0);
                ASSERT_EQ( strcmp(myString2.c_str(), "Hello World"), 0);
            }

            { // Initializer list
                cpstd::string myString("Hello World");
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);

                myString.assign({'H','e','l','l','o'});
                ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
            }
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

        TEST(CPSTL_String_Modifiers, insert) {
            
            { // cpstd::string
                cpstd::string a,b,c;

                a = "Hello";
                b = " ";
                c = "World";

                cpstd::string myString;
                myString.append(a);
                myString.append(c);
                myString.insert(5,b);

                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }   

            #if defined(CPSTRING_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                { // std::string
                    std::string a,b,c;

                    a = "Hello";
                    b = " ";
                    c = "World";

                    cpstd::string myString;
                    myString.append(a);
                    myString.append(c);
                    myString.insert(5,b);

                    ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
                }
            #endif

            { // substring
                cpstd::string a,b,c;

                a = "Hello, everyone";
                b = "The World Cup is captivating";
                c = "This is a CPVector Unit Test";

                cpstd::string myString;
                myString.append(a,0,5); //Extract "Hello" from a
                myString.append(b,4,5); //Extract "World" from b
                myString.insert(5,c,4,1); //Extract ' ' from c

                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }

            { // C String
                cpstd::string myString("HelloWorld");

                char buff[] = " ";
                myString.insert(5, buff);
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }

            { // buffer
                cpstd::string myString("HelloWorld");

                char buff[] = {' ', ' ', 'a'};
                myString.insert(5,buff,1);
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }

            { // fill
                cpstd::string myString("HelloWorld");

                myString.insert(5, 1,' ');
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }

            #if defined(CPSTRING_USING_STL)
            { // Initializer list
                cpstd::string myString(" World");

                myString.insert(0, {'H','e','l','l','o'});
                ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
            }
            #endif 
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

        TEST(CPSTL_String_Modifiers, erase) {
            
            cpstd::string myString("Hello, I just returned from Disney World, what an amazing trip!");
            myString.erase(5, 29);
            myString.erase(11, 23);
            ASSERT_EQ( strcmp(myString.c_str(), "Hello World"), 0);
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

        TEST(CPSTL_String_Modifiers, replace) {
            
            cpstd::string base("this is a test string.");
            cpstd::string str2("n example");
            cpstd::string str3("sample phrase");

            // replace signatures used in the same order as described above:

            cpstd::string myString=base;
            ASSERT_EQ( strcmp(myString.c_str(), "this is a test string."), 0);

            myString.replace(9,5,str2);
            ASSERT_EQ( strcmp(myString.c_str(), "this is an example string."), 0);

            myString.replace(19,6,str3,7,6); 
            ASSERT_EQ( strcmp(myString.c_str(), "this is an example phrase."), 0);

            myString.replace(8,10,"just a");   
            ASSERT_EQ( strcmp(myString.c_str(), "this is just a phrase."), 0);

            myString.replace(8,6,"a shorty",7);  
            ASSERT_EQ( strcmp(myString.c_str(), "this is a short phrase."), 0);

            myString.replace(22,1,3,'!');    
            ASSERT_EQ( strcmp(myString.c_str(), "this is a short phrase!!!"), 0);
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

        TEST(CPSTL_String_Modifiers, swap) {
            
            cpstd::string str1("String A");
            cpstd::string str2("String B");

            ASSERT_EQ( strcmp(str1.c_str(), "String A"), 0);
            ASSERT_EQ( strcmp(str2.c_str(), "String B"), 0);

            str1.swap(str2);

            ASSERT_EQ( strcmp(str1.c_str(), "String B"), 0);
            ASSERT_EQ( strcmp(str2.c_str(), "String A"), 0);
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

        TEST(CPSTL_String_Modifiers, pop_back) {
            
            cpstd::string myString("12345");
            ASSERT_EQ( strcmp(myString.c_str(), "12345"), 0);

            myString.pop_back();
            ASSERT_EQ( strcmp(myString.c_str(), "1234"), 0);

            myString.pop_back();
            ASSERT_EQ( strcmp(myString.c_str(), "123"), 0);

            myString.pop_back();
            ASSERT_EQ( strcmp(myString.c_str(), "12"), 0);

            myString.pop_back();
            ASSERT_EQ( strcmp(myString.c_str(), "1"), 0);

            myString.pop_back();
            ASSERT_EQ( strcmp(myString.c_str(), ""), 0);
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

        TEST(CPSTL_String_Modifiers, formatted) {

            cpstd::string myString2;


            myString2.formatted("Value of Pi = %.3f", 3.141516f);

            ASSERT_EQ(myString2.size(), snprintf(NULL, 0, "Value of Pi = %.3f", 3.141516f));
            ASSERT_GE(myString2.capacity(), snprintf(NULL, 0, "Value of Pi = %.3f", 3.141516f));

            int a = 10, b = 20, c;
            c = a + b;

            myString2.formatted("Sum of %d and %d is %d", a, b, c);

            ASSERT_EQ(myString2.size(), snprintf(NULL, 0, "Sum of %d and %d is %d", a, b, c));
            ASSERT_GE(myString2.capacity(), snprintf(NULL, 0, "Sum of %d and %d is %d", a, b, c));
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////! @test
    //! This test case assesses the size() method of the CPString class.
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.
        
        #if defined(CPSTRING_USING_STD_STRING)
            TEST(CPSTL_String_StringOperations, std_string_cast_operator) {
                cpstd::string myString("Hello");
                ASSERT_EQ( strcmp( ((std::string)myString).c_str(), "Hello"), 0);
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
        
        TEST(CPSTL_String_StringOperations, c_str) {
            cpstd::string myString("Hello");
            ASSERT_EQ( strcmp(myString.c_str(), "Hello"), 0);
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
        
        TEST(CPSTL_String_StringOperations, data) {
            cpstd::string myString("Hello");
            ASSERT_EQ( strcmp(myString.data(), "Hello"), 0);
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
        
        TEST(CPSTL_String_StringOperations, copy) {
            char buffer[20];
            cpstd::string str ("Test string...");
            auto length = str.copy(buffer,6,5);
            buffer[length]='\0';
            ASSERT_EQ( strcmp(buffer, "string"), 0);
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
        
        TEST(CPSTL_String_StringOperations, find) {
            cpstd::string str ("There are two needles in this haystack with needles.");
            cpstd::string str2 ("needle");

            // different member versions of find in the same order as above:
            size_t found = str.find(str2);
            ASSERT_EQ( found, 14);

            found=str.find("needles are small",found+1,6);
            ASSERT_EQ( found, 44);

            found=str.find("haystack");
            ASSERT_EQ( found, 30);

            found=str.find('.');
            ASSERT_EQ( found, 51);
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
        
        TEST(CPSTL_String_StringOperations, rfind) {
            cpstd::string str ("The sixth sick sheik's sixth sheep's sick.");
            cpstd::string key ("sixth");

            size_t found = str.rfind(key);
            ASSERT_EQ( found, 23);
            if (found!=cpstd::string::npos){
                str.replace (found,key.length(),"seventh");
            }

            ASSERT_EQ( strcmp(str.c_str(), "The sixth sick sheik's seventh sheep's sick."), 0);
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
        
        TEST(CPSTL_String_StringOperations, find_first_of) {

            // cpstd::string
            { 
                cpstd::string str ("Please, replace the vowels in this sentence by asterisks.");
                auto found = str.find_first_of(cpstd::string("aeiou"));
                
                while (found!=cpstd::string::npos){
                    str[found]='*';
                    found=str.find_first_of(cpstd::string("aeiou"),found+1);
                }

                ASSERT_EQ( strcmp(str.c_str(), "Pl**s*, r*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks."), 0);
            }

            // c string
            { 
                cpstd::string str ("Please, replace the vowels in this sentence by asterisks.");
                auto found = str.find_first_of("aeiou");
                
                while (found!=cpstd::string::npos){
                    str[found]='*';
                    found=str.find_first_of("aeiou",found+1);
                }

                ASSERT_EQ( strcmp(str.c_str(), "Pl**s*, r*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks."), 0);
            }
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
        
        namespace {
            void SplitFilename (const cpstd::string& str, cpstd::string& path, cpstd::string& file)
            {
              auto found = str.find_last_of("/\\");
              path = str.substr(0,found);
              file = str.substr(found+1);
            }
        }

        TEST(CPSTL_String_StringOperations, find_last_of) {

            // cpstd::string
            {
                cpstd::string path;
                cpstd::string file;

                cpstd::string str1(cpstd::string("/usr/bin/man"));
                SplitFilename (str1, path, file);
                ASSERT_EQ(strcmp(path.c_str(), "/usr/bin"), 0);
                ASSERT_EQ(strcmp(file.c_str(), "man"), 0);

                cpstd::string str2 (cpstd::string("c:\\windows\\winhelp.exe"));
                SplitFilename (str2, path, file);
                ASSERT_EQ(strcmp(path.c_str(), "c:\\windows"), 0);
                ASSERT_EQ(strcmp(file.c_str(), "winhelp.exe"), 0);
            }

            // c string
            {
                cpstd::string path;
                cpstd::string file;

                cpstd::string str1("/usr/bin/man");
                SplitFilename (str1, path, file);
                ASSERT_EQ( strcmp(path.c_str(), "/usr/bin"), 0);
                ASSERT_EQ( strcmp(file.c_str(), "man"), 0);

                cpstd::string str2 ("c:\\windows\\winhelp.exe");
                SplitFilename (str2, path, file);
                ASSERT_EQ( strcmp(path.c_str(), "c:\\windows"), 0);
                ASSERT_EQ( strcmp(file.c_str(), "winhelp.exe"), 0);
            }
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
        
        TEST(CPSTL_String_StringOperations, find_first_not_of) {

            cpstd::string str ("look for non-alphabetic characters...");

            auto found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");

            ASSERT_EQ( str[found], '-');
            ASSERT_EQ( found, 12);
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
        
        TEST(CPSTL_String_StringOperations, find_last_not_of) {
            cpstd::string str ("Please, erase trailing white-spaces   \n");
            cpstd::string whitespaces (" \t\f\v\n\r");

            size_t found = str.find_last_not_of(whitespaces);
            
            if (found!=cpstd::string::npos){str.erase(found+1);}
            else{str.clear();}

            ASSERT_EQ( strcmp(str.c_str(), "Please, erase trailing white-spaces"), 0);
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
        
        TEST(CPSTL_String_StringOperations, substr) {
            cpstd::string str("We think in generalities, but we live in details.");
            cpstd::string str2 = str.substr (3,5);
            size_t pos = str.find("live"); 
            cpstd::string str3 = str.substr (pos);
            str2 += " ";
            str2 += str3;
            ASSERT_EQ( strcmp(str2.c_str(), "think live in details."), 0);
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
        
        TEST(CPSTL_String_StringOperations, compare) {
            cpstd::string str1 ("green apple");
            cpstd::string str2 ("red apple");

            ASSERT_NE(str1.compare(str2), 0);
            ASSERT_EQ(str1.compare(6,5,"apple"), 0);
            ASSERT_EQ(str2.compare(str2.size()-5,5,"apple"), 0);
            ASSERT_EQ(str1.compare(6,5,str2,4,5), 0);
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////! @test
    //! This test case assesses the concatenation operator for CPString.
    //! It checks the concatenation of two CPString instances and ensures that the result
    //! is as expected. The purpose of this test is to verify that the concatenation
    //! operator (+) correctly combines the content of two CPString objects.
    //! 
    //! The test creates two CPString instances, 'a' containing "012" and 'b' containing "345".
    //! It then uses the concatenation operator (+) to combine 'a' and 'b' into a new CPString
    //! named 'result'. Finally, the test asserts that the content of 'result' matches "012345".
        /*
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_CPString_CPString) {
            cpstd::string a = "012";
            cpstd::string b = "345";
            cpstd::string result = a + b;
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with rvalue operands.
    //! It checks the concatenation of two CPString instances using std::move and ensures
    //! that the result is as expected. The purpose of this test is to verify that the concatenation
    //! operator (+) correctly combines the content of two CPString objects, where both operands
    //! are rvalues.
    //! 
    //! The test creates two CPString instances, 'a' containing "012" and 'b' containing "345".
    //! It then uses std::move to treat 'a' and 'b' as rvalues and concatenate them into a new CPString
    //! named 'result'. The test further asserts that the content of 'result' matches "012345".
    //! Additionally, it checks that the sizes of 'a' and 'b' become 0 after the concatenation.
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_rval_rval) {
            cpstd::string a = "012";
            cpstd::string b = "345";
            cpstd::string result = std::move(a) + std::move(b);
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 0);
            ASSERT_EQ(b.size(), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with a CPString and an rvalue operand.
    //! It checks the concatenation of a CPString instance and an rvalue CPString using std::move,
    //! and ensures that the result is as expected. The purpose of this test is to verify that the concatenation
    //! operator (+) correctly combines the content of a CPString and an rvalue CPString, and that the sizes
    //! of the operands are updated correctly.
    //! 
    //! The test creates two CPString instances, 'a' containing "012" and 'b' containing "345". It then uses
    //! the concatenation operator (+) to combine 'a' and std::move(b) into a new CPString named 'result'.
    //! The test further asserts that the content of 'result' matches "012345". Additionally, it checks that the
    //! size of 'a' remains 3 (the size of the original 'a') and that the size of 'b' becomes 0 after the concatenation.
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_CPString_rval) {
            cpstd::string a = "012";
            cpstd::string b = "345";
            cpstd::string result = a + std::move(b);
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 3);
            ASSERT_EQ(b.size(), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with an rvalue operand and a CPString.
    //! It checks the concatenation of an rvalue CPString and a CPString instance, and ensures that the result
    //! is as expected. The purpose of this test is to verify that the concatenation operator (+) correctly combines
    //! the content of an rvalue CPString and a CPString, and that the sizes of the operands are updated correctly.
    //! 
    //! The test creates two CPString instances, 'a' containing "012" and 'b' containing "345". It then uses
    //! std::move(a) and the concatenation operator (+) to combine them into a new CPString named 'result'.
    //! The test further asserts that the content of 'result' matches "012345". Additionally, it checks that the
    //! size of 'a' becomes 0 after the concatenation and that the size of 'b' remains 3 (the size of the original 'b').
    //! 
    //! This test case is crucial to validate the correctness of the concatenation operator for CPString instances
    //! with an rvalue CPString and a CPString.
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_rval_CPString) {
            cpstd::string a = "012";
            cpstd::string b = "345";
            cpstd::string result = std::move(a) + b;
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 0);
            ASSERT_EQ(b.size(), 3);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with a CPString and a C-string operand.
    //! It checks the concatenation of a CPString instance and a C-string, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines the content of
    //! a CPString and a C-string, and that the size of the CPString is updated correctly.
    //! 
    //! The test creates a CPString instance 'a' containing "012" and uses the concatenation operator (+) to combine
    //! it with the C-string "345" into a new CPString named 'result'. The test further asserts that the content of
    //! 'result' matches "012345" and that the size of 'a' remains 3 (the size of the original 'a').
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_CPString_Cstr) {
            cpstd::string a = "012";
            cpstd::string result = a + "345";
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 3);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with an rvalue CPString and a C-string operand.
    //! It checks the concatenation of an rvalue CPString and a C-string, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines the content of
    //! an rvalue CPString and a C-string, and that the rvalue CPString's size becomes 0.
    //! 
    //! The test creates a CPString instance 'a' containing "012" and uses std::move(a) and the concatenation operator (+)
    //! to combine it with the C-string "345" into a new CPString named 'result'. The test further asserts that the content
    //! of 'result' matches "012345" and that the size of 'a' becomes 0 after the concatenation.

        TEST(CPSTL_String_NonMemberFunctions, Concatenation_rval_Cstr) {
            cpstd::string a = "012";
            cpstd::string result = std::move(a) + "345";
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with a C-string and a CPString operand.
    //! It checks the concatenation of a C-string and a CPString instance, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines the content of
    //! a C-string and a CPString, and that the size of the CPString is updated correctly.
    //! 
    //! The test creates a CPString instance 'a' containing "345" and uses the concatenation operator (+) to combine
    //! the C-string "012" with 'a' into a new CPString named 'result'. The test further asserts that the content of
    //! 'result' matches "012345" and that the size of 'a' remains 3 (the size of the original 'a').
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_Cstr_CPString) {
            cpstd::string a = "345";
            cpstd::string result = "012" + a;
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 3);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with a C-string and an rvalue CPString operand.
    //! It checks the concatenation of a C-string and an rvalue CPString, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines the content of
    //! a C-string and an rvalue CPString, and that the rvalue CPString's size becomes 0.
    //! 
    //! The test creates a CPString instance 'a' containing "345" and uses the concatenation operator (+) to combine
    //! the C-string "012" with std::move(a) into a new CPString named 'result'. The test further asserts that the content
    //! of 'result' matches "012345" and that the size of 'a' becomes 0 after the concatenation.

        TEST(CPSTL_String_NonMemberFunctions, Concatenation_Cstr_rval) {
            cpstd::string a = "345";
            cpstd::string result = "012" + std::move(a);
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 0);
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////! The purpose of this test is to verify that the size() method correctly
    //! @test
    //! This test case assesses the concatenation operator for CPString with a CPString and a character operand.
    //! It checks the concatenation of a CPString instance and a character, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines the content of
    //! a CPString and a character, and that the size of the CPString is updated correctly.
    //! 
    //! The test creates a CPString instance 'a' containing "01234" and uses the concatenation operator (+) to combine
    //! it with the character '5' into a new CPString named 'result'. The test further asserts that the content of
    //! 'result' matches "012345" and that the size of 'a' becomes 5 (the size of the original 'a' plus one character).
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_CPString_char) {
            cpstd::string a = "01234";
            cpstd::string result = a + '5';
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 5);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with an rvalue CPString and a character operand.
    //! It checks the concatenation of an rvalue CPString and a character, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines the content of
    //! an rvalue CPString and a character, and that the rvalue CPString's size becomes 0.
    //! 
    //! The test creates a CPString instance 'a' containing "01234" and uses the concatenation operator (+) to combine
    //! std::move(a) with the character '5' into a new CPString named 'result'. The test further asserts that the content
    //! of 'result' matches "012345" and that the size of 'a' becomes 0 after the concatenation.

        TEST(CPSTL_String_NonMemberFunctions, Concatenation_rval_char) {
            cpstd::string a = "01234";
            cpstd::string result = std::move(a) + '5';
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the concatenation operator for CPString with a character operand and a CPString.
    //! It checks the concatenation of a character and a CPString, and ensures that the result is as expected.
    //! The purpose of this test is to verify that the concatenation operator (+) correctly combines a character and
    //! a CPString, and that the size of the CPString is updated correctly.
    //! 
    //! The test creates a CPString instance 'a' containing "12345" and uses the concatenation operator (+) to combine
    //! the character '0' with 'a' into a new CPString named 'result'. The test further asserts that the content of
    //! 'result' matches "012345" and that the size of 'a' remains 5 (the size of the original 'a' is not affected by
    //! the concatenation with a character).
        
        TEST(CPSTL_String_NonMemberFunctions, Concatenation_char_CPString) {
            cpstd::string a = "12345";
            cpstd::string result = '0' + a;
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 5);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, Concatenation_char_rval) {
            cpstd::string a = "12345";
            cpstd::string result = '0' + std::move(a);
            ASSERT_EQ(strcmp(result.c_str(), "012345"), 0);
            ASSERT_EQ(a.size(), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, EqualityComparisson_CPString_CPString) {
            cpstd::string a = "12345";
            cpstd::string b = "12345";
            ASSERT_EQ(a == b, 1);
            b = "54321";
            ASSERT_EQ(a==b, 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, EqualityComparisson_CPString_Cstr) {
            cpstd::string a = "12345";
            ASSERT_EQ(a == "12345", 1);
            ASSERT_EQ(a == "54321", 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, EqualityComparisson_Cstr_CPString) {
            cpstd::string a = "12345";
            ASSERT_EQ("12345" == a, 1);
            ASSERT_EQ("54321" == a, 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, InequalityComparisson_CPString_CPString) {
            cpstd::string a = "12345";
            cpstd::string b = "12345";
            ASSERT_EQ(a != b, 0);
            b = "54321";
            ASSERT_EQ(a!=b, 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, InequalityComparisson_CPString_Cstr) {
            cpstd::string a = "12345";
            ASSERT_EQ(a != "12345", 0);
            ASSERT_EQ(a != "54321", 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, InequalityComparisson_Cstr_CPString) {
            cpstd::string a = "12345";
            ASSERT_EQ("12345" != a, 0);
            ASSERT_EQ("54321" != a, 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, LessThanComparisson_CPString_CPString) {
            cpstd::string a = "aaabc";
            cpstd::string b = "aabbc";
            ASSERT_EQ(a < b, 1);
            b = "aaabb";
            ASSERT_EQ(a < b, 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, LessThanComparisson_CPString_Cstr) {
            cpstd::string a = "aaabc";
            ASSERT_EQ(a < "aabbc", 1);
            ASSERT_EQ(a < "aaabb", 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, LessThanComparisson_Cstr_CPString) {
            cpstd::string a = "aabbc";
            ASSERT_EQ("aaabc" < a, 1);
            a = "aaabb";
            ASSERT_EQ("aaabc" < a, 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, LessOrEqualThanComparisson_CPString_CPString) {
            cpstd::string a = "aaabc";
            cpstd::string b = "aabbc";
            ASSERT_EQ(a <= b, 1);
            b = a;
            ASSERT_EQ(a <= b, 1);
            b = "aaabb";
            ASSERT_EQ(a <= b, 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, LessOrEqualThanComparisson_CPString_Cstr) {
            cpstd::string a = "aaabc";
            ASSERT_EQ(a <= "aabbc", 1);
            ASSERT_EQ(a <= "aaabc", 1);
            ASSERT_EQ(a <= "aaabb", 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, LessOrEqualThanComparisson_Cstr_CPString) {
            cpstd::string a = "aabbc";
            ASSERT_EQ("aaabc" <= a, 1);
            a = "aaabc";
            ASSERT_EQ("aaabc" <= a, 1);
            a = "aaabb";
            ASSERT_EQ("aaabc" <= a, 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, GreaterThanComparisson_CPString_CPString) {
            cpstd::string a = "aaabc";
            cpstd::string b = "aabbc";
            ASSERT_EQ(a > b, 0);
            b = "aaabb";
            ASSERT_EQ(a > b, 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, GreaterThanComparisson_CPString_Cstr) {
            cpstd::string a = "aaabc";
            ASSERT_EQ(a > "aabbc", 0);
            ASSERT_EQ(a > "aaabb", 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, GreaterThanComparisson_Cstr_CPString) {
            cpstd::string a = "aabbc";
            ASSERT_EQ("aaabc" > a, 0);
            a = "aaabb";
            ASSERT_EQ("aaabc" > a, 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, GreaterOrEqualThanComparisson_CPString_CPString) {
            cpstd::string a = "aaabc";
            cpstd::string b = "aabbc";
            ASSERT_EQ(a >= b, 0);
            b = a;
            ASSERT_EQ(a >= b, 1);
            b = "aaabb";
            ASSERT_EQ(a >= b, 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, GreaterOrEqualThanComparisson_CPString_Cstr) {
            cpstd::string a = "aaabc";
            ASSERT_EQ(a >= "aabbc", 0);
            ASSERT_EQ(a >= "aaabc", 1);
            ASSERT_EQ(a >= "aaabb", 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, GreaterOrEqualThanComparisson_Cstr_CPString) {
            cpstd::string a = "aabbc";
            ASSERT_EQ("aaabc" >= a, 0);
            a = "aaabc";
            ASSERT_EQ("aaabc" >= a, 1);
            a = "aaabb";
            ASSERT_EQ("aaabc" >= a, 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.

        TEST(CPSTL_String_NonMemberFunctions, swap) {
            cpstd::string a = "1";
            cpstd::string b = "2";

            ASSERT_EQ(strcmp(a.c_str(), "1"), 0);
            ASSERT_EQ(strcmp(b.c_str(), "2"), 0);

            cpstd::swap(a,b);

            ASSERT_EQ(strcmp(a.c_str(), "2"), 0);
            ASSERT_EQ(strcmp(b.c_str(), "1"), 0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.
                            
        #if defined(CPSTRING_USING_STL) || defined(CPSTRING_USING_STD_STRING)
            TEST(CPSTL_String_NonMemberFunctions, istream) {
                cpstd::string myStr;
                std::istringstream("Hello") >> myStr;
                ASSERT_EQ(strcmp(myStr.c_str(), "Hello"), 0);
            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.
                            
        #if defined(CPSTRING_USING_STL) || defined(CPSTRING_USING_STD_STRING)
            TEST(CPSTL_String_NonMemberFunctions, ostream) {
                cpstd::string myStr = "Hello";
                std::ostringstream out;
                out << myStr;
                ASSERT_EQ(strcmp(out.str().c_str(), "Hello"), 0);
            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.
                            
        #if defined(CPSTRING_USING_STL) || defined(CPSTRING_USING_STD_STRING)
            TEST(CPSTL_String_NonMemberFunctions, getline) {

                cpstd::string myString;
                std::istringstream is;

                cpstd::getline(std::istringstream("Hello World"), myString);
                ASSERT_EQ(strcmp(myString.c_str(), "Hello World"), 0);
                myString.clear();

                cpstd::getline(std::istringstream("Hello World"), myString, ' ');
                ASSERT_EQ(strcmp(myString.c_str(), "Hello"), 0);
                myString.clear();

                is = std::istringstream("Hello World");
                cpstd::getline(is, myString);
                ASSERT_EQ(strcmp(myString.c_str(), "Hello World"), 0);
                myString.clear();

                is = std::istringstream("Hello World");
                cpstd::getline(is, myString, ' ');
                ASSERT_EQ(strcmp(myString.c_str(), "Hello"), 0);
                myString.clear();

            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! The purpose of this test is to verify that the size() method correctly
    //! returns the size (number of characters) of the CPString.\n\n
    //! The test checks the size of CPString instances after various assignments
    //! and expects the assertions to hold true, demonstrating the correctness
    //! of the size() method.
                            
        TEST(CPSTL_String_NonMemberFunctions, to__string) {

            {
                int x = INT_MAX;
                cpstd::string myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"2147483647"),0);

                x = INT_MIN;
                myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"-2147483648"),0);
            }

            {
                long x = LONG_MAX;
                cpstd::string myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"2147483647"),0);

                x = LONG_MIN;
                myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"-2147483648"),0);
            }

            {
                long long x = LLONG_MAX;
                cpstd::string myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"9223372036854775807"),0);

                x = LLONG_MIN;
                myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"-9223372036854775808"),0);
            }

            {
                unsigned x = UINT_MAX;
                cpstd::string myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"4294967295"),0);
            }

            {
                unsigned long x = ULONG_MAX;
                cpstd::string myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"4294967295"),0);
            }

            {
                unsigned long long x = ULLONG_MAX;
                cpstd::string myString = cpstd::to_string(x);
                std::cout<<myString<<std::endl;
                ASSERT_EQ(strcmp(myString.c_str(),"18446744073709551615"),0);
            }

        }*/
    //
    //////////////////////////////////////////////////////////////////////////////////
#endif