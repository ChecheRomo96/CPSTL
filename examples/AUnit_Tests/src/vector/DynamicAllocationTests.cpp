#include <Aunit.h>
#include <CPvector.h>
#include <aunit/contrib/gtest.h>

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

            EXPECT_EQ(myVectorptr, (void*)nullptr);
            
            myVectorptr = new cpstd::vector<uint8_t>(12);

            ASSERT_NE(myVectorptr, (void*)nullptr);

            EXPECT_EQ(myVectorptr->size(),12);

            delete(myVectorptr);
        #elif (CPVECTOR_USING_C_ALLOCATION)

            cpstd::vector<uint8_t>* myVectorptr = NULL;

            EXPECT_EQ(myVectorptr,(void*)NULL);
            
            myVectorptr = (cpstd::vector<uint8_t>*)calloc(1, sizeof(cpstd::vector<uint8_t>));
            (*myVectorptr) = cpstd::vector<uint8_t>(12);

            ASSERT_NE(myVectorptr,(void*)NULL);

            EXPECT_EQ(myVectorptr->size(),12);

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

        EXPECT_EQ((void*)myVectorptr,nullptr);
        
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
                EXPECT_EQ(myVectorptr[i][j], (uint8_t) ((8*i) + j) );
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
                EXPECT_EQ(myVectorptr[i][j], (8*i) + j);
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
                EXPECT_EQ(myVector[i][j], (8*i) + j);
            }
        }

        for(uint8_t i = 0; i < myVector.size(); i++){
            for(uint8_t j = 0; j < myVector[i].size(); j++){
                myVector[i][j] = (8*i) + j;
                EXPECT_EQ(myVector[i][j], (8*i) + j);
            }
            myVector[i].clear();
        }

        myVector.clear();
    }
//
//////////////////////////////////////////////////////////////////////////////////