#ifndef CROSS_PLATFFORM_STL_VECTOR_BOOL_H
#define CROSS_PLATFFORM_STL_VECTOR_BOOL_H

    #include <CPSTL_BuildSettings.h>
    #include <utility/CPSTL_Move.h>
    #include <CPinitializer_list.h>
    #include <CPiterator.h>
    #include <CPmemory.h>
    #include <CPutility.h>
    #include <CPalgorithm.h>
    #include <utility/CPSTL_types.h>

    #if defined CPSTL_USING_STL
        #include <iostream>
    #endif

    #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
        #include "CPVector_Exceptions.h"
    #endif

    #include "CPSTL_Vector.h"
    
    namespace cpstd {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! @brief Cross Platform Vector class
        //!
        //! cpstd::Vector<T> is a dynamic-size sequence container that stores elements contiguously. It
        //! automatically expands as needed and can minimize reallocations with the reserve() function.
        //! The elements are stored contiguously, meaning you can access them through iterators or regular
        //! pointers. This allows passing pointers to vector elements to functions expecting array pointers.
        //! The storage is managed automatically, expanding as needed. Vectors usually occupy more space
        //! than static arrays since extra memory is allocated for future growth. Reallocation can be
        //! costly; you can avoid it with the reserve() function when the element count is known beforehand.
        //! @tparam T Data type for the Dynamic Array

            #ifdef CPSTL_USING_STL
                // Partial specialization for when T is bool
                template <class Alloc>
                struct vector_helper<bool, Alloc> {
                    using type = std::vector<bool, Alloc>;
                    // You can add additional functionality or overrides here if needed
                };
            #else
                template <class Alloc>
                class vector<bool, Alloc>{
                public:
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Typdefs and aliases

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Value Types

                            using value_type = bool;
                            using allocator_type = Alloc;
                            using reference = value_type&;
                            using const_reference = const value_type&;
                            using pointer = typename cpstd::allocator_traits<allocator_type>::pointer;
                            using const_pointer = typename cpstd::allocator_traits<allocator_type>::const_pointer;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Iterator Types
                        // 
                            using difference_type = cpstd::ptrdiff_t;
                            using size_type = cpstd::size_t;

                            class iterator {
                            private:
                                uint8_t* _Buffer;
                                size_type _Index;

                            public:
                                using iterator_category = cpstd::random_access_iterator_tag;
                                using value_type = bool;
                                using difference_type = cpstd::ptrdiff_t;
                                using pointer = bool*;
                                using reference = bool&;

                                // Constructor
                                iterator(uint8_t* buffer, size_type index) : _Buffer(buffer), _Index(index) {}

                                // Dereference operator
                                reference operator*() const {
                                    size_type byteIndex = _Index / 8;
                                    size_type bitIndex = _Index % 8;
                                    return (_Buffer[byteIndex] & (1 << bitIndex)) != 0;
                                }

                                // Increment and Decrement operators
                                iterator& operator++() {
                                    ++_Index;
                                    return *this;
                                }

                                iterator operator++(int) {
                                    iterator temp = *this;
                                    ++(*this);
                                    return temp;
                                }

                                iterator& operator--() {
                                    --_Index;
                                    return *this;
                                }

                                iterator operator--(int) {
                                    iterator temp = *this;
                                    --(*this);
                                    return temp;
                                }

                                // Arithmetic operators
                                iterator operator+(difference_type n) const {
                                    return iterator(_Buffer, _Index + n);
                                }

                                iterator& operator+=(difference_type n) {
                                    _Index += n;
                                    return *this;
                                }

                                iterator operator-(difference_type n) const {
                                    return iterator(_Buffer, _Index - n);
                                }

                                iterator& operator-=(difference_type n) {
                                    _Index -= n;
                                    return *this;
                                }
                            };

                            using const_iterator = const bool*;
                            using reverse_iterator = cpstd::reverse_iterator<iterator>;
                            using const_reverse_iterator = cpstd::reverse_iterator<const_iterator>;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    protected:
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Instance Variables

                            size_type _Size;
                            size_type _Capacity;
                            uint8_t* _Buffer;
                            Alloc _Alloc; // Instance of the custom allocator
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                    public:

                        bool operator[](size_type index) const {
                            return (_Buffer[index / 8] & (1 << index % 8)) != 0;
                        }
                };
            #endif    

        //!
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        

            


    }   







#endif//CROSS_PLATFFORM_STL_VECTOR_BOOL_H