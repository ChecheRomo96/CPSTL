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
    
    #if defined(CPSTRING_USING_STD_STRING)
        TEST(CPSTL_String_StringOperations, std_string_cast_operator) {
            cpstd::string myString("Hello");
            std::cout << ((std::string)myString).c_str() <<std::endl;
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
        std::size_t found = str.find(str2);
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

        std::size_t found = str.rfind(key);
        ASSERT_EQ( found, 23);
        if (found!=cpstd::string::npos)
        str.replace (found,key.length(),"seventh");

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
        cpstd::string str ("Please, replace the vowels in this sentence by asterisks.");
        auto found = str.find_first_of("aeiou");
        
        while (found!=cpstd::string::npos){
            str[found]='*';
            found=str.find_first_of("aeiou",found+1);
        }

        ASSERT_EQ( strcmp(str.c_str(), "Pl**s*, r*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks."), 0);
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
          std::cout << "Splitting: " << str << '\n';
          auto found = str.find_last_of("/\\");

          path = str.substr(0,found);
          file = str.substr(found+1);
        }
    }

    TEST(CPSTL_String_StringOperations, find_last_of) {

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
        std::size_t pos = str.find("live"); 
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
//////////////////////////////////////////////////////////////////////////////////