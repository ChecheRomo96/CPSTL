#include <gtest/gtest.h>
#include <CPvector>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the size() method of the CPString class.
//! The purpose of this test is to verify that the size() method correctly
//! returns the size (number of characters) of the CPString.\n\n
//! The test checks the size of CPString instances after various assignments
//! and expects the assertions to hold true, demonstrating the correctness
//! of the size() method.

    TEST(CPSTL_Vector_Modifiers, assign_fill) {
        
        cpstd::vector<uint8_t> myVector;

        myVector.assign(5, 0xFF);

        EXPECT_EQ(myVector.size(), 5);
        EXPECT_EQ(myVector[0], 0xFF);
        EXPECT_EQ(myVector[1], 0xFF);
        EXPECT_EQ(myVector[2], 0xFF);
        EXPECT_EQ(myVector[3], 0xFF);
        EXPECT_EQ(myVector[4], 0xFF);
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

    #if defined(CPSTL_USING_STL) || defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
        TEST(CPSTL_Vector_Modifiers, assign_InitializerList) {
            
            cpstd::vector<uint8_t> myVector;
            myVector.assign({ 0,1,2,3,4 });
            EXPECT_EQ(myVector.size(), 5);

            EXPECT_EQ(myVector.size(), 5);
            EXPECT_EQ(myVector[0], 0);
            EXPECT_EQ(myVector[1], 1);
            EXPECT_EQ(myVector[2], 2);
            EXPECT_EQ(myVector[3], 3);
            EXPECT_EQ(myVector[4], 4);
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

    TEST(CPSTL_Vector_Modifiers, push_back) {
        
        cpstd::vector<uint8_t> myVector;

        for(uint8_t i = 0; i < 10; i++){
            myVector.push_back(i);
            ASSERT_EQ(myVector.back(), i);
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
        class testClass {

        protected: 
            uint8_t a;

        public:
            testClass() : a(0) {}
            testClass(uint8_t x) : a(x){}
            testClass(testClass&& rhs) noexcept{
                a = rhs.a;
                rhs.a = 0;
            }

            testClass(const testClass& rhs){
                a = rhs.a;
            }

            uint8_t A() const{ return a; }

            testClass& operator=(testClass&& rhs) noexcept {
                a = rhs.a;
                rhs.a = 0;

                return *this;
            }


            testClass& operator=(const testClass& rhs) noexcept {
                a = rhs.a;

                return *this;
            }
            
            friend bool operator==(const testClass& lhs, const testClass& rhs);
        };

        bool operator==(const testClass& lhs, const testClass& rhs) {
            return lhs.a == rhs.a;
        }
    }

    TEST(CPSTL_Vector_Modifiers, push_back_move) {
        
        cpstd::vector<testClass> myVector;

        for(uint8_t i = 1; i < 10; i++){
            testClass tmp(i);
            ASSERT_EQ(tmp.A(), i);
            myVector.push_back(cpstd::move(tmp));
            ASSERT_EQ(myVector.back(), i);
            ASSERT_EQ(tmp.A(), 0);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_Modifiers, pop_back) {

        cpstd::vector<uint8_t> myVector = { 0,1,2,3,4 };

        uint8_t count = 4;

        while( !myVector.empty() ){
            ASSERT_EQ(myVector.back(), count--);
            myVector.pop_back();
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_Modifiers, insert) {

        cpstd::vector<uint8_t> myVector = { 1,3 };

        myVector.insert(0,0);
        myVector.insert(2,2);

        for(size_t i = 0; i < myVector.size(); i++){
            ASSERT_EQ(myVector[i],i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_Modifiers, insert_move) {

        cpstd::vector<testClass> myVector = { 1,3 };

        myVector.insert(cpstd::move(0),0);
        myVector.insert(cpstd::move(2),2);

        for(uint8_t i = 0; i < myVector.size(); i++){
            ASSERT_EQ(myVector[i],i);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_Modifiers, insert_fill) {

        cpstd::vector<char> myVector = { 'a', 'a' };

        myVector.insert(1, 2, 'b');

        ASSERT_EQ(myVector[0], 'a');
        ASSERT_EQ(myVector[1], 'b');
        ASSERT_EQ(myVector[2], 'b');
        ASSERT_EQ(myVector[3], 'a');
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the subscript operator [] of the CPVector class for
//! array-style element access.
//! The purpose of this test is to verify that the subscript operator correctly
//! allows access to individual elements of a CPVector, enabling reading and
//! updating their values. It also checks the size of the vector to ensure it
//! remains unchanged.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the subscript operator [] effectively enables array-style element access, and
//! the size of the vector remains consistent.

    TEST(CPSTL_Vector_Modifiers, insert_initializer_list) {

        cpstd::vector<char> myVector = { 'a', 'a' };

        myVector.insert(1, {'b', 'b'});

        ASSERT_EQ(myVector[0], 'a');
        ASSERT_EQ(myVector[1], 'b');
        ASSERT_EQ(myVector[2], 'b');
        ASSERT_EQ(myVector[3], 'a');
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "erase" functionality of the CPVector class.
//! The purpose of this test is to verify that the "erase" method correctly removes
//! elements from the vector at the specified position, decreases its size, and
//! maintains the integrity of the remaining elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "erase" method effectively removes elements from the vector, reduces its
//! size, and preserves the integrity of the remaining elements.

    TEST(CPSTL_Vector_Modifiers, erase) {

        cpstd::vector<uint8_t> myVector = { 0,1,2,3,4 };

        uint8_t counter = 0;
        
        while( !myVector.empty() ){
            EXPECT_EQ(myVector[0],counter++);
            myVector.erase(0);
        }
    }
//
/////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "erase" functionality of the CPVector class.
//! The purpose of this test is to verify that the "erase" method correctly removes
//! elements from the vector at the specified position, decreases its size, and
//! maintains the integrity of the remaining elements.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "erase" method effectively removes elements from the vector, reduces its
//! size, and preserves the integrity of the remaining elements.

    TEST(CPSTL_Vector_Modifiers, erase_range) {

        cpstd::vector<uint8_t> myVector = { 0,1,2,3,4 };
        myVector.erase(2,4);
        EXPECT_EQ(myVector.size(), 3);
        EXPECT_EQ(myVector[0], 0);
        EXPECT_EQ(myVector[1], 1);
        EXPECT_EQ(myVector[2], 4);
    }
//
/////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "swap" functionality of the CPVector class.
//! The purpose of this test is to verify that the "swap" method correctly swaps
//! elements within the vector, maintaining their integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "swap" method effectively swaps elements within the vector while
//! preserving the integrity of the swapped elements.

    TEST(CPSTL_Vector_Modifiers, swap) {

        cpstd::vector<uint8_t> myVector = { 0,1,2,3,4 };
        cpstd::vector<uint8_t> myVector2 = { 0,1,2,3 };

        EXPECT_EQ(myVector.size(), 5);
        EXPECT_EQ(myVector2.size(), 4);

        myVector.swap(myVector2);

        EXPECT_EQ(myVector.size(), 4);
        EXPECT_EQ(myVector2.size(), 5);
    }
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the "swap" functionality of the CPVector class.
//! The purpose of this test is to verify that the "swap" method correctly swaps
//! elements within the vector, maintaining their integrity.\n\n
//! The test is expected to pass if all assertions hold true, demonstrating that
//! the "swap" method effectively swaps elements within the vector while
//! preserving the integrity of the swapped elements.

    TEST(CPSTL_Vector_Modifiers, clear) {

        cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
        ASSERT_EQ(myVector.size(), 5);
        myVector.clear();
        ASSERT_EQ(myVector.size(), 0);
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


    TEST(CPSTL_Vector_Modifiers, emplace) {

        cpstd::vector<uint8_t> myVector;

        EXPECT_EQ(myVector.size(),0);

        for (size_t i = 1; i < 10; i++) {
            myVector.emplace(0, cpstd::move(static_cast<uint8_t>(i)));
            EXPECT_EQ(myVector[0], i);
        }
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


    TEST(CPSTL_Vector_Modifiers, emplace_move) {

        cpstd::vector<testClass> myVector;

        EXPECT_EQ(myVector.size(),0);

        for(size_t i = 1; i < 10; i++){
            testClass tmp(static_cast<uint8_t>(i));
            myVector.emplace(0, cpstd::move(tmp));
            EXPECT_EQ(myVector[0], i);
            ASSERT_EQ(tmp.A(), 0);
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

    TEST(CPSTL_Vector_Modifiers, emplace_back) {
        
        cpstd::vector<uint8_t> myVector;

        for(uint8_t i = 0; i < 10; i++){
            myVector.emplace_back(i);
            ASSERT_EQ(myVector.back(), i);
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

    TEST(CPSTL_Vector_Modifiers, emplace_back_move) {
        
        cpstd::vector<testClass> myVector;

        for(uint8_t i = 0; i < 10; i++){
            testClass tmp(i);
            myVector.emplace_back(cpstd::move(tmp));
            ASSERT_EQ(myVector.back(), i);
            ASSERT_EQ(tmp.A(), 0);
        }
    }
//
//////////////////////////////////////////////////////////////////////////////////