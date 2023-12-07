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
        //! cpstd::Vector<value_type> is a dynamic-size sequence container that stores elements contiguously. It
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
                template <>
                class vector<bool, cpstd::allocator<uint8_t>>{
                public:
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Typdefs and aliases

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Value Types

                            using value_type = bool;
                            using allocator_type = cpstd::allocator<uint8_t>;
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

                                // Comparison operators
                                bool operator==(const iterator& rhs) const {
                                    return _Index == rhs._Index;
                                }

                                bool operator!=(const iterator& rhs) const {
                                    return !(*this == rhs);
                                }

                                bool operator<(const iterator& rhs) const {
                                    return _Index < rhs._Index;
                                }

                                bool operator<=(const iterator& rhs) const {
                                    return _Index <= rhs._Index;
                                }

                                bool operator>(const iterator& rhs) const {
                                    return _Index > rhs._Index;
                                }

                                bool operator>=(const iterator& rhs) const {
                                    return _Index >= rhs._Index;
                                }

                                // Subscript operator
                                reference operator[](difference_type n) const {
                                    return *(*this + n);
                                }
                            };

                            class const_iterator {
                            private:
                                const uint8_t* _Buffer;  // Use const pointer for const_iterator
                                size_type _Index;
                            public:
                                using iterator_category = cpstd::random_access_iterator_tag;
                                using value_type = bool;
                                using difference_type = cpstd::ptrdiff_t;
                                using pointer = const bool*;   // const-qualified pointer for const_iterator
                                using reference = const bool&;  // const-qualified reference for const_iterator

                                // Constructor
                                const_iterator(const uint8_t* buffer, size_type index) : _Buffer(buffer), _Index(index) {}

                                // Dereference operator
                                reference operator*() const {
                                    size_type byteIndex = _Index / 8;
                                    size_type bitIndex = _Index % 8;
                                    return (_Buffer[byteIndex] & (1 << bitIndex)) != 0;
                                }

                                // Increment and Decrement operators
                                const_iterator& operator++() {
                                    ++_Index;
                                    return *this;
                                }

                                const_iterator operator++(int) {
                                    const_iterator temp = *this;
                                    ++(*this);
                                    return temp;
                                }

                                const_iterator& operator--() {
                                    --_Index;
                                    return *this;
                                }

                                const_iterator operator--(int) {
                                    const_iterator temp = *this;
                                    --(*this);
                                    return temp;
                                }

                                // Arithmetic operators
                                const_iterator operator+(difference_type n) const {
                                    return const_iterator(_Buffer, _Index + n);
                                }

                                const_iterator& operator+=(difference_type n) {
                                    _Index += n;
                                    return *this;
                                }

                                const_iterator operator-(difference_type n) const {
                                    return const_iterator(_Buffer, _Index - n);
                                }

                                const_iterator& operator-=(difference_type n) {
                                    _Index -= n;
                                    return *this;
                                }

                                // Comparison operators
                                bool operator==(const const_iterator& rhs) const {
                                    return _Index == rhs._Index;
                                }

                                bool operator!=(const const_iterator& rhs) const {
                                    return !(*this == rhs);
                                }

                                bool operator<(const const_iterator& rhs) const {
                                    return _Index < rhs._Index;
                                }

                                bool operator<=(const const_iterator& rhs) const {
                                    return _Index <= rhs._Index;
                                }

                                bool operator>(const const_iterator& rhs) const {
                                    return _Index > rhs._Index;
                                }

                                bool operator>=(const const_iterator& rhs) const {
                                    return _Index >= rhs._Index;
                                }

                                // Subscript operator
                                reference operator[](difference_type n) const {
                                    return *(*this + n);
                                }
                            };

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
                        cpstd::allocator<uint8_t> _Alloc; // Instance of the custom allocator
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                public:

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // iterators

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @name Iterators
                        //! @{
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return iterator to beginning
                            //!
                            //! This function returns an iterator pointing to the beginning of the vector's elements.
                            //!
                            //! @return iterator - An iterator to the beginning of the vector.

                                iterator begin() noexcept{
                                    return iterator(_Buffer, 0);
                                }

                                const_iterator begin() const noexcept{
                                    return const_iterator(_Buffer, 0);
                                }                        
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return iterator to end
                            //!
                            //! This function returns an iterator pointing to the end of the vector's elements.
                            //!
                            //! @return iterator - An iterator to the end of the vector.

                                iterator end() noexcept{
                                    return iterator(_Buffer, _Size);
                                }

                                const_iterator end() const noexcept{
                                    return const_iterator(_Buffer, _Size);

                                }                    
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return reverse iterator to reverse beginning
                            //!
                            //! This function returns a reverse iterator pointing to the beginning of the reversed vector's elements.
                            //!
                            //! @return reverse_iterator - A reverse iterator to the beginning of the reversed vector.

                                reverse_iterator rbegin() noexcept{
                                    return reverse_iterator(_Buffer, _Size);
                                }

                                const_reverse_iterator rbegin() const noexcept{
                                    return const_reverse_iterator(_Buffer, _Size);
                                }                        
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return reverse iterator to reverse end
                            //!
                            //! This function returns a reverse iterator pointing to the end of the reversed vector's elements.
                            //!
                            //! @return reverse_iterator - A reverse iterator to the end of the reversed vector.

                                iterator rend() noexcept{
                                    return iterator(_Buffer, 0);
                                }

                                const_iterator rend() const noexcept{
                                    return const_iterator(_Buffer, 0);

                                }                    
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_iterator to beginning
                            //!
                            //! This function returns a constant iterator pointing to the beginning of the vector's elements.
                            //!
                            //! @return const_iterator - A constant iterator to the beginning of the vector's elements.

                                const_iterator cbegin() const noexcept{
                                    return const_iterator(_Buffer, 0);
                                }                        
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_iterator to end
                            //!
                            //! This function returns a constant iterator pointing to the end of the vector's elements.
                            //!
                            //! @return const_iterator - A constant iterator to the end of the vector's elements.

                                const_iterator cend() const noexcept{
                                    return const_iterator(_Buffer, _Size);

                                }                    
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_reverse_iterator to reverse beginning
                            //!
                            //! This function returns a constant reverse iterator pointing to the beginning of the vector's elements.
                            //!
                            //! @return const_reverse_iterator - A constant reverse iterator to the beginning of the vector's elements.

                                const_reverse_iterator crbegin() const noexcept{
                                    return const_reverse_iterator(_Buffer, _Size);
                                }                        
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_reverse_iterator to reverse end
                            //!
                            //! This function returns a constant reverse iterator pointing to the end of the vector's elements.
                            //!
                            //! @return const_reverse_iterator - A constant reverse iterator to the end of the vector's elements.

                                const_reverse_iterator crend() const noexcept{
                                    return const_reverse_iterator(_Buffer, 0);
                                }                    
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @}
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @name Constructors, Destructor, and Assignment Operator
                    //! @{
                        
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Default constructor
                        //!
                        //! Initializes the vector to have size() = 0, the Capacity value is undefined, it's value is only bigger than size at all times. In order to reduce 
                        //! the capacity of the vector see shrink_to_fit() or clear().
                        
                            vector() {
                                _Buffer = nullptr;
                                _Size = 0;
                                _Capacity = 0;
                            }   
                        //!
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Fill constructor. 
                        //!
                        //! Resizes the container to contain count elements, does nothing if count == 0.\n\n
                        //! If value parameter is not given additional default-inserted elements are appended\n 
                        //! If value parameter is given additional copies of value are appended.\n
                        //! @tparam count New size of the conatainer
                        //! @tparam value The value to initialize the elements with

                            explicit vector (size_type n, const allocator_type& alloc = allocator_type()) : vector(){

                                resize(n);
                            }

                            vector (size_type n, const value_type& val, const allocator_type& alloc = allocator_type()) : vector(){

                                resize(n, val);
                            }
                        //!
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief range constructor.
                        //!
                        //! Constructs a container with as many elements as the range [first,last), with each element emplace-constructed from its corresponding element in that range, in the same order.
                        //! Input iterators to the initial and final positions in a range. The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
                        //! The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
                        //! @tparam InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
                        //! @param first Input iterators to the initial and final positions in a range.
                        //! @param last Input iterators to the initial and final positions in a range.
                        //! @param alloc Allocator object.



                            template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>* = nullptr>  
                            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : vector(){
                                _Alloc = alloc;
                                assign(first, last);
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Copy constructor.
                        //!
                        //! Constructs the container with the copy of the contents of other
                        //! @tparam other another container to be used as source to initialize the elements of the container with
                        
                            vector(const vector<value_type, allocator_type>& other) : vector(){
                                resize(other.size());
                                memcpy(_Buffer, other._Buffer, _Size);
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Copy constructor.
                        //!
                        //! Constructs the container with the copy of the contents of an array of objects of type T.
                        //! @tparam pointer location of the data to copy
                        //! @tparam len number of elements to copy

                            vector(const vector& x, const allocator_type& alloc) : vector() {
                                _Alloc = alloc;
                                resize(x.size());
                                memcpy(_Buffer, x._Buffer, _Size);
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Move constructor. 
                        //!
                        //! Constructs the container with the copy of the contents of other
                        //! @tparam pointer location of the data to copy
                        //! @tparam len number of elements to copy
                        
                            vector(vector<value_type, allocator_type>&& source) noexcept: vector(){
                                cpstd::swap(_Buffer, source._Buffer);
                                cpstd::swap(_Size, source._Size);
                                cpstd::swap(_Capacity, source._Capacity);
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief cpstd::initializer list constructor. 
                        //!
                        //! Constructs the container with an initializer list
                        //! @tparam list std::initializer list with matching template argument
                        //
                            vector(cpstd::initializer_list<value_type> list): vector(){
                                resize(list.size());
                                auto it = begin();
                                for (const auto& item : list) {
                                    *it = item;
                                    ++it;
                                }
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Destructor. 
                        //!
                        //! Destroys all the elements amd changes the size and capacity to 0. (Releases the used memory)
                        
                            ~vector(){
                                if (_Buffer) {
                                    for (size_type i = 0; i < _Size; ++i) {
                                        _Alloc.destroy(&_Buffer[i]);  // Call the destructor for each element
                                    }
                                    _Alloc.deallocate(_Buffer, _Capacity);  // Deallocate the memory
                                }
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Assignment Operators

                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Assignment operator.
                            //! 
                            //! This operator is used to assign new contents to the container by replacing the existing contents.
                            //! @tparam source Another container of the same type.
                            
                                vector<value_type, allocator_type>& operator=(const vector<value_type, allocator_type>& source){
                                    if (this != &source) {
                                        resize(source.size());
                                        auto it = begin();
                                        for (const auto& item : source) {
                                            *it = item;
                                            ++it;
                                        }
                                    }
                                    return *this;
                                }
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Move Assignment operator.
                            //! 
                            //! This operator is used to assign new contents to the container by replacing the existing contents.
                            //! @tparam source Another container of the same type.
                             
                                vector<value_type, allocator_type>& operator=(vector<value_type, allocator_type>&& source) noexcept{
                                    if (this != &source) {
                                        cpstd::swap(_Buffer, source._Buffer);
                                        cpstd::swap(_Size, source._Size);
                                        cpstd::swap(_Capacity, source._Capacity);
                                    }
                                    return *this;
                                }
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief cpstd::initializer list constructor
                            //!
                            //! Constructs the container with an initializer list
                            //! @tparam list std::initializer list with matching template argument
                            //
                                vector<value_type, allocator_type>& operator=(cpstd::initializer_list<value_type> il) { 
                                    resize(il.size());
                                    auto it = begin();
                                    for (const auto& item : il) {
                                        *it = item;
                                        ++it;
                                    }
                                    return *this;
                                }
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @}
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @name Capacity
                    //! @{
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Returns the number of elements in the vector.
                        //!
                        //! This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
                        
                            size_type size() const noexcept{
                                return _Size;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Resizes the container to contain new_size elements, does nothing if new_size == size().
                        //!
                        //! If the current size is greater than new_size, the container is reduced to to fit new_size elements.\n
                        //! If the current size is less than count and value parameter is unused, then additional default-inserted elements are appended.
                        //! If the current size is less than count and value parameter is used, then additional copies of value are appended.
                        //! @tparam new_size New size of the container.
                        //! @tparam value The value to initialize the new elements with.
                         
                            void resize(size_type new_size, const_reference value = false){
                                // Calculate the new byte count
                                size_type new_byte_count = (new_size + 7) / 8;

                                if (new_size < _Size) {
                                    // Destruct elements if resizing to a smaller size
                                    for (size_type i = new_byte_count; i < _Size; ++i) {
                                        _Alloc.destroy(&_Buffer[i]);
                                    }
                                } else if (new_byte_count > _Size) {
                                    if (new_byte_count > _Capacity) {
                                        // Reallocate memory if necessary
                                        pointer new_buffer = _Alloc.allocate(new_byte_count);

                                        for (size_type i = 0; i < _Size; ++i) {
                                            _Alloc.construct(&new_buffer[i], cpstd::move(_Buffer[i])); // Move old elements to the new memory
                                            _Alloc.destroy(&_Buffer[i]);  // Destroy the old elements
                                        }
                                        _Alloc.deallocate(_Buffer, _Capacity);  // Deallocate the old memory
                                        _Buffer = new_buffer;
                                        _Capacity = new_byte_count;
                                    }
                                    // Initialize new elements if resizing to a larger size
                                    for (size_type i = _Size; i < new_byte_count; ++i) {
                                        _Alloc.construct(&_Buffer[i], value);
                                    }
                                }
                                _Size = new_byte_count * 8; // Update size in bits
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
                        //!
                        //! This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
                        //! Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
                        //! The capacity of a vector can be explicitly altered by calling member vector::reserve.
                        
                            size_type capacity() const noexcept{
                                return _Capacity;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Checks if the vector is empty.
                        //!
                        //! This function determines whether the vector contains any elements.
                        //! @return true if the vector is empty, false otherwise.

                            bool empty() const {
                                return (_Size == 0) ? true : false;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation) to a value that's greater or equal to capacity.
                        //!
                        //! If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.\n
                        //! reserve() does not change the size of the vector.\n
                        //! If after the operation the new size() is greater than old capacity() a reallocation takes place, in which case all iterators (including the end() iterator) and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.\n
                        //! After a call to reserve(), insertions will not trigger reallocation unless the insertion would make the size of the vector greater than the value of capacity().\n
                        //! If an allocation fails and exceptions are enabled (CPSTL_VECTOR_EXCEPTIONS_ENABLED), then the method throws a cpstd::bad_allocation exception.\n
                        
                            void reserve(size_type new_cap){
                                // Calculate the new byte count
                                size_type new_byte_count = (new_cap + 7) / 8;

                                if (new_cap > _Capacity) {
                                    // Reallocate memory if necessary
                                    pointer new_buffer = _Alloc.allocate(new_byte_count);

                                    for (size_type i = 0; i < _Size; ++i) {
                                        _Alloc.construct(&new_buffer[i], cpstd::move(_Buffer[i]));  // Move old elements to the new memory
                                        _Alloc.destroy(&_Buffer[i]);  // Destroy the old elements
                                    }

                                    _Alloc.deallocate(_Buffer, _Capacity);  // Deallocate the old memory
                                    _Buffer = new_buffer;
                                    _Capacity = new_byte_count*8;
                                }
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Requests the container to reduce its capacity to fit its size.
                        //!
                        //! The request is non-binding, and the container implementation is free to optimize otherwise and leave the vector with a capacity greater than its size.\n
                        //! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.                     
                         
                            void shrink_to_fit(){
                                // Calculate the new byte count
                                size_type new_byte_count = _Size / 8;

                                if ((_Capacity/8) > new_byte_count) {
                                    pointer new_buffer = _Alloc.allocate(new_byte_count);

                                    if (new_buffer) {
                                        // Move the old elements to the new memory
                                        cpstd::uninitialized_move(_Buffer, _Buffer + _Size, new_buffer);

                                        // Destroy the old elements
                                        for (size_type i = 0; i < _Size; ++i) {
                                            _Buffer[i].~T();
                                        }

                                        // Deallocate the old memory
                                        _Alloc.deallocate(_Buffer, _Capacity);

                                        // Update the buffer and capacity
                                        _Buffer = new_buffer;
                                        _Capacity = new_byte_count * 8;
                                    }
                                }
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @}
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                    void resize(size_type new_size, const_reference value = bool()) {
                        size_type new_byte_size = (new_size + 7) / 8;

                        if (new_size < _Size) {
                            // Destruct elements if resizing to a smaller size
                            for (size_type i = new_size; i < _Size; ++i) {
                                // Clear the corresponding bit in the byte
                                _Buffer[i / 8] &= ~(1 << (i % 8));
                            }
                        } else if (new_size > _Size) {
                            if (new_byte_size > capacity()) {
                                // Reallocate memory if necessary
                                uint8_t* new_buffer = _Alloc.allocate(new_byte_size);

                                // Copy old bytes to the new memory
                                for (size_type i = 0; i < (_Size + 7) / 8; ++i) {
                                    new_buffer[i] = _Buffer[i];
                                }

                                _Alloc.deallocate(_Buffer, (_Size + 7) / 8);  // Deallocate the old memory
                                _Buffer = new_buffer;
                            }

                            // Initialize new bits if resizing to a larger size
                            for (size_type i = _Size; i < new_size; ++i) {
                                // Set the corresponding bit in the byte
                                if (value) {
                                    _Buffer[i / 8] |= (1 << (i % 8));
                                }
                            }
                        }

                        _Size = new_size;
                    }

                    bool operator[](size_type index) const {
                        return (_Buffer[index / 8] & (1 << index % 8)) != 0;
                    }
                };
            #endif    

        //!
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        

            


    }   







#endif//CROSS_PLATFFORM_STL_VECTOR_BOOL_H