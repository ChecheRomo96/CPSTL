#include <gtest/gtest.h>
#include <CPstring>
#include <iostream>
/*
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the concatenation operator for CPString.
//! It checks the concatenation of two CPString instances and ensures that the result
//! is as expected. The purpose of this test is to verify that the concatenation
//! operator (+) correctly combines the content of two CPString objects.
//! 
//! The test creates two CPString instances, 'a' containing "012" and 'b' containing "345".
//! It then uses the concatenation operator (+) to combine 'a' and 'b' into a new CPString
//! named 'result'. Finally, the test asserts that the content of 'result' matches "012345".
    
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

    }
//
//////////////////////////////////////////////////////////////////////////////////
*/