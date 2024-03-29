#ifndef CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H
#define CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H

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
        #include <vector>
    #endif

    #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
        #include "CPVector_Exceptions.h"
    #endif
    
    namespace cpstd {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // class and friend function forward declarartion

            template <class T, class Alloc = cpstd::allocator<T>>
            class  vector;

            template <class T, class Alloc>
            bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

            template <class T, class Alloc>
            void swap(vector<T, Alloc>& x);
        //
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

            #ifdef CPSTL_USING_STL_ALLOCATION

                namespace {
                    template <class T, class Alloc = std::allocator<T>>
                    struct vector_helper {
                        using type = std::vector<T, Alloc>;
                    };
                }

                template <class T, class Alloc = std::allocator<T>>
                using vector = typename vector_helper<T, Alloc>::type;
            #else

                template <class T, class Alloc>
                class  vector{
                public:
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Typdefs and aliases
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Value Types

                            using value_type = T;
                            using allocator_type = Alloc;
                            using reference = value_type&;
                            using const_reference = const value_type&;
                            using pointer = typename cpstd::allocator_traits<allocator_type>::pointer;
                            using const_pointer = typename cpstd::allocator_traits<allocator_type>::const_pointer;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Iterator Types

                            using iterator = T*;
                            using const_iterator = const T*;
                            using reverse_iterator = cpstd::reverse_iterator<iterator>;
                            using const_reverse_iterator = cpstd::reverse_iterator<const_iterator>;
                            using difference_type = cpstd::ptrdiff_t;
                            using size_type = cpstd::size_t;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                protected:
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Instance Variables

                        size_type _Size;
                        size_type _Capacity;
                        T* _Buffer;
                        Alloc _Alloc; // Instance of the custom allocator
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

                                iterator begin() noexcept;
                                const_iterator begin() const noexcept;
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return iterator to end
                            //!
                            //! This function returns an iterator pointing to the end of the vector's elements.
                            //!
                            //! @return iterator - An iterator to the end of the vector.

                                iterator end() noexcept;
                                const_iterator end() const noexcept;       
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return reverse iterator to reverse beginning
                            //!
                            //! This function returns a reverse iterator pointing to the beginning of the reversed vector's elements.
                            //!
                            //! @return reverse_iterator - A reverse iterator to the beginning of the reversed vector.

                                reverse_iterator rbegin() noexcept;
                                const_reverse_iterator rbegin() const noexcept;
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return reverse iterator to reverse end
                            //!
                            //! This function returns a reverse iterator pointing to the end of the reversed vector's elements.
                            //!
                            //! @return reverse_iterator - A reverse iterator to the end of the reversed vector.

                                iterator rend() noexcept;
                                const_iterator rend() const noexcept; 
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_iterator to beginning
                            //!
                            //! This function returns a constant iterator pointing to the beginning of the vector's elements.
                            //!
                            //! @return const_iterator - A constant iterator to the beginning of the vector's elements.

                                const_iterator cbegin() const noexcept;                      
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_iterator to end
                            //!
                            //! This function returns a constant iterator pointing to the end of the vector's elements.
                            //!
                            //! @return const_iterator - A constant iterator to the end of the vector's elements.

                                const_iterator cend() const noexcept;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_reverse_iterator to reverse beginning
                            //!
                            //! This function returns a constant reverse iterator pointing to the beginning of the vector's elements.
                            //!
                            //! @return const_reverse_iterator - A constant reverse iterator to the beginning of the vector's elements.

                                const_reverse_iterator crbegin() const noexcept;
                            //!
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Return const_reverse_iterator to reverse end
                            //!
                            //! This function returns a constant reverse iterator pointing to the end of the vector's elements.
                            //!
                            //! @return const_reverse_iterator - A constant reverse iterator to the end of the vector's elements.

                                const_reverse_iterator crend() const noexcept;
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
                        
                                vector();
                        //!
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Fill constructor. 
                        //!
                        //! Resizes the container to contain count elements, does nothing if count == 0.\n\n
                        //! If value parameter is not given additional default-inserted elements are appended\n 
                        //! If value parameter is given additional copies of value are appended.\n
                        //! @tparam count New size of the conatainer
                        //! @tparam value The value to initialize the elements with

                            explicit vector(size_type n, const allocator_type& alloc = allocator_type());
                            vector(size_type n, const value_type& val, const allocator_type& alloc = allocator_type());
                        //!
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Range constructor.
                        //!
                        //! Constructs a container with as many elements as the range [first,last), with each element emplace-constructed from its corresponding element in that range, in the same order.
                        //! Input iterators to the initial and final positions in a range. The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
                        //! The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
                        //! @tparam InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
                        //! @param first Input iterators to the initial and final positions in a range.
                        //! @param last Input iterators to the initial and final positions in a range.
                        //! @param alloc Allocator object.

                            template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>* = nullptr>  
                            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Copy constructor.
                        //!
                        //! Constructs the container with the copy of the contents of other
                        //! @tparam other another container to be used as source to initialize the elements of the container with
                        
                            vector(const vector<value_type, allocator_type>& other);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Copy constructor.
                        //!
                        //! Constructs the container with the copy of the contents of an array of objects of type T.
                        //! @tparam pointer location of the data to copy
                        //! @tparam len number of elements to copy

                            vector(const vector& x, const allocator_type& alloc);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Move constructor. 
                        //!
                        //! Constructs the container with the copy of the contents of other
                        //! @tparam pointer location of the data to copy
                        //! @tparam len number of elements to copy
                        
                            vector(vector<value_type, allocator_type>&& source) noexcept;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief cpstd::initializer list constructor. 
                        //!
                        //! Constructs the container with an initializer list
                        //! @tparam list std::initializer list with matching template argument
                        //
                            vector(cpstd::initializer_list<T> list);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Destructor. 
                        //!
                        //! Destroys all the elements amd changes the size and capacity to 0. (Releases the used memory)
                        
                            ~vector();
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Assignment Operators

                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Assignment operator.
                            //! 
                            //! This operator is used to assign new contents to the container by replacing the existing contents.
                            //! @tparam source Another container of the same type.
                            
                                vector<value_type, allocator_type>& operator=(const vector<value_type, allocator_type>& source);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Move Assignment operator.
                            //! 
                            //! This operator is used to assign new contents to the container by replacing the existing contents.
                            //! @tparam source Another container of the same type.
                             
                                vector<value_type, allocator_type>& operator=(vector<value_type, allocator_type>&& source) noexcept;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief cpstd::initializer list constructor
                            //!
                            //! Constructs the container with an initializer list
                            //! @tparam list std::initializer list with matching template argument
                            //
                                vector<value_type, allocator_type>& operator=(cpstd::initializer_list<T> il);
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
                        
                            size_type size() const noexcept;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Resizes the container to contain new_size elements, does nothing if new_size == size().
                        //!
                        //! If the current size is greater than new_size, the container is reduced to to fit new_size elements.\n
                        //! If the current size is less than count and value parameter is unused, then additional default-inserted elements are appended.
                        //! If the current size is less than count and value parameter is used, then additional copies of value are appended.
                        //! @tparam new_size New size of the container.
                        //! @tparam value The value to initialize the new elements with.
                         
                            void resize(size_type new_size, const_reference value = T());
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
                        //!
                        //! This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
                        //! Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
                        //! The capacity of a vector can be explicitly altered by calling member vector::reserve.
                        
                            size_type capacity() const noexcept;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Checks if the vector is empty.
                        //!
                        //! This function determines whether the vector contains any elements.
                        //! @return true if the vector is empty, false otherwise.

                            bool empty() const;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation) to a value that's greater or equal to capacity.
                        //!
                        //! If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.\n
                        //! reserve() does not change the size of the vector.\n
                        //! If after the operation the new size() is greater than old capacity() a reallocation takes place, in which case all iterators (including the end() iterator) and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.\n
                        //! After a call to reserve(), insertions will not trigger reallocation unless the insertion would make the size of the vector greater than the value of capacity().\n
                        //! If an allocation fails and exceptions are enabled (CPSTL_VECTOR_EXCEPTIONS_ENABLED), then the method throws a cpstd::bad_allocation exception.\n
                        
                            void reserve(size_type new_cap);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Requests the container to reduce its capacity to fit its size.
                        //!
                        //! The request is non-binding, and the container implementation is free to optimize otherwise and leave the vector with a capacity greater than its size.\n
                        //! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.                     
                         
                            void shrink_to_fit();
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @}
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @name Element Access
                    //! @{
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Subscript Array Operators
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Non-const subscript array operator. This operator references the element at the specified position.
                            //!
                            //! Similar to the at() function, it might cause undefined behavior if the position is out of the vector's size bounds.
                            //! @param position Position of the element to fetch.
                            
                                reference operator[](size_type position);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Const subscript array operator. This operator references the element at the specified position, providing read-only access.
                            //!
                            //! Similar to the at() function, it might cause undefined behavior if the position is out of the vector's size bounds.
                            //! @param position Position of the element to fetch.

                                const_reference operator[](size_type position) const;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // at
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access element
                            //!
                            //! Returns a reference to the element at position n in the vector.
                            //! The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it 
                            //! is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
                            //! @tparam position Position of an element in the container.
                            //! If this is greater than, or equal to, the vector size, an exception of type out_of_range is thrown.\n
                            //! Notice that the first element has a position of 0 (not 1).\n
                            //! Member type size_type is an unsigned integral type.\n
                            
                                reference at(size_type position);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access element
                            //!
                            //! Returns a const_reference to the element at position n in the vector.
                            //! The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it 
                            //! is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
                            //! @tparam position Position of an element in the container.
                            //! If this is greater than, or equal to, the vector size, an exception of type out_of_range is thrown.\n
                            //! Notice that the first element has a position of 0 (not 1).\n
                            //! Member type size_type is an unsigned integral type.\n

                                const_reference at(size_type position) const;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // front
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access first element 
                            //!
                            //! Returns a reference to the first element in the vector.\n
                            //! Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.\n
                            //! Calling this function on an empty container causes undefined behavior.
                            
                                reference front();
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access first element 
                            //!
                            //! Returns a const_reference to the first element in the vector.\n
                            //! Unlike member vector::begin, which returns an const_iterator to this same element, this function returns a direct const_reference.\n
                            //! Calling this function on an empty container causes undefined behavior.

                                const_reference front() const;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // back
                        
                             //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access first element 
                            //!
                            //! Returns a reference to the last element in the vector.\n
                            //! Unlike member vector::end, which returns an iterator to this same element, this function returns a direct reference.\n
                            //! Calling this function on an empty container causes undefined behavior.
                            
                                reference back();
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access first element 
                            //!
                            //! Returns a const_reference to the last element in the vector.\n
                            //! Unlike member vector::end, which returns an const_iterator to this same element, this function returns a direct const_reference.\n
                            //! Calling this function on an empty container causes undefined behavior.

                                const_reference back() const;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // data
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Access data
                            //!
                            //! Returns a direct pointer to the memory array used internally by the vector to store its owned elements if the function is non-const.
                            //! For the const version, returns a direct const_pointer to the memory array.
                            //!
                            //! Because elements in the vector are guaranteed to be stored in contiguous storage locations in the same 
                            //! order as represented by the vector, the pointer retrieved can be offset to access any element in the array.
                            //!
                            //! @return For the non-const version, returns a pointer to the memory array. For the const version, returns a const_pointer.
                            
                                pointer data() noexcept;
                                const_pointer data() const noexcept;
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @}
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @name Modifiers
                    //! @{
                        
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // assign

                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
                            //!
                            //! In the range version, the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
                            //!
                            //! @param n   New size for the container.
                            //! @param val Value to fill the container with. Each of the 'n' elements in the container will be initialized to a copy of this value.
                                
                                template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>* = nullptr>  
                                void assign (InputIterator first, InputIterator last);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Assigns new contents to the container by initializing it with 'n' elements, each initialized to a copy of 'val'.
                            //!
                            //! @param n   New size for the container.
                            //! @param val Value to fill the container with. Each of the 'n' elements in the container will be initialized to a copy of this value.
                                
                                void assign(size_type n, const value_type& val);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Assigns new contents to the container by replacing the existing contents with the elements from another container.
                            //!
                            //! @param il Another container of the same type used to assign the new contents to this container.
                             
                                void assign(cpstd::initializer_list<T> il);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // push_back
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Appends the given element value to the end of the container.
                            //! 
                            //! Increases the size of the container by one and appends the given 'value' at the end.
                            //!
                            //! @param value The value to be added at the end of the container.

                                void push_back(const_reference value);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Appends the given element value to the end of the container.
                            //!
                            //! If after the operation the new size() is greater than old capacity() a reallocation takes place.
                            //! The class used must implement the proper move semantics in order for this method to be able to call a move assignment operator.
                            //! @tparam value the value of the element to append.

                                void push_back(value_type&& Rvalue);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Delete the last elemnt
                        //!
                        //! When you call this method on an empty vector, it leads to undefined behavior. The C++ standard does not specify what should happen in this scenario. Attempting to remove an element from an empty container is an error and can cause the program to crash or produce incorrect results.
                        //! @tparam value The value of the element to append.
                        //! @return Returns the poped value
                        
                            void pop_back();
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // insert

                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Insert an element into the vector at a specified position.
                            //!
                            //! Inserts a copy of the specified value into the vector at the specified position, expanding the container if necessary. If the position is beyond the end of the vector, the behavior is undefined.
                            //!
                            //! @param position Iterator pointing to the position where the element will be inserted.
                            //! @param val The value of the element to insert.
                            //! @return An iterator pointing to the first inserted element, or to the existing element if no insertion happens.
                                
                                iterator insert(const_iterator position, const value_type& val);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Insert multiple copies of an element into the vector at a specified position.
                            //!
                            //! Inserts n copies of the specified value into the vector at the specified position, expanding the container if necessary. The behavior is undefined if the position is beyond the end of the vector.
                            //!
                            //! @param position Iterator pointing to the position where the elements will be inserted.
                            //! @param n The number of elements to insert.
                            //! @param val The value of the element to insert.
                            //! @return An iterator pointing to the first inserted element, or to the existing element if no insertion happens.
                            
                                iterator insert(const_iterator position, size_type n, const value_type& val);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Move-construct and insert an element into the vector at a specified position.
                            //!
                            //! Constructs an element in place at the specified position using move semantics, expanding the container if necessary. If the position is beyond the end of the vector, the behavior is undefined.
                            //!
                            //! @param position Iterator pointing to the position where the element will be inserted.
                            //! @param val The value of the element to insert.
                            //! @return An iterator pointing to the first inserted element, or to the existing element if no insertion happens.

                                iterator insert(const_iterator position, value_type&& val);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Insert elements from an initializer list into the vector at a specified position.
                            //!
                            //! Inserts elements from the provided initializer list into the vector at the specified position, expanding the container if necessary. If the position is beyond the end of the vector, the behavior is undefined.
                            //!
                            //! @param position Iterator pointing to the position where the elements will be inserted.
                            //! @param il An initializer list containing elements to insert.
                            //! @return An iterator pointing to the first inserted element, or to the existing element if no insertion happens.
                                
                                iterator insert(const_iterator position, cpstd::initializer_list<T> il);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Insert elements from a range specified by iterators into the vector at a specified position.
                            //!
                            //! Inserts elements from the range [first, last) into the vector at the specified position, expanding the container if necessary. If the position is beyond the end of the vector, the behavior is undefined.
                            //!
                            //! @tparam InputIterator Type of the input iterators.
                            //! @param position Iterator pointing to the position where the elements will be inserted.
                            //! @param first Iterator pointing to the beginning of the range to insert.
                            //! @param last Iterator pointing to the end of the range to insert.
                            //! @return An iterator pointing to the first inserted element, or to the existing element if no insertion happens.
                                
                                template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>* = nullptr>  
                                iterator insert(const_iterator position, InputIterator first, InputIterator last);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // 
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // erase
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Deletes the element at the given index from the list, if index >= size the method does nothing.
                            //!
                            //! The element is destroyed and erased.
                            //! @tparam index The index of the element to be erased.

                                iterator erase(const_iterator position);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Erases the elements between both given indices
                            //!
                            //! The elements are destroyed and erased. The elemnts erased include (this*)[first] and (this*)[last]. If (last<=first) or (first>=size()) the method does nothing.
                            //! @tparam first The index of the first element to be erased.
                            //! @tparam last The index of the last element to be erased.

                                iterator erase(const_iterator first, const_iterator last);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Swaps the elements at index_a and index_b
                        //!
                        //! The element is constructed through std::allocator_traits::construct, which typically uses placement-new to construct the element in-place at a location provided by the container. However, if the required location has been occupied by an existing element, the inserted element is constructed at another location at first, and then move assigned into the required location.
                        //! The class used must implement the proper move semantics in order for this method to be able to call a move assignment operator.
                        //! @tparam index_a the value of the first element to swap.

                            void swap(vector<value_type, allocator_type>& x) noexcept;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Removes all elements from the vector (which are destroyed), leaving the container with a size and capacity of 0.
                        //!
                        //! if ( capacity > 0 ) A reallocation is guaranteed to happen, and the vector capacity is guaranteed to change due to calling this function.
                         
                            void clear() noexcept;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // emplace
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Construct and insert element
                            //!
                            //! Inserts a new element at the specified position.
                            //!
                            //! This function extends the container by constructing a new element in place at the specified position
                            //! using the provided arguments (args) for its construction.
                            //!
                            //! @tparam Args The types of arguments used for constructing the new element.
                            //! @param position Iterator pointing to the position where the new element will be inserted.
                            //! @param args Arguments forwarded for the construction of the new element.
                            //! 
                            //! This operation effectively increases the container size by one.
                            //!
                            //! Automatic reallocation of the allocated storage space occurs only if the new size surpasses the current capacity.
                            //!
                            //! Because vectors use an array as their underlying storage, inserting elements at positions other than the vector's end
                            //! causes all elements after the specified position to shift by one to their new positions. This can be less efficient compared
                            //! to operations performed by other sequence containers (e.g., list or forward_list). Consider using emplace_back for direct
                            //! extension at the end of the container.
                            //!
                            //! The element is constructed in-place by calling allocator_traits::construct with the forwarded args.
                            //!
                            //! Another related member function is insert, which either copies or moves existing objects into the container.
                            //!
                            //! @see emplace_back
                            //!
                            //! @param Position in the container where the new element is inserted.\n
                            //! Member type const_iterator is a random access iterator type that points to a const element.
                            //! @tparam args Arguments forwarded to construct the new element.
                            //! @return An iterator that points to the newly emplaced element.\n\n
                            //! Member type iterator is a random access iterator type that points to an element.\n\n
                            //! If a reallocation happens, the storage is allocated using the container's allocator, which may throw exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).

                                template <class... Args>
                                iterator emplace(const_iterator position, Args&&... args);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // emplace_back
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Construct and insert element at the end
                            //!
                            //! Inserts a new element at the end of the vector, right after its current last element.
                            //! This new element is constructed in place using args as the arguments for its constructor.
                            //!
                            //! This effectively increases the container size by one, which causes an automatic reallocation
                            //! of the allocated storage space if -and only if- the new vector size surpasses the current
                            //! vector capacity.
                            //!
                            //! The element is constructed in-place by calling allocator_traits::construct with args forwarded.
                            //!
                            //! A similar member function exists, push_back, which either copies or moves an existing object
                            //! into the container.
                            //!
                            //! @param args Arguments forwarded to construct the new element.
                            //! @return none.
                            //!
                            //! If a reallocation happens, the storage is allocated using the container's allocator, which
                            //! may throw exceptions on failure (for the default allocator, bad_alloc is thrown if the
                            //! allocation request does not succeed).
                                
                                template <class... Args>
                                void emplace_back(Args&&... args);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @}
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @name Non Member Functions
                    //! @{
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Relational Operators
                        
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Equal to.
                            //! Checks if both vectors are equal in size and contents.
                            //! It is important that the class T has defined == and != operators.
                            //! @tparam source Another container of the same type.
                             
                                friend bool operator== <T, Alloc>(const vector<value_type, allocator_type>& lhs, const vector<value_type, allocator_type>& rhs);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Not equal to.
                            //! Checks if both vectors are not equal in size or contents.
                            //! It is important that the class T has defined == and != operators.
                            //! @tparam source Another container of the same type.
                            
                                friend bool operator!= <T, Alloc>(const vector<value_type, allocator_type>& lhs, const vector<value_type, allocator_type>& rhs);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Less than.
                            //! Checks if the left vector is lexicographically less than the right vector.
                            //! It is important that the class T has defined < operator.
                            //! @tparam source Another container of the same type.
                            
                                friend bool operator< <T, Alloc>(const vector<value_type, allocator_type>& lhs, const vector<value_type, allocator_type>& rhs);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Less than or equal to.
                            //! Checks if the left vector is lexicographically less than or equal to the right vector.
                            //! It is important that the class T has defined < operator.
                            //! @tparam source Another container of the same type.
                            
                                friend bool operator<= <T, Alloc>(const vector<value_type, allocator_type>& lhs, const vector<value_type, allocator_type>& rhs);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Greater than.
                            //! Checks if the left vector is lexicographically greater than the right vector.
                            //! It is important that the class T has defined > operator.
                            //! @tparam source Another container of the same type.
                            
                                friend bool operator> <T, Alloc>(const vector<value_type, allocator_type>& lhs, const vector<value_type, allocator_type>& rhs);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            //! @brief Greater than or equal to.
                            //! Checks if the left vector is lexicographically greater than or equal to the right vector.
                            //! It is important that the class T has defined > operator.
                            //! @tparam source Another container of the same type.
                            
                                friend bool operator>= <T, Alloc>(const vector<value_type, allocator_type>& lhs, const vector<value_type, allocator_type>& rhs);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Swap contents.
                        //! Exchanges the contents of this vector with another vector.
                        //! This operation does not involve the allocation or deallocation of storage.
                        //! @tparam vector Another vector of the same type.
                        //! @param x Vector to swap with.
                            
                            friend void swap(vector<value_type, allocator_type>& x);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @}
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                };
            #endif    
        //!
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::swap(vector& , vector&) Specialization

            template <class T, class Alloc = cpstd::allocator<T>>
            void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) noexcept;
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    }   

    #include "CPSTL_Vector.tpp"

#endif//CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H