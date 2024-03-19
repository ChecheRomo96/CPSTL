#ifndef CPSTL_STRING_CLASS_H
#define CPSTL_STRING_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPtype_traits.h>
    #include <CPutility.h>
    #include <CPmemory.h>
    
    #if __has_include(<string>)
        #include <string>
    #endif

    #if __has_include(<ios>)
        #include <ios>
    #endif

    #include "CPSTL_char_traits.h"
 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // basic_string
        #include <CPios.h>

        namespace cpstd{ 
        #if defined(CPSTL_STRING_USING_STL_ALLOCATION)
            template < class charT, class traits = std::char_traits<charT>, class Alloc = std::allocator<charT> >
            using basic_string = std::basic_string< charT, traits, Alloc>;
        #else
            template< class charT, class traits = char_traits<charT>, class Alloc = allocator<charT>> 
            class basic_string{
            public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Typdefs and aliases
            
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Value Types

                    using traits_type = traits;
                    using allocator_type = Alloc;
                    using value_type = typename traits_type::char_type;
                    using reference = value_type&;
                    using const_reference = const value_type&;
                    using pointer = typename cpstd::allocator_traits<allocator_type>::pointer;
                    using const_pointer = typename cpstd::allocator_traits<allocator_type>::const_pointer;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Iterator Types
                
                    using iterator = charT*;
                    using const_iterator = const charT*;
                    using reverse_iterator = cpstd::reverse_iterator<iterator>;
                    using const_reverse_iterator = cpstd::reverse_iterator<const_iterator>;
                    using difference_type = cpstd::ptrdiff_t;
                    using size_type = cpstd::size_t;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //
            ////////////////////////////////////////////////////////////////////////////////////////////
            // Member Constants

                #if defined(CPSTL_STRING_USING_STL_ALLOCATION) || defined(CPSTL_USING_STL)
                    static constexpr size_type npos = std::string::npos;
                #else
                    static constexpr size_type npos = -1;
                #endif
            //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            protected:

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Protected Members
            
                #if defined(CPSTL_STRING_USING_C_ALLOCATION) || defined(CPSTL_STRING_USING_CPP_ALLOCATION)
                    size_type _size;
                    size_type _capacity;
                    value_type* _buffer;
                    Alloc _Alloc; // Instance of the custom allocator
                #endif
            //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            public:                    

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Constructors 
            
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Default 

                    basic_string();
                    explicit basic_string(const allocator_type& alloc);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Copy   

                    basic_string(const basic_string& str);
                    basic_string(const basic_string& str, const allocator_type& alloc);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // substring

                    basic_string(const basic_string& str, size_type pos, size_type len = npos, const allocator_type& alloc = allocator_type());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // from c-string

                    basic_string(const charT* s, const allocator_type& alloc = allocator_type());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // from buffer

                    basic_string(const charT* s, size_type n, const allocator_type& alloc = allocator_type());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // fill

                    basic_string(size_type n, charT c, const allocator_type& alloc = allocator_type());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // range

                    template <class InputIterator>
                    basic_string(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // initializer list

                    basic_string(initializer_list<charT> il, const allocator_type& alloc = allocator_type());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // move

                    basic_string(basic_string&& str) noexcept;
                    basic_string(basic_string&& str, const allocator_type& alloc);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // std::basic_string
                
                    #if __has_include(<string>)
                        basic_string(const std::basic_string<charT>& str, const allocator_type& alloc = allocator_type());
                    #endif
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @name Assignment Operator
            //! @{
                
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // basic_string

                    basic_string& operator=(const basic_string& str);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // c-string
                
                    basic_string& operator=(const charT* s);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // character
                
                    basic_string& operator=(charT c);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // initializer list    
                
                    basic_string& operator=(initializer_list<charT> il);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // move
                
                    basic_string& operator=(basic_string&& str) noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // std::basic_string

                    #if __has_include(<string>)
                        basic_string(const std::basic_string<charT, traits_type, allocator_type>& str, const allocator_type& alloc = allocator_type());
                    #endif
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @}
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @name Iterators
            //! @{
            
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return iterator to beginning
                //!
                //! This function returns an iterator pointing to the beginning of the string's elements.
                //!
                //! @return iterator - An iterator to the beginning of the string.

                    iterator begin() noexcept;
                    const_iterator begin() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return iterator to end
                //!
                //! This function returns an iterator pointing to the end of the string's elements.
                //!
                //! @return iterator - An iterator to the end of the string.

                    iterator end() noexcept;
                    const_iterator end() const noexcept;       
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return reverse iterator to reverse beginning
                //!
                //! This function returns a reverse iterator pointing to the beginning of the reversed string's elements.
                //!
                //! @return reverse_iterator - A reverse iterator to the beginning of the reversed string.

                    reverse_iterator rbegin() noexcept;
                    const_reverse_iterator rbegin() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return reverse iterator to reverse end
                //!
                //! This function returns a reverse iterator pointing to the end of the reversed string's elements.
                //!
                //! @return reverse_iterator - A reverse iterator to the end of the reversed string.

                    iterator rend() noexcept;
                    const_iterator rend() const noexcept; 
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return const_iterator to beginning
                //!
                //! This function returns a constant iterator pointing to the beginning of the string's elements.
                //!
                //! @return const_iterator - A constant iterator to the beginning of the string's elements.

                    const_iterator cbegin() const noexcept;                      
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return const_iterator to end
                //!
                //! This function returns a constant iterator pointing to the end of the string's elements.
                //!
                //! @return const_iterator - A constant iterator to the end of the string's elements.

                    const_iterator cend() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return const_reverse_iterator to reverse beginning
                //!
                //! This function returns a constant reverse iterator pointing to the beginning of the string's elements.
                //!
                //! @return const_reverse_iterator - A constant reverse iterator to the beginning of the string's elements.

                    const_reverse_iterator crbegin() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Return const_reverse_iterator to reverse end
                //!
                //! This function returns a constant reverse iterator pointing to the end of the string's elements.
                //!
                //! @return const_reverse_iterator - A constant reverse iterator to the end of the string's elements.

                    const_reverse_iterator crend() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @}
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @name Capacity
            //! @{
            
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Returns the number of elements in the string.
                //!
                //! This is the number of actual objects held in the string, which is not necessarily equal to its storage capacity.
                
                    size_type size() const noexcept;
                //!
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Returns the number of elements in the string.
                //!
                //! This function returns the number of actual objects held in the string, which is not necessarily equal to its storage capacity.
                //!
                //! @return The number of elements in the string.
                //!
                //! @note This function has constant complexity and does not modify the state of the string.
                //!
                    size_type length() const noexcept;
                //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Returns the number of elements in the string.
                //!
                //! This is the maximum potential length the string can reach due to known system or library implementation limitations, but the object is not guaranteed 
                //! to be able to reach that length: it can still fail to allocate storage at any point before that length is reached.
                //!
                //! @return The maximum length the basic_string can reach.
                //!
                //! @note This function has constant complexity and does not modify the state of the string.
                //!
                    size_type max_size() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Resizes the container to contain new_size elements, does nothing if new_size == size().
                //!
                //! If the current size is greater than new_size, the container is reduced to to fit new_size elements.\n
                //! If the current size is less than count and value parameter is unused, then additional default-inserted elements are appended.
                //! If the current size is less than count and value parameter is used, then additional copies of value are appended.
                //! @tparam new_size New size of the container.
                //! @tparam value The value to initialize the new elements with.
                 
                    void resize(size_type new_size, charT  c = charT());
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Returns the size of the storage space currently allocated for the string, expressed in terms of elements.
                //!
                //! This capacity is not necessarily equal to the string size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
                //! Notice that this capacity does not suppose a limit on the size of the string. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a string is given by member max_size.
                //! The capacity of a string can be explicitly altered by calling member string::reserve.
                
                    size_type capacity() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Increase the capacity of the string (the total number of elements that the string can hold without requiring reallocation) to a value that's greater or equal to capacity.
                //!
                //! If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.\n
                //! reserve() does not change the size of the string.\n
                //! If after the operation the new size() is greater than old capacity() a reallocation takes place, in which case all iterators (including the end() iterator) and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.\n
                //! After a call to reserve(), insertions will not trigger reallocation unless the insertion would make the size of the string greater than the value of capacity().\n
                //! If an allocation fails and exceptions are enabled (CPSTL_VECTOR_EXCEPTIONS_ENABLED), then the method throws a cpstd::bad_allocation exception.\n
                
                    void reserve(size_type new_cap);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Checks if the string is empty.
                //!
                //! This function determines whether the string contains any elements.
                //! @return true if the string is empty, false otherwise.

                    bool empty() const noexcept;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Clears the content of the string.
                //!
                //! This function removes all elements from the string, leaving it with a size of 0.
                //!
                //! @note This function has constant complexity and modifies the state of the string by removing all elements.
                //!
                    void clear() noexcept;
                //!
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Requests the container to reduce its capacity to fit its size.
                //!
                //! The request is non-binding, and the container implementation is free to optimize otherwise and leave the string with a capacity greater than its size.\n
                //! This may cause a reallocation, but has no effect on the string size and cannot alter its elements.                     
                 
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
                    //! Similar to the at() function, it might cause undefined behavior if the position is out of the string's size bounds.
                    //! @param position Position of the element to fetch.
                    
                        reference operator[](size_type position);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Const subscript array operator. This operator references the element at the specified position, providing read-only access.
                    //!
                    //! Similar to the at() function, it might cause undefined behavior if the position is out of the string's size bounds.
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
                    //! Returns a reference to the element at position n in the string.
                    //! The function automatically checks whether n is within the bounds of valid elements in the string, throwing an out_of_range exception if it 
                    //! is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
                    //! @tparam position Position of an element in the container.
                    //! If this is greater than, or equal to, the string size, an exception of type out_of_range is thrown.\n
                    //! Notice that the first element has a position of 0 (not 1).\n
                    //! Member type size_type is an unsigned integral type.\n
                    
                        reference at(size_type position);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Access element
                    //!
                    //! Returns a const_reference to the element at position n in the string.
                    //! The function automatically checks whether n is within the bounds of valid elements in the string, throwing an out_of_range exception if it 
                    //! is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
                    //! @tparam position Position of an element in the container.
                    //! If this is greater than, or equal to, the string size, an exception of type out_of_range is thrown.\n
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
                    //! Returns a reference to the first element in the string.\n
                    //! Unlike member string::begin, which returns an iterator to this same element, this function returns a direct reference.\n
                    //! Calling this function on an empty container causes undefined behavior.
                    
                        reference front();
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Access first element 
                    //!
                    //! Returns a const_reference to the first element in the string.\n
                    //! Unlike member string::begin, which returns an const_iterator to this same element, this function returns a direct const_reference.\n
                    //! Calling this function on an empty container causes undefined behavior.

                        const_reference front() const;
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // back
                
                     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Access last element 
                    //!
                    //! Returns a reference to the last element in the string.\n
                    //! Unlike member string::end, which returns an iterator to this same element, this function returns a direct reference.\n
                    //! Calling this function on an empty container causes undefined behavior.
                    
                        reference back();
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Access last element 
                    //!
                    //! Returns a const_reference to the last element in the string.\n
                    //! Unlike member string::end, which returns an const_iterator to this same element, this function returns a direct const_reference.\n
                    //! Calling this function on an empty container causes undefined behavior.

                        const_reference back() const;
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @}
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @name Modifiers
            //! @{
                
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // operator+=
                    
                    basic_string& operator+= (const basic_string& str);
                    basic_string& operator+= (const charT* s);
                    basic_string& operator+= (charT c);
                    basic_string& operator+= (initializer_list<charT> il);
                // 
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // append

                    basic_string& append (const basic_string& str);
                    basic_string& append (const basic_string& str, size_type subpos, size_type sublen = npos);
                    basic_string& append (const charT* s);
                    basic_string& append (const charT* s, size_type n);
                    basic_string& append (size_type n, charT c);
                    
                    template <class InputIterator>
                    basic_string& append (InputIterator first, InputIterator last);
                    
                    basic_string& append (initializer_list<charT> il);                
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Appends the given element value to the end of the container.
                //! @param value The value to be added at the end of the container.

                    void push_back(charT c);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // assign

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns the value of another string to this string.
                    //! @param str The string whose contents will be copied into this string.
                    //! @return A reference to this string after the assignment.
                    //!                        
                        basic_string& assign(const basic_string& str);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns a substring of another string to this string.
                    //! @param str    The string from which the substring will be assigned.
                    //! @param subpos The starting position of the substring in `str`.
                    //! @param sublen The length of the substring to assign.
                    //! @return A reference to this string after the assignment.
                    //!                       
                        basic_string& assign(const basic_string& str, size_type subpos, size_type sublen = npos);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns the value of a C-style string to this string.
                    //! @param s The C-style string whose contents will be copied into this string.
                    //! @return A reference to this string after the assignment.
                    //!                 
                        basic_string& assign(const charT* s);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns a substring of a C-style string to this string.
                    //! @param s The C-style string from which the substring will be assigned.
                    //! @param n The length of the substring to assign.
                    //! @return A reference to this string after the assignment.
                    //!              
                        basic_string& assign(const charT* s, size_type n);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns new contents to the container by initializing it with 'n' elements, each initialized to a copy of 'val'.
                    //! @param n   New size for the container.
                    //! @param val Value to fill the container with. Each of the 'n' elements in the container will be initialized to a copy of this value.
                        
                        basic_string& assign(size_type n, charT c);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns new contents to the string, replacing its current contents, and modifying its size accordingly.
                    //! @param n   New size for the container.
                    //! @param val Value to fill the container with. Each of the 'n' elements in the container will be initialized to a copy of this value.
                        
                        template <class Iterator, cpstd::enable_if_t<cpstd::is_pointer_v<Iterator>>* = nullptr>  
                        basic_string& assign(Iterator first, Iterator last);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns new contents to the container by replacing the existing contents with the elements from another container.
                    //! @param il Another container of the same type used to assign the new contents to this container.
                     
                        basic_string& assign(cpstd::initializer_list<charT> il);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Assigns new contents to the container by replacing the existing contents with the elements from another container.
                    //! @param il Another container of the same type used to assign the new contents to this container.
                     
                        basic_string& assign(basic_string&& str) noexcept;
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // insert
                    
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts the contents of another string into this string at the specified position.
                    //! @param pos The position at which to insert the contents of the other string.
                    //! @param str The string whose contents will be inserted.
                    //! @return A reference to this string after the insertion.
                    
                        basic_string& insert (size_type pos, const basic_string& str);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts a substring of another string into this string at the specified position.
                    //! @param pos    The position at which to insert the substring.
                    //! @param str    The string from which to extract the substring.
                    //! @param subpos The starting position of the substring in the other string.
                    //! @param sublen The length of the substring to insert.
                    //! @return A reference to this string after the insertion.
                    
                        basic_string& insert (size_type pos, const basic_string& str, size_type subpos, size_type sublen = npos);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts the contents of a C-style string into this string at the specified position.
                    //! @param pos The position at which to insert the C-style string.
                    //! @param s   The C-style string whose contents will be inserted.
                    //! @return A reference to this string after the insertion.
                    
                        basic_string& insert (size_type pos, const charT* s);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts a substring of a C-style string into this string at the specified position.
                    //! @param pos The position at which to insert the substring.
                    //! @param s   The C-style string from which to extract the substring.
                    //! @param n   The length of the substring to insert.
                    //! @return A reference to this string after the insertion.
                    
                        basic_string& insert (size_type pos, const charT* s, size_type n);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts multiple copies of a character into this string at the specified position.
                    //! @param pos The position at which to insert the characters.
                    //! @param n   The number of characters to insert.
                    //! @param c   The character to insert.
                    //! @return A reference to this string after the insertion.
                    
                        basic_string& insert (size_type pos,   size_type n, charT c);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    //! @brief Inserts multiple copies of a character into this string before the character pointed by the iterator.
                    //! @param p The iterator pointing to the character before which to insert the characters.
                    //! @param n The number of characters to insert.
                    //! @param c The character to insert.
                    //! @return An iterator pointing to the first inserted character.
                    
                        iterator insert (const_iterator p, size_type n, charT c);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts a character into this string before the character pointed by the iterator.
                    //! @param p The iterator pointing to the character before which to insert the character.
                    //! @param c The character to insert.
                    //! @return An iterator pointing to the inserted character.
                    
                        iterator insert (const_iterator p, charT c);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts elements from a range into this string before the character pointed by the iterator.
                    //! @param p     The iterator pointing to the character before which to insert the elements.
                    //! @param first Iterator to the beginning of the range of elements to insert.
                    //! @param last  Iterator to the end of the range of elements to insert.
                    //! @return An iterator pointing to the first inserted element.
                    
                        template <class InputIterator>     iterator insert (iterator p, InputIterator first, InputIterator last);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Inserts elements from an initializer list into this string before the character pointed by the iterator.
                    //! @param p  The iterator pointing to the character before which to insert the elements.
                    //! @param il The initializer list containing the elements to insert.
                    //! @return A reference to this string after the insertion.
                    
                        basic_string& insert (const_iterator p, initializer_list<charT> il);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // 
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // erase
                
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Erases characters from the string.
                    //! @param pos The position of the first character to erase.
                    //! @param len The number of characters to erase.
                    //! @return A reference to this string after the erasure.
                    
                        basic_string& erase(size_type pos = 0, size_type len = npos);
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Erases a character from the string at the specified position.
                    //! @param position The iterator pointing to the character to erase.
                    //! @return An iterator pointing to the character following the erased character.
                    
                        iterator erase(const_iterator position);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Erases characters from the string in the range specified by the iterators.
                    //! @param first The iterator pointing to the first character to erase.
                    //! @param last  The iterator pointing to the character following the last character to erase.
                    //! @return An iterator pointing to the character following the last erased character.
                    
                        iterator erase(const_iterator first, const_iterator last);
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // 
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // replace
                    
                    basic_string& replace (size_type pos, size_type len, const basic_string& str);
                    basic_string& replace (const_iterator i1, const_iterator i2, const basic_string& str);
                    basic_string& replace (size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen = npos);
                    basic_string& replace (size_type pos, size_type len, const charT* s);
                    basic_string& replace (const_iterator i1, const_iterator i2, const charT* s);
                    basic_string& replace (size_type pos, size_type len, const charT* s, size_type n);
                    basic_string& replace (const_iterator i1, const_iterator i2, const charT* s, size_type n);
                    basic_string& replace (size_type pos, size_type len, size_type n, charT c);
                    basic_string& replace (const_iterator i1, const_iterator i2, size_type n, charT c);
                    
                    template <class InputIterator>  basic_string& replace (const_iterator i1, const_iterator i2, InputIterator first, InputIterator last);
                    basic_string& replace (const_iterator i1, const_iterator i2, initializer_list<charT> il);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // swap
                    
                    void swap (basic_string& str);
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @brief Delete the last elemnt
                //! @tparam value The value of the element to append.
                //! @return Returns the poped value
                    
                    void pop_back();
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @}
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //! @name String operations
            //! @{
                    const charT* c_str() const noexcept;
                    
                    const charT* data() const noexcept;

                    operator std::basic_string<charT, std::char_traits<charT>, std::allocator<charT>>() const;

                    allocator_type get_allocator() const noexcept;

                    size_type copy (charT* s, size_type len, size_type pos = 0) const;

                    size_type find (const basic_string& str, size_type pos = 0) const noexcept;
                    size_type find (const charT* s, size_type pos = 0) const;
                    size_type find (const charT* s, size_type pos, size_type n) const;
                    size_type find (charT c, size_type pos = 0) const noexcept;

                    size_type rfind (const basic_string& str, size_type pos = npos) const noexcept;
                    size_type rfind (const charT* s, size_type pos = npos) const;
                    size_type rfind (const charT* s, size_type pos, size_type n) const;
                    size_type rfind (charT c, size_type pos = npos) const noexcept;

                    size_type find_first_of (const basic_string& str, size_type pos = 0) const noexcept;
                    size_type find_first_of (const charT* s, size_type pos = 0) const;
                    size_type find_first_of (const charT* s, size_type pos, size_type n) const;
                    size_type find_first_of (charT c, size_type pos = 0) const noexcept;

                    size_type find_last_of (const basic_string& str, size_type pos = npos) const noexcept;
                    size_type find_last_of (const charT* s, size_type pos = npos) const;
                    size_type find_last_of (const charT* s, size_type pos, size_type n) const;
                    size_type find_last_of (charT c, size_type pos = npos) const noexcept;

                    size_type find_first_not_of (const basic_string& str, size_type pos = 0) const noexcept;
                    size_type find_first_not_of (const charT* s, size_type pos = 0) const;
                    size_type find_first_not_of (const charT* s, size_type pos, size_type n) const;
                    size_type find_first_not_of (charT c, size_type pos = 0) const noexcept;

                    size_type find_last_not_of (const basic_string& str, size_type pos = npos) const noexcept;
                    size_type find_last_not_of (const charT* s, size_type pos = npos) const;
                    size_type find_last_not_of (const charT* s, size_type pos, size_type n) const;
                    size_type find_last_not_of (charT c, size_type pos = npos) const noexcept;

                    basic_string substr (size_type pos = 0, size_type len = npos) const;

                    int compare (const basic_string& str) const noexcept;
                    int compare (size_type pos, size_type len, const basic_string& str) const;
                    int compare (size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen = npos) const;
                    int compare (const charT* s) const;
                    int compare (size_type pos, size_type len, const charT* s) const;
                    int compare (size_type pos, size_type len, const charT* s, size_type n) const;
            //! @}
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
            };
        #endif
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Non-member functions overload

        namespace cpstd{ 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // operator+

            template <class charT, class traits, class Alloc>
            basic_string<charT,traits,Alloc> operator+(const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT,traits,Alloc>&& lhs, basic_string<charT,traits,Alloc>&& rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT,traits,Alloc>&& lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT,traits,Alloc>& lhs, basic_string<charT,traits,Alloc>&& rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT,traits,Alloc>&& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const charT* lhs, const basic_string<charT,traits,Alloc>&  rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const charT* lhs, basic_string<charT,traits,Alloc>&& rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT,traits,Alloc>& lhs, charT rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT,traits,Alloc>&& lhs, charT rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(charT lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(charT lhs, basic_string<charT,traits,Alloc>&& rhs);
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // relational operators
            
            template <class charT, class traits, class Alloc>  
            bool operator==(const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs) noexcept;

            template <class charT, class traits, class Alloc>  
            bool operator==(const charT* lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            bool operator==(const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>  
            bool operator!=(const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs) noexcept;

            template <class charT, class traits, class Alloc>  
            bool operator!=(const charT* lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            bool operator!=(const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>  
            bool operator< (const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs) noexcept;

            template <class charT, class traits, class Alloc>  
            bool operator< (const charT* lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            bool operator< (const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>  
            bool operator<=(const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs) noexcept;

            template <class charT, class traits, class Alloc>  
            bool operator<=(const charT* lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            bool operator<=(const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>  
            bool operator> (const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs) noexcept;

            template <class charT, class traits, class Alloc>  
            bool operator> (const charT* lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            bool operator> (const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);

            template <class charT, class traits, class Alloc>  
            bool operator>=(const basic_string<charT,traits,Alloc>& lhs, const basic_string<charT,traits,Alloc>& rhs) noexcept;

            template <class charT, class traits, class Alloc>  
            bool operator>=(const charT* lhs, const basic_string<charT,traits,Alloc>& rhs);

            template <class charT, class traits, class Alloc>
            bool operator>=(const basic_string<charT,traits,Alloc>& lhs, const charT* rhs);
        // 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // swap
        
            template <class charT, class traits, class Alloc>
            void swap (basic_string<charT,traits,Alloc>& a, basic_string<charT,traits,Alloc>& b) noexcept;
        // 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // operator>> (cpstd::basic_istream) and operator << (cpstd::basic_ostream)
        
            //template <class charT, class traits, class Alloc>  
            //basic_istream<charT,traits>& operator>>(basic_istream<charT,traits>& is, basic_string<charT,traits,Alloc>& str);
        
            //template <class charT, class traits, class Alloc>
            //cpstd::basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>& os, const basic_string<charT,traits,Alloc>& str);
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // operator>> (std::basic_istream) and operator << (std::basic_ostream)

            #if __has_include(<ios>)
            template <class charT, class traits, class Alloc>
            std::basic_istream<charT, std::char_traits<charT>>& operator>>(std::basic_istream<charT, std::char_traits<charT>>& is, cpstd::basic_string<charT, traits, Alloc>& str);
            
            template <class charT, class traits, class Alloc>
            std::basic_ostream<charT, std::char_traits<charT>>& operator<<(std::basic_ostream<charT, std::char_traits<charT>>& os, const cpstd::basic_string<charT, traits, Alloc>& str);
            #endif
        //            
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // getline
            /*
            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>& is, basic_string<charT,traits,Alloc>& str, charT delim);

            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>&& is, basic_string<charT,traits,Alloc>& str, charT delim);

            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>& is, basic_string<charT,traits,Alloc>& str);

            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>&& is, basic_string<charT,traits,Alloc>& str);
            */
        // 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // getline
            #if __has_include(<ios>)
            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>& is, basic_string<charT,traits,Alloc>& str, charT delim);

            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>&& is, basic_string<charT,traits,Alloc>& str, charT delim);

            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>& is, basic_string<charT,traits,Alloc>& str);

            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>&& is, basic_string<charT,traits,Alloc>& str);
            #endif
        // 
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Template Specializations

        namespace cpstd{ 
            using string    = cpstd::basic_string<char>;
            using wstring   = cpstd::basic_string<wchar_t>;
            using u16string = cpstd::basic_string<char16_t>;
            using u32string = cpstd::basic_string<char32_t>;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    #include "CPSTL_String.tpp"
    
#endif//CPSTL_STRING_CLASS_H
