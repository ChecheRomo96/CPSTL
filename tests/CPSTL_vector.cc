#if defined(ARDUINO)
    #include <Aunit.h>
    #include <aunit/contrib/gtest.h>
#endif

#if __has_include(<gtest/gtest.h>)
    #include <gtest/gtest.h>
#endif

#include <CPvector>

#if defined(CPSTL_VECTOR_ENABLED)
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the cpstd::vector class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty vector with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty vector with a size of zero.

        TEST(CPSTL_Vector_ConstructorTesting, Default) {
            cpstd::vector<uint8_t> myVector;
            ASSERT_EQ(myVector.size(),0);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the resize constructor of the cpstd::vector class.
    //! The purpose of this test is to verify that the resize constructor correctly
    //! initializes a vector with the specified size.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the resize constructor effectively creates a vector with the specified size.


        TEST(CPSTL_Vector_ConstructorTesting, Resize) {
            cpstd::vector<uint8_t> myVector(20);
            ASSERT_EQ(myVector.size(),20);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the copy constructor of the cpstd::vector class.
    //! The purpose of this test is to verify that the copy constructor correctly
    //! initializes a new vector by copying the content of an existing vector.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the copy constructor effectively creates a new vector with content identical
    //! to the original vector.

        TEST(CPSTL_Vector_ConstructorTesting, Copy) {
            cpstd::vector<uint8_t> myVector(20);
            ASSERT_EQ(myVector.size(),20);

            for(uint8_t i = 0; i < myVector.size(); i++){
                myVector[i] = i;
            }

            cpstd::vector<uint8_t> myVector2(myVector);

            for(uint8_t i = 0; i < myVector.size(); i++){
                ASSERT_EQ(myVector[i], myVector2[i]);
            }
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    // CopyConstructor2

        TEST(CPSTL_Vector_ConstructorTesting, Copy2) {

            uint8_t Data[UINT8_MAX] = {};

            for(uint8_t i = 0; i < UINT8_MAX; i++ ){
                Data[i] = i;
            }

            cpstd::vector<uint8_t> myVector(Data, UINT8_MAX);
            ASSERT_EQ(myVector.size(),UINT8_MAX);

            for(uint8_t i = 0; i < myVector.size(); i++){
                ASSERT_EQ(myVector[i], i);
            }
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the copy constructor of the cpstd::vector class with a
    //! range of data.
    //! The purpose of this test is to verify that the copy constructor correctly
    //! initializes a new vector by copying a range of data from an external array.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the copy constructor effectively creates a new vector with content identical
    //! to the specified data range.

        TEST(CPSTL_Vector_ConstructorTesting, Move) {

            static const uint8_t values[] = {0, 1, 2};
            cpstd::vector<uint8_t> myVector(values, 3);
            ASSERT_EQ(myVector.size(),3);

            for(uint8_t i = 0; i < myVector.size(); i++){
                ASSERT_EQ(myVector[i], i);
            }

            cpstd::vector<uint8_t> myVec2 = cpstd::move(myVector);

            ASSERT_EQ(myVector.size(), 0);
            ASSERT_EQ(myVector.capacity(), 0);

            for (uint8_t i = 0; i < myVec2.size(); i++){
                ASSERT_EQ(myVec2[i], i);
            }

        }
    //
    //! @test
    //! This test case assesses the copy constructor of the cpstd::vector class with a
    //! range of data.
    //! The purpose of this test is to verify that the copy constructor correctly
    //! initializes a new vector by copying a range of data from an external array.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the copy constructor effectively creates a new vector with content identical
    //! to the specified data range.

        #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
            TEST(CPSTL_Vector_ConstructorTesting, Move2) {

                std::vector<uint8_t> myVector = {0, 1, 2};

                cpstd::vector<uint8_t> myVec2 = cpstd::move(myVector);

                ASSERT_EQ(myVector.size(), 0);
                ASSERT_EQ(myVector.capacity(), 0);

                for (uint8_t i = 0; i < myVec2.size(); i++){
                    ASSERT_EQ(myVec2[i], i);
                }
            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the copy constructor of the cpstd::vector class with a
    //! range of data.
    //! The purpose of this test is to verify that the copy constructor correctly
    //! initializes a new vector by copying a range of data from an external array.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the copy constructor effectively creates a new vector with content identical
    //! to the specified data range.
        #if defined(CPSTL_USING_STL) || defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
            TEST(CPSTL_Vector_ConstructorTesting, InitializerList) {

                cpstd::vector<uint8_t> myVector = {0, 1, 2};

                ASSERT_EQ(myVector.size(), 3);
                ASSERT_EQ(myVector.capacity(), 3);

                for (uint8_t i = 0; i < myVector.size(); i++){
                    ASSERT_EQ(myVector[i], i);
                }

            }
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the "resize" functionality of the cpstd:: class.
    //! The purpose of this test is to verify that the "resize" method correctly
    //! changes the size of the vector while maintaining its content integrity.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the "resize" method effectively changes the size of the vector without
    //! affecting the content's integrity.

        TEST(CPSTL_Vector_Capacity, size) {

            cpstd::vector<uint8_t> myVector;
            ASSERT_EQ(myVector.size(),0);

            for(uint8_t i = 0; i < UINT8_MAX; i++ )
            {
                myVector.resize(i);
                ASSERT_EQ(myVector.size(),i);
            }
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the "resize" functionality of the cpstd:: class.
    //! The purpose of this test is to verify that the "resize" method correctly
    //! changes the size of the vector while maintaining its content integrity.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the "resize" method effectively changes the size of the vector without
    //! affecting the content's integrity.

        TEST(CPSTL_Vector_Capacity, resize) {

            cpstd::vector<uint8_t> myVector;
            ASSERT_EQ(myVector.size(),0);

            for(uint8_t i = 0; i < UINT8_MAX; i++ )
            {
                myVector.resize(i);
                ASSERT_EQ(myVector.size(),i);
            }
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the "resize" functionality of the cpstd:: class.
    //! The purpose of this test is to verify that the "resize" method correctly
    //! changes the size of the vector while maintaining its content integrity.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the "resize" method effectively changes the size of the vector without
    //! affecting the content's integrity.

        TEST(CPSTL_Vector_Capacity, capacity) {

            cpstd::vector<uint8_t> myVector;
            ASSERT_EQ(myVector.size(), 0);
            ASSERT_GE(myVector.capacity(), 0);

            for(uint8_t i = 0; i < UINT8_MAX; i++ )
            {
                myVector.resize(i);
                ASSERT_EQ(myVector.size(),i);
                ASSERT_GE(myVector.capacity(),i);
            }

            cpstd::vector<uint8_t> myVector2;
            myVector2.reserve(UINT8_MAX);
            ASSERT_EQ(myVector2.size(),0);
            ASSERT_GE(myVector2.capacity(), UINT8_MAX);

            for(uint8_t i = 0; i < UINT8_MAX; i++ )
            {
                myVector2.resize(i);
                ASSERT_EQ(myVector2.size(),i);
                ASSERT_GE(myVector2.capacity(), UINT8_MAX);
            }


        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the "resize" functionality of the cpstd:: class.
    //! The purpose of this test is to verify that the "resize" method correctly
    //! changes the size of the vector while maintaining its content integrity.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the "resize" method effectively changes the size of the vector without
    //! affecting the content's integrity.

        TEST(CPSTL_Vector_Capacity, empty) {

            cpstd::vector<uint8_t> myVector;
            ASSERT_EQ(myVector.empty(), 1);
            myVector.resize(10);
            ASSERT_EQ(myVector.empty(), 0);
            myVector.clear();
            ASSERT_EQ(myVector.empty(), 1);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the "resize" functionality of the cpstd:: class.
    //! The purpose of this test is to verify that the "resize" method correctly
    //! changes the size of the vector while maintaining its content integrity.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the "resize" method effectively changes the size of the vector without
    //! affecting the content's integrity.

        TEST(CPSTL_Vector_Capacity, reserve) {

            cpstd::vector<uint8_t> myVector;
            myVector.reserve(UINT8_MAX);
            ASSERT_EQ(myVector.size(),0);
            ASSERT_GE(myVector.capacity(), UINT8_MAX);

            for(uint8_t i = 0; i < UINT8_MAX; i++ )
            {
                myVector.resize(i);
                ASSERT_EQ(myVector.size(),i);
                ASSERT_GE(myVector.capacity(), UINT8_MAX);
            }
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the "resize" functionality of the cpstd:: class.
    //! The purpose of this test is to verify that the "resize" method correctly
    //! changes the size of the vector while maintaining its content integrity.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! the "resize" method effectively changes the size of the vector without
    //! affecting the content's integrity.

        TEST(CPSTL_Vector_Capacity, shrink_to_fit) {

            cpstd::vector<uint8_t> myVector;
            myVector.reserve(UINT8_MAX);
            ASSERT_EQ(myVector.size(),0);
            ASSERT_GE(myVector.capacity(), UINT8_MAX);

            myVector.resize(10);
            myVector.shrink_to_fit();

            ASSERT_EQ(myVector.size(), 10);
            ASSERT_GE(myVector.capacity(), 10);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the cpstd::vector class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty vector with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty vector with a size of zero.

        TEST(CPSTL_Vector_AssignmentTesting, cpstd_vector) {
            cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
            ASSERT_EQ(myVector.size(), (size_t) 5);
            ASSERT_EQ(myVector.capacity(), (size_t) 5);

            cpstd::vector<uint8_t> myVector2 = myVector;
            ASSERT_EQ(myVector.size(), (size_t) 5);
            ASSERT_EQ(myVector.capacity(), (size_t) 5);
            ASSERT_EQ(myVector2.size(), (size_t) 5);
            ASSERT_EQ(myVector2.capacity(), (size_t) 5);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the cpstd::vector class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty vector with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty vector with a size of zero.

        TEST(CPSTL_Vector_AssignmentTesting, cpstd_vector_move) {
            cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
            ASSERT_EQ(myVector.size(), (size_t) 5);
            ASSERT_EQ(myVector.capacity(), (size_t) 5);

            cpstd::vector<uint8_t> myVector2 = cpstd::move(myVector);
            ASSERT_EQ(myVector.size(), (size_t) 0);
            ASSERT_EQ(myVector.capacity(), (size_t) 0);
            ASSERT_EQ(myVector2.size(), (size_t) 5);
            ASSERT_EQ(myVector2.capacity(), (size_t) 5);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the cpstd::vector class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty vector with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty vector with a size of zero.

        TEST(CPSTL_Vector_AssignmentTesting, InitializerList) {
            cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
            ASSERT_EQ(myVector.size(), (size_t) 5);
            ASSERT_EQ(myVector.capacity(), (size_t) 5);

            cpstd::vector<uint8_t> myVector2 = cpstd::move(myVector);
            ASSERT_EQ(myVector.size(), (size_t) 0);
            ASSERT_EQ(myVector.capacity(), (size_t) 0);
            ASSERT_EQ(myVector2.size(), (size_t) 5);
            ASSERT_EQ(myVector2.capacity(), (size_t) 5);
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

        TEST(CPSTL_Vector_ElemetAccess, SubscriptArray) {

            cpstd::vector<uint8_t> myVector(5);
            ASSERT_EQ(myVector.size(),5);

            for(uint8_t i = 0; i < myVector.size(); i++ )
            {
                myVector[i] = i;
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

        TEST(CPSTL_Vector_ElemetAccess, at) {

            cpstd::vector<uint8_t> myVector(5);
            ASSERT_EQ(myVector.size(),5);

            for(uint8_t i = 0; i < myVector.size(); i++ ){
                myVector[i] = i;
                ASSERT_EQ(myVector.at(i),i);
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

        TEST(CPSTL_Vector_ElemetAccess, front) {

            cpstd::vector<uint8_t> myVector(5);
            ASSERT_EQ(myVector.size(),5);

            for(uint8_t i = 0; i < myVector.size(); i++ ){
                myVector[i] = i;
            }

            uint8_t count = 0;

            while( !myVector.empty() ){
                ASSERT_EQ(myVector.front(), count++);
                myVector.erase(0);
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

        TEST(CPSTL_Vector_ElemetAccess, back) {

            cpstd::vector<uint8_t> myVector(5);
            ASSERT_EQ(myVector.size(),5);

            for(size_t i = 0; i < myVector.size(); i++ ){
                myVector[i] = static_cast<uint8_t>(i);
            }

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

        TEST(CPSTL_Vector_ElemetAccess, data) {

            cpstd::vector<uint8_t> myVector(5);
            ASSERT_EQ(myVector.size(),5);

            for(uint8_t i = 0; i < myVector.size(); i++ ){
                myVector[i] = i;
                ASSERT_EQ((uint8_t)*(myVector.data()+i), i);
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

        TEST(CPSTL_Vector_Modifiers, assign_fill) {
            
            cpstd::vector<uint8_t> myVector;

            myVector.assign(5, 0xFF);

            ASSERT_EQ(myVector.size(), 5);
            ASSERT_EQ(myVector[0], 0xFF);
            ASSERT_EQ(myVector[1], 0xFF);
            ASSERT_EQ(myVector[2], 0xFF);
            ASSERT_EQ(myVector[3], 0xFF);
            ASSERT_EQ(myVector[4], 0xFF);
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
                ASSERT_EQ(myVector.size(), 5);

                ASSERT_EQ(myVector.size(), 5);
                ASSERT_EQ(myVector[0], 0);
                ASSERT_EQ(myVector[1], 1);
                ASSERT_EQ(myVector[2], 2);
                ASSERT_EQ(myVector[3], 3);
                ASSERT_EQ(myVector[4], 4);
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
                ASSERT_EQ(myVector.back().A(), i);
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
                ASSERT_EQ(myVector[i].A(),i);
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
                ASSERT_EQ(myVector[0],counter++);
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
            ASSERT_EQ(myVector.size(), 3);
            ASSERT_EQ(myVector[0], 0);
            ASSERT_EQ(myVector[1], 1);
            ASSERT_EQ(myVector[2], 4);
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

            ASSERT_EQ(myVector.size(), 5);
            ASSERT_EQ(myVector2.size(), 4);

            myVector.swap(myVector2);

            ASSERT_EQ(myVector.size(), 4);
            ASSERT_EQ(myVector2.size(), 5);
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

            ASSERT_EQ(myVector.size(),0);

            for (size_t i = 1; i < 10; i++) {
                myVector.emplace(0, cpstd::move(static_cast<uint8_t>(i)));
                ASSERT_EQ(myVector[0], i);
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

            ASSERT_EQ(myVector.size(),0);

            for(size_t i = 1; i < 10; i++){
                testClass tmp(static_cast<uint8_t>(i));
                myVector.emplace(0, cpstd::move(tmp));
                ASSERT_EQ(myVector[0].A(), i);
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
                ASSERT_EQ(myVector.back().A(), i);
                ASSERT_EQ(tmp.A(), 0);
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



        TEST(CPSTL_Vector_NonMemberFunctions, RelationalOperators_Equal) {
            
            cpstd::vector<uint8_t> myVector = {0,1,2,3,4};
            cpstd::vector<uint8_t> myVector2 = {0,1,2,3,4};

            ASSERT_EQ(myVector == myVector2, 1);
            myVector2 = {0,1,2,3};
            ASSERT_EQ(myVector == myVector2, 0);
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

            ASSERT_EQ(myVector != myVector2, 0);
            myVector2 = {0,1,2,3};
            ASSERT_EQ(myVector != myVector2, 1);
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

            ASSERT_EQ(myVector < myVector2, 1);
            myVector2 = {0,1,2,3};
            ASSERT_EQ(myVector < myVector2, 0);
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

            ASSERT_EQ(myVector > myVector2, 1);
            myVector2 = {0,1,2,3,4};
            ASSERT_EQ(myVector > myVector2, 0);
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

            ASSERT_EQ(myVector <= myVector2, 1);
            myVector2 = {0,1,2,3};
            ASSERT_EQ(myVector <= myVector2, 1);
            myVector2 = {0,1,2};
            ASSERT_EQ(myVector <= myVector2, 0);
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

            ASSERT_EQ(myVector >= myVector2, 1);
            myVector2 = {0,1,2,3,4};
            ASSERT_EQ(myVector >= myVector2, 1);
            myVector2 = {0,1,2,3,4,5};
            ASSERT_EQ(myVector >= myVector2, 0);
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

            ASSERT_EQ(myVector.size(), 5);
            ASSERT_EQ(myVector2.size(), 4);

            cpstd::swap(myVector, myVector2);

            ASSERT_EQ(myVector.size(), 4);
            ASSERT_EQ(myVector2.size(), 5);

        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the dynamic allocation and use of a CPVector pointer
    //! with the object constructor.
    //! The purpose of this test is to verify that dynamic memory allocation for a
    //! CPVector pointer and object construction using the constructor work as
    //! expected.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! dynamic memory allocation and object construction for a CPVector pointer are
    //! successful.

        TEST(CPSTL_Vector_DynamicAllocationTesting, VectorPointerToObject) {

            #if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION) || defined(CPVECTOR_USING_CPP_ALLOCATION)
                cpstd::vector<uint8_t>* myVectorptr = nullptr;

                ASSERT_EQ((void*)myVectorptr,nullptr);
                
                myVectorptr = new cpstd::vector<uint8_t>(12);

                ASSERT_NE(myVectorptr,nullptr);

                ASSERT_EQ(myVectorptr->size(),12);

                delete(myVectorptr);
            #elif (CPVECTOR_USING_C_ALLOCATION)

                cpstd::vector<uint8_t>* myVectorptr = NULL;

                ASSERT_EQ(myVectorptr,(void*)NULL);
                
                myVectorptr = (cpstd::vector<uint8_t>*)calloc(1, sizeof(cpstd::vector<uint8_t>));
                (*myVectorptr) = cpstd::vector<uint8_t>(12);

                ASSERT_NE(myVectorptr,(void*)NULL);

                ASSERT_EQ(myVectorptr->size(),12);

                delete(myVectorptr);

            #endif
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses dynamic allocation and use of a CPVector pointer to an
    //! array of vectors.
    //! The purpose of this test is to verify that dynamic memory allocation for a
    //! CPVector pointer to an array of vectors and subsequent object construction and
    //! manipulation work as expected.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! dynamic memory allocation and object manipulation for a CPVector pointer to an
    //! array of vectors are successful.

        TEST(CPSTL_Vector_DynamicAllocationTesting, VectorPointerToArray) {
        #if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION) || defined(CPVECTOR_USING_CPP_ALLOCATION)

            cpstd::vector<uint8_t>* myVectorptr = nullptr;

            ASSERT_EQ((void*)myVectorptr,nullptr);
            
            myVectorptr = new cpstd::vector<uint8_t>[8];

            ASSERT_NE(myVectorptr,nullptr);

            for(uint8_t i = 0; i < 8; i++){
                myVectorptr[i] = cpstd::vector<uint8_t>(8);
                ASSERT_EQ(myVectorptr[i].size(), 8);

                for(uint8_t j = 0; j < 8; j++){    
                    myVectorptr[i][j] = (8*i) + j;
                }
            }
            
            for(uint8_t i = 0; i < 8; i++){
                for(uint8_t j = 0; j < 8; j++){
                    ASSERT_EQ(myVectorptr[i][j], (8*i) + j);
                }
            }

            delete[] myVectorptr;
        #elif defined(CPVECTOR_USING_C_ALLOCATION)

            cpstd::vector<uint8_t>* myVectorptr = NULL;

            myVectorptr = (cpstd::vector<uint8_t>*)calloc(8, sizeof(cpstd::vector<uint8_t>));

            ASSERT_NE(myVectorptr, (void*)NULL);

            for(uint8_t i = 0; i < 8; i++){
                myVectorptr[i] = cpstd::vector<uint8_t>(8);

                for(uint8_t j = 0; j < 8; j++){    
                    myVectorptr[i][j] = (8*i) + j;
                }
            }
            
            for(uint8_t i = 0; i < 8; i++){
                for(uint8_t j = 0; j < 8; j++){
                    ASSERT_EQ(myVectorptr[i][j], (8*i) + j);
                }
                myVectorptr[i].cpstd::vector<uint8_t>::~vector();
            }
            free(myVectorptr);
            myVectorptr = NULL;

        #endif
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses dynamic allocation and use of a CPVector containing
    //! CPVector elements.
    //! The purpose of this test is to verify that dynamic memory allocation for a
    //! CPVector containing CPVector elements, resizing, and subsequent element
    //! manipulation work as expected.\n\n
    //! The test is expected to pass if all assertions hold true, demonstrating that
    //! dynamic memory allocation, resizing, and element manipulation for a CPVector
    //! containing CPVector elements are successful.

        TEST(CPSTL_Vector_DynamicAllocationTesting, VectorOfVectors) {
            cpstd::vector<cpstd::vector<uint8_t>> myVector(8);

            ASSERT_EQ(myVector.size(),8);

            for(uint8_t i = 0; i < myVector.size(); i++){
                ASSERT_EQ(myVector[i].size(),0);

                myVector[i].resize(8);
                ASSERT_EQ(myVector[i].size(),8);

                for(uint8_t j = 0; j < myVector[i].size(); j++){
                    myVector[i][j] = (8*i) + j;
                    ASSERT_EQ(myVector[i][j], (8*i) + j);
                }
            }

            for(uint8_t i = 0; i < myVector.size(); i++){
                for(uint8_t j = 0; j < myVector[i].size(); j++){
                    myVector[i][j] = (8*i) + j;
                    ASSERT_EQ(myVector[i][j], (8*i) + j);
                }
                myVector[i].clear();
            }

            myVector.clear();
        }
    //
    //////////////////////////////////////////////////////////////////////////////////
#endif