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
            std::cout<<myString.c_str()<<std::endl;
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
//////////////////////////////////////////////////////////////////////////////////