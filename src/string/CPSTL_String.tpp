#include "CPSTL_String.h"

namespace cpstd {
#ifndef CPSTL_USING_STL

    //////////////////////////////////////////////////////////////////////////////////////////////
    // basic_string


        //////////////////////////////////////////////////////////////////////////////////////////
        // Constructors 
        
            //////////////////////////////////////////////////////////////////////////////////////
            // Default 

                template< class charT, class traits, class Alloc> 
                basic_string<charT, traits, Alloc>::basic_string()
                : _size(0), _capacity(0), _buffer(nullptr), _Alloc() {
                    _buffer = _Alloc.allocate(1); // Allocate memory for one character
                    _buffer[0] = '\0';
                }

                template< class charT, class traits, class Alloc> 
                basic_string<charT, traits, Alloc>::basic_string(const allocator_type& alloc)
                : _size(0), _capacity(0), _buffer(nullptr), _Alloc(alloc) {
                    _buffer = _Alloc.allocate(1); // Allocate memory for one character
                    _buffer[0] = '\0';
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Copy

                template< class charT, class traits, class Alloc> 
                basic_string<charT, traits, Alloc>::basic_string(const basic_string& str)
                : basic_string(){
                    assign(str);
                }
                
                template< class charT, class traits, class Alloc> 
                basic_string<charT, traits, Alloc>::basic_string(const basic_string& str, const allocator_type& alloc)
                : basic_string(alloc){
                    assign(str);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // substring

                template< class charT, class traits, class Alloc> 
                basic_string<charT, traits, Alloc>::basic_string(const basic_string& str, size_type pos, size_type len, const allocator_type& alloc)
                : basic_string(alloc){
                    assign(str, pos, len);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // from c-string

                template< class charT, class traits, class Alloc> 
                basic_string<charT, traits, Alloc>::basic_string(const charT* s, const allocator_type& alloc)
                : basic_string(alloc){
                    assign(s);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // From buffer

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>::basic_string(const charT* s, size_type n, const allocator_type& alloc)
                    : basic_string(alloc) {
                    assign(s, n);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Fill

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>::basic_string(size_type n, charT c, const allocator_type& alloc)
                    : basic_string(alloc) {
                    assign(n, c);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Range

                template <class charT, class traits, class Alloc>
                template <class InputIterator>
                basic_string<charT, traits, Alloc>::basic_string(InputIterator first, InputIterator last, const allocator_type& alloc)
                    : basic_string(alloc) {
                    assign(first, last);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Initializer list

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>::basic_string(initializer_list<charT> il, const allocator_type& alloc)
                    : basic_string(alloc) {
                    assign(il);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Move constructors

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>::basic_string(basic_string&& str) noexcept
                    : _size(0), _capacity(0), _buffer(nullptr), _Alloc(std::move(str._Alloc)) {
                    swap(str);
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>::basic_string(basic_string&& str, const allocator_type& alloc)
                    : basic_string(alloc) {
                    assign(std::move(str));
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // std::basic_string

                #if __has_include(<string>)
                template <class charT, class traits, class Alloc>                
                basic_string<charT, traits, Alloc>::basic_string(const std::basic_string<charT>& str, const allocator_type& alloc)
                    : basic_string(alloc) {
                    resize(str.size());

                    for (size_type i = 0; i < size(); i++) {
                        (*this)[i] = str[i];
                    }
                }
                #endif
            //
            //////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // Assignment Operator
        
            //////////////////////////////////////////////////////////////////////////////////////
            // basic_string

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator=(const basic_string& str) {
                    if (this != &str) {
                        assign(str);
                    }
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // c-string
            
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator=(const charT* s) {
                    assign(s);
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // character
            
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator=(charT c) {
                    assign(1, c);
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // initializer list    
            
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator=(initializer_list<charT> il) {
                    assign(il);
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // move
            
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator=(basic_string&& str) noexcept {
                    if (this != &str) {
                        // Deallocate existing buffer if it's not empty
                        if (_buffer) {
                            _Alloc.deallocate(_buffer, _capacity+1);
                        }

                        // Transfer resources from the source to the destination
                        _size = str._size;
                        _capacity = str._capacity;
                        _buffer = str._buffer;
                        _Alloc = cpstd::move(str._Alloc);

                        // Reset the source object
                        str._size = 0;
                        str._capacity = 0;
                        str._buffer = nullptr;
                    }
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // std::basic_string
            
                #ifdef CPSTL_USING_STL
                template<class charT, class traits, class Allocator>
                basic_string<charT, traits, Allocator>& basic_string<charT, traits, Allocator>::operator=(const std::basic_string<charT, traits, Allocator>& str) {
                    assign(str);
                    return *this;
                }
                #endif
            //
            //////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // Iterators

            //////////////////////////////////////////////////////////////////////////////////////
            // begin

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::begin() noexcept {
                    return _buffer;
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_iterator basic_string<charT, traits, Alloc>::begin() const noexcept {
                    return _buffer;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // end

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::end() noexcept {
                    return _buffer + _size;
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_iterator basic_string<charT, traits, Alloc>::end() const noexcept {
                    return _buffer + _size;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // rbegin

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::reverse_iterator basic_string<charT, traits, Alloc>::rbegin() noexcept {
                    return reverse_iterator(end());
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reverse_iterator basic_string<charT, traits, Alloc>::rbegin() const noexcept {
                    return const_reverse_iterator(end());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // rend

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::rend() noexcept {
                    return iterator(begin());
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_iterator basic_string<charT, traits, Alloc>::rend() const noexcept {
                    return const_iterator(begin());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // cbegin

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_iterator basic_string<charT, traits, Alloc>::cbegin() const noexcept {
                    return const_iterator(begin());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // cend

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_iterator basic_string<charT, traits, Alloc>::cend() const noexcept {
                    return const_iterator(_buffer + _size);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // crbegin

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reverse_iterator basic_string<charT, traits, Alloc>::crbegin() const noexcept {
                    return const_reverse_iterator(end());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // crend

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reverse_iterator basic_string<charT, traits, Alloc>::crend() const noexcept {
                    return const_reverse_iterator(begin());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // Capacity
        
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // size
                
                    template<class charT, class traits, class Allocator>
                    typename basic_string<charT, traits, Allocator>::size_type basic_string<charT, traits, Allocator>::size() const noexcept {
                        return _size;
                    }
                //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // length

                    template<class charT, class traits, class Allocator>
                    typename basic_string<charT, traits, Allocator>::size_type basic_string<charT, traits, Allocator>::length() const noexcept {
                        return traits::length(_buffer);
                    }
                //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // max_size

                    template <class charT, class traits, class Alloc>
                    typename basic_string<charT, traits, Alloc>::size_type
                    basic_string<charT, traits, Alloc>::max_size() const noexcept {
                        return _Alloc.max_size();
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // resize

                    template <class charT, class traits, class Alloc>
                    void basic_string<charT, traits, Alloc>::resize(size_type new_size, charT c) {
                        if (new_size < _size) {
                            _size = new_size;
                            if (_buffer) {
                                _buffer[_size] = charT(); // Null-terminate the string
                            }
                        } else if (new_size > _size) {
                            reserve(new_size);
                            for (size_type i = _size; i < new_size; ++i) {
                                _buffer[i] = c;
                            }
                            _size = new_size;
                            _buffer[_size] = charT(); // Null-terminate the string
                        }
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // capacity
                
                    template <class charT, class traits, class Alloc>
                    typename basic_string<charT, traits, Alloc>::size_type
                    basic_string<charT, traits, Alloc>::capacity() const noexcept {
                        return _capacity;
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // reserve
                
                    template <class charT, class traits, class Alloc>
                    void basic_string<charT, traits, Alloc>::reserve(size_type new_capacity) {
                        if (new_capacity > _capacity) {
                            // Allocate a new buffer with the requested capacity
                            pointer new_buffer = _Alloc.allocate(new_capacity+1);

                            // Copy existing elements to the new buffer
                            traits::copy(new_buffer, _buffer, _size); // +1 to include the null terminator

                            new_buffer[_size] = charT();

                            // Deallocate the old buffer
                            _Alloc.deallocate(_buffer, _capacity);

                            // Update internal state
                            _buffer = new_buffer;
                            _capacity = new_capacity;
                        }
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // empty

                    template <class charT, class traits, class Alloc>
                    bool basic_string<charT, traits, Alloc>::empty() const noexcept {
                        return _size == 0;
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // clear
                
                    template <class charT, class traits, class Alloc>
                    void basic_string<charT, traits, Alloc>::clear() noexcept {
                        _size = 0;
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // shrink_to_fit
                
                    template <class charT, class traits, class Alloc>
                    void basic_string<charT, traits, Alloc>::shrink_to_fit() {
                        if (_size < _capacity) {
                        // Allocate a new buffer with exact size needed
                        value_type* new_buffer = _Alloc.allocate(_size + 1); // Add 1 for null terminator
                        // Copy the content
                        traits::copy(new_buffer, _buffer, _size);
                        // Null-terminate the new buffer
                        new_buffer[_size] = value_type(); // Null terminator
                        // Deallocate the old buffer
                        _Alloc.deallocate(_buffer, _capacity);
                        // Update members
                        _buffer = new_buffer;
                        _capacity = _size;
                    }
                    }
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // Element Access
            
            //////////////////////////////////////////////////////////////////////////////////////
            // Subscript Array Operators

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::reference basic_string<charT, traits, Alloc>::operator[](size_type position) {
                    return _buffer[position];
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reference basic_string<charT, traits, Alloc>::operator[](size_type position) const {
                    return _buffer[position];
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // at
                
                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::reference basic_string<charT, traits, Alloc>::at(size_type position) {
                    if (position >= _size) {
                        throw std::out_of_range("basic_string::at");
                    }
                    return _buffer[position];
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reference basic_string<charT, traits, Alloc>::at(size_type position) const {
                    if (position >= _size) {
                        throw std::out_of_range("basic_string::at");
                    }
                    return _buffer[position];
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // front

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::reference basic_string<charT, traits, Alloc>::front() {
                    return *begin();
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reference basic_string<charT, traits, Alloc>::front() const {
                    return *cbegin();
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
            // back

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::reference basic_string<charT, traits, Alloc>::back() {
                    return *(end() - 1);
                }

                template <class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::const_reference basic_string<charT, traits, Alloc>::back() const {
                    return *(cend() - 1);
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // Modifiers

            //////////////////////////////////////////////////////////////////////////////////////
            // operator+=
                
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator+=(const basic_string& str) {
                    append(str);
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator+=(const charT* s) {
                    append(s);
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator+=(charT c) {
                    push_back(c);
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::operator+=(initializer_list<charT> il) {
                    append(il);
                    return *this;
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
            // append
                
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(const basic_string& str) {
                    return append(str.data(), str.size());
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(const basic_string& str, size_type subpos, size_type sublen) {
                    sublen = cpstd::min(sublen, str.size() - subpos);
                    return append(str.data() + subpos, sublen);
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(const charT* s) {
                    return append(s, traits::length(s));
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(const charT* s, size_type n) {
                    const size_type new_size = _size + n;
                    if (new_size > _capacity) {
                        reserve(new_size);
                    }
                    traits::copy(_buffer + _size, s, n);
                    _size = new_size;
                    _buffer[_size] = charT();
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(size_type n, charT c) {
                    const size_type new_size = _size + n;
                    if (new_size > _capacity) {
                        reserve(new_size);
                    }
                    traits::assign(_buffer + _size, n, c);
                    _size = new_size;
                    _buffer[_size] = charT();
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                template <class InputIterator>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(InputIterator first, InputIterator last) {
                    const size_type count = std::distance(first, last);
                    const size_type new_size = _size + count;
                    if (new_size > _capacity) {
                        reserve(new_size);
                    }
                    for (; first != last; ++first) {
                        _buffer[_size++] = *first;
                    }
                    _buffer[_size] = charT();
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::append(initializer_list<charT> il) {
                    return append(il.begin(), il.end());
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
            // push_back
                
                template <class charT, class traits, class Alloc>
                void basic_string<charT, traits, Alloc>::push_back(charT c) {
                    const size_type new_size = _size + 1;
                    if (new_size > _capacity) {
                        reserve(new_size);
                    }
                    _buffer[_size++] = c;
                    _buffer[_size] = charT();
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
            // assign
                
                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(const basic_string& str) {
                    resize(str._size);
                    return replace(0, _size, str);
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(const basic_string& str, size_type subpos, size_type sublen) {
                    return replace(0, _size, str, subpos, sublen);
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(const charT* s) {
                    size_type len = traits::length(s);
                    resize(len);
                    traits::copy(_buffer, s, len);
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(const charT* s, size_type n) {
                    resize(n);
                    traits::copy(_buffer, s, n);
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(size_type n, charT c) {
                    resize(n);
                    traits::assign(_buffer, n, c);
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(initializer_list<charT> il) {
                    clear();
                    insert(begin(), il.begin(), il.end());
                    return *this;
                }

                template <class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::assign(basic_string&& str) noexcept {
                    swap(str);
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // insert
                
                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::insert(size_type pos, const basic_string& str) {
                    return insert(pos, str, 0, str.size());
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::insert(size_type pos, const basic_string& str, size_type subpos, size_type sublen) {
                    if (subpos > str.size()) {
                        throw std::out_of_range("basic_string::insert");
                    }
                    return insert(pos, str.data() + subpos, std::min(sublen, str.size() - subpos));
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::insert(size_type pos, const charT* s) {
                    return insert(pos, s, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::insert(size_type pos, const charT* s, size_type n) {
                    if (pos > size()) {
                        throw std::out_of_range("basic_string::insert");
                    }
                    resize(size() + n);
                    traits::move(_buffer + pos + n, _buffer + pos, size() - pos);
                    traits::copy(_buffer + pos, s, n);
                    _size += n;
                    return *this;
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::insert(size_type pos, size_type n, charT c) {
                    if (pos > size()) {
                        throw std::out_of_range("basic_string::insert");
                    }
                    resize(size() + n);
                    traits::move(_buffer + pos + n, _buffer + pos, size() - pos);
                    traits::assign(_buffer + pos, n, c);
                    _size += n;
                    return *this;
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::insert(const_iterator p, size_type n, charT c) {
                    size_type pos = p - _buffer;
                    insert(pos, n, c);
                    return iterator(_buffer + pos);
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::insert(const_iterator p, charT c) {
                    size_type pos = p - _buffer;
                    insert(pos, 1, c);
                    return iterator(_buffer + pos);
                }

                template<class charT, class traits, class Alloc>
                template<class InputIterator>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::insert(iterator p, InputIterator first, InputIterator last) {
                    size_type pos = p - _buffer;
                    size_type len = cpstd::distance(first, last);
                    if (pos > size()) {
                        throw std::out_of_range("basic_string::insert");
                    }
                    if (size() + len > capacity()) {
                        reserve(size() + len);
                    }
                    traits::move(_buffer + pos + len, _buffer + pos, size() - pos);
                    traits::copy(_buffer + pos, first, len);
                    _size += len;
                    (*this)[_size] = charT();
                    return iterator(_buffer + pos);
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::insert(const_iterator p, initializer_list<charT> il) {
                    size_type pos = p - _buffer;
                    insert(pos, il.begin(), il.size());
                    return *this;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // erase
                
                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::erase(size_type pos, size_type len) {
                    if (pos >= size()) {
                        throw std::out_of_range("basic_string::erase");
                    }
                    len = cpstd::min(len, size() - pos);
                    traits::move(_buffer + pos, _buffer + pos + len, size() - pos - len);
                    _size -= len;
                    (*this)[_size] = charT();
                    return *this;
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::erase(const_iterator position) {
                    size_type pos = position - _buffer;
                    if (pos >= size()) {
                        throw std::out_of_range("basic_string::erase");
                    }
                    traits::move(_buffer + pos, _buffer + pos + 1, size() - pos - 1);
                    --_size;
                    return iterator(_buffer + pos);
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::iterator basic_string<charT, traits, Alloc>::erase(const_iterator first, const_iterator last) {
                    size_type startPos = first - _buffer;
                    size_type endPos = last - _buffer;
                    if (startPos >= size() || endPos > size() || startPos >= endPos) {
                        throw std::out_of_range("basic_string::erase");
                    }
                    traits::move(_buffer + startPos, _buffer + endPos, size() - endPos);
                    _size -= (endPos - startPos);
                    return iterator(_buffer + startPos);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // replace
            
                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(size_type pos, size_type len, const basic_string& str) {
                    return replace(begin() + pos, begin() + pos + len, str.begin(), str.end());
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(const_iterator i1, const_iterator i2, const basic_string& str) {
                    return replace(i1 - begin(), i2 - i1, str);
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen) {
                    return replace(begin() + pos, begin() + pos + len, str.begin() + subpos, str.begin() + subpos + std::min(sublen, str.size() - subpos));
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(size_type pos, size_type len, const charT* s) {
                    return replace(begin() + pos, begin() + pos + len, s, s + traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(const_iterator i1, const_iterator i2, const charT* s) {
                    return replace(i1, i2, s, s + traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(size_type pos, size_type len, const charT* s, size_type n) {
                    return replace(begin() + pos, begin() + pos + len, s, s + n);
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(const_iterator i1, const_iterator i2, const charT* s, size_type n) {
                    return replace(i1 - begin(), i2 - i1, s, s + n);
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(size_type pos, size_type len, size_type n, charT c) {
                    return replace(begin() + pos, begin() + pos + len, n, c);
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(const_iterator i1, const_iterator i2, size_type n, charT c) {
                    size_type startPos = i1 - begin();
                    size_type endPos = i2 - begin();
                    erase(startPos, endPos - startPos);
                    insert(startPos, n, c);
                    return *this;
                }

                template<class charT, class traits, class Alloc>
                template<class InputIterator>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(const_iterator i1, const_iterator i2, InputIterator first, InputIterator last) {
                    // Calculate the position indices from iterators
                    size_type pos = i1 - _buffer;
                    size_type len = i2 - i1;

                    // Calculate the length of the replacement sequence
                    size_type replace_len = cpstd::distance(first, last);

                    // Calculate the new size after replacement
                    size_type new_size = size() - len + replace_len;

                    // Ensure capacity for the new string size
                    if (new_size > capacity()) {
                        resize(new_size);
                    }

                    // Move the elements after the replaced sequence
                    traits::move(_buffer + pos + replace_len, _buffer + pos + len, size() - pos - len);

                    // Copy the replacement sequence into the buffer
                    traits::copy(_buffer + pos, first, replace_len);

                    // Update the size of the string
                    _size = new_size;
                    (*this)[_size] = charT();

                    return *this;
                }

                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>& basic_string<charT, traits, Alloc>::replace(const_iterator i1, const_iterator i2, initializer_list<charT> il) {
                    return replace(i1 - begin(), i2 - i1, il.begin(), il.end());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // swap

                template<class charT, class traits, class Alloc>
                void basic_string<charT, traits, Alloc>::swap(basic_string& str) {
                    if (this != &str) {
                        cpstd::swap(_size, str._size);
                        cpstd::swap(_capacity, str._capacity);
                        cpstd::swap(_buffer, str._buffer);
                        cpstd::swap(_Alloc, str._Alloc);
                    }
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
            // pop_back

                template<class charT, class traits, class Alloc>
                void basic_string<charT, traits, Alloc>::pop_back() {
                    if (_size > 0) {
                        _size--;
                        _buffer[_size] = charT(); // Null-terminate the string
                    }
                }
            // 
            //////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // String operations

            //////////////////////////////////////////////////////////////////////////////////////
            // c_str
            
                template<class charT, class traits, class Alloc>
                const charT* basic_string<charT, traits, Alloc>::c_str() const noexcept {
                    // Ensure null-termination
                    if (_size == 0) {
                        static const charT emptyString[] = { charT('\0') };
                        return emptyString;
                    } else {
                        // Return pointer to the beginning of the internal buffer
                        return _buffer;
                    }
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // data
                
                template<class charT, class traits, class Alloc>
                const charT* basic_string<charT, traits, Alloc>::data() const noexcept {
                    // Return pointer to the beginning of the internal buffer
                    return _buffer;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // std::basic_string cast operator
                
                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc>::operator std::basic_string<charT, std::char_traits<charT>, std::allocator<charT>>() const {
                    return std::basic_string<charT>(_buffer, _size); // Convert cpstd::basic_string to std::string
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // get_allocator
                
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::allocator_type basic_string<charT, traits, Alloc>::get_allocator() const noexcept {
                    // Return a copy of the allocator
                    return _Alloc;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // copy
                
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::copy(charT* s, size_type len, size_type pos) const {
                    // Check if pos is within bounds
                    if (pos > size()) {
                        throw std::out_of_range("basic_string::copy");
                    }
                    
                    // Determine the actual number of characters to copy
                    size_type count = std::min(len, size() - pos);
                    
                    // Copy characters from the string to the given character array
                    traits::copy(s, _buffer + pos, count);
                    
                    return count;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // find
                
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find(const basic_string& str, size_type pos) const noexcept {
                    return find(str.data(), pos, str.size());
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find(const charT* s, size_type pos) const {
                    return find(s, pos, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find(const charT* s, size_type pos, size_type n) const {
                    if (pos > _size || n == 0) {
                        return npos; // Return npos if pos is out of range or n is 0
                    }

                    const charT* substr = _buffer + pos; // Pointer to the start of the substring to search

                    for (size_type i = pos; i <= _size - n; ++i, ++substr) {
                        if (traits::compare(substr, s, n) == 0) {
                            return i; // Return the position of the first occurrence of the substring
                        }
                    }

                    return npos; // Return npos if the substring is not found
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find(charT c, size_type pos) const noexcept {
                    if (pos >= size()) {
                        return npos;  // Not found if starting position is beyond or equal to string size
                    }
                    
                    const charT* result = traits::find(_buffer + pos, size() - pos, c);
                    return result != nullptr ? result - _buffer : npos;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // rfind
                
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::rfind(const basic_string& str, size_type pos) const noexcept {
                    return rfind(str.data(), pos, str.size());
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::rfind(const charT* s, size_type pos) const {
                    return rfind(s, pos, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::rfind(const charT* s, size_type pos, size_type n) const {
                    if (size() < n) {
                        return npos;  // Not found if string size is less than the substring size
                    }
                    
                    pos = std::min(pos, size() - n);  // Adjust starting position
                    
                    for (size_type i = pos; i != npos; --i) {
                        if (traits::compare(_buffer + i, s, n) == 0) {
                            return i;  // Found the substring, return its index
                        }
                    }
                    
                    return npos;  // Substring not found
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::rfind(charT c, size_type pos) const noexcept {
                    if (pos == npos) {
                        pos = size();
                    }
                    
                    for (size_type i = std::min(pos, size()); i != npos; --i) {
                        if (traits::eq(_buffer[i], c)) {
                            return i;  // Found the character, return its index
                        }
                    }
                    
                    return npos;  // Character not found
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // find_first_of
                
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_of(const basic_string& str, size_type pos) const noexcept {
                    if (pos >= size()) {
                        return npos; // Return npos if pos is greater than or equal to the size of the string
                    }
                    return find_first_of(str.data(), pos, str.size());
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_of(const charT* s, size_type pos) const {
                    return find_first_of(s, pos, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_of(const charT* s, size_type pos, size_type n) const {
                    for (; pos < size(); ++pos) {
                        if (traits::find(s, n, _buffer[pos]) != nullptr) {
                            return pos;
                        }
                    }
                    return npos;
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_of(charT c, size_type pos) const noexcept {
                    return find(c, pos);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // find_last_of
            
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_of(const basic_string& str, size_type pos) const noexcept {
                    return find_last_of(str.data(), pos, str.size());
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_of(const charT* s, size_type pos) const {
                    return find_last_of(s, pos, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_of(const charT* s, size_type pos, size_type n) const {
                    if (size() == 0) return npos;
                    pos = std::min(pos, size() - 1);
                    for (; pos != npos; --pos) {
                        if (traits::find(s, n, _buffer[pos]) != nullptr) {
                            return pos;
                        }
                    }
                    return npos;
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_of(charT c, size_type pos) const noexcept {
                    return rfind(c, pos);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // find_first_not_of

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_not_of(const basic_string& str, size_type pos) const noexcept {
                    return find_first_not_of(str.data(), pos, str.size());
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_not_of(const charT* s, size_type pos) const {
                    return find_first_not_of(s, pos, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_not_of(const charT* s, size_type pos, size_type n) const {
                    if (pos >= size()) return npos;
                    for (; pos < size(); ++pos) {
                        if (traits::find(s, n, _buffer[pos]) == nullptr) {
                            return pos;
                        }
                    }
                    return npos;
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_first_not_of(charT c, size_type pos) const noexcept {
                    return find_first_not_of(&c, pos, 1);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // find_last_not_of
            
                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_not_of(const basic_string& str, size_type pos) const noexcept {
                    return find_last_not_of(str.data(), pos, str.size());
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_not_of(const charT* s, size_type pos) const {
                    return find_last_not_of(s, pos, traits::length(s));
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_not_of(const charT* s, size_type pos, size_type n) const {
                    if (size() == 0) return npos;
                    if (pos >= size()) pos = size() - 1;
                    for (; pos != npos; --pos) {
                        if (traits::find(s, n, _buffer[pos]) == nullptr) {
                            return pos;
                        }
                    }
                    return npos;
                }

                template<class charT, class traits, class Alloc>
                typename basic_string<charT, traits, Alloc>::size_type basic_string<charT, traits, Alloc>::find_last_not_of(charT c, size_type pos) const noexcept {
                    return find_last_not_of(&c, pos, 1);
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // substr
                
                template<class charT, class traits, class Alloc>
                basic_string<charT, traits, Alloc> basic_string<charT, traits, Alloc>::substr(size_type pos, size_type len) const {
                    if (pos > size()) pos = size();
                    if (len == npos || pos + len > size()) len = size() - pos;
                    return basic_string(_buffer + pos, len, get_allocator());
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // compare
            
                template<class charT, class traits, class Alloc>
                int basic_string<charT, traits, Alloc>::compare(const basic_string& str) const noexcept {
                    return compare(0, size(), str);
                }

                template<class charT, class traits, class Alloc>
                int basic_string<charT, traits, Alloc>::compare(size_type pos, size_type len, const basic_string& str) const {
                    return compare(pos, len, str.data(), str.size());
                }

                template<class charT, class traits, class Alloc>
                int basic_string<charT, traits, Alloc>::compare(size_type pos1, size_type len1, const basic_string& str, size_type pos2, size_type len2) const {
                    return compare(pos1, len1, str.data() + pos2, len2);
                }

                template<class charT, class traits, class Alloc>
                int basic_string<charT, traits, Alloc>::compare(const charT* s) const {
                    return compare(0, size(), s);
                }

                template<class charT, class traits, class Alloc>
                int basic_string<charT, traits, Alloc>::compare(size_type pos, size_type len, const charT* s) const {
                    size_type rlen = traits::length(s);
                    if (pos > size()) pos = size();
                    if (len == npos || pos + len > size()) len = size() - pos;
                    len = std::min(len, rlen);
                    int cmp = traits::compare(_buffer + pos, s, len);
                    if (cmp == 0 && len < rlen) cmp = -1;
                    return cmp;
                }

                template<class charT, class traits, class Alloc>
                int basic_string<charT, traits, Alloc>::compare(size_type pos, size_type len, const charT* s, size_type n) const {
                    size_type rlen = traits::length(s);
                    if (pos > size()) pos = size();
                    if (len == npos || pos + len > size()) len = size() - pos;
                    len = std::min(len, n);
                    int cmp = traits::compare(_buffer + pos, s, len);
                    if (cmp == 0 && len < rlen) cmp = -1;
                    return cmp;
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////////////////////////
    // Non-member functions overload

        //////////////////////////////////////////////////////////////////////////////////////////
        // operator+

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT, traits, Alloc>& lhs, const basic_string<charT, traits, Alloc>& rhs) {
                basic_string<charT, traits, Alloc> result = lhs;
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT, traits, Alloc>&& lhs, basic_string<charT, traits, Alloc>&& rhs) {
                basic_string<charT, traits, Alloc> result = std::move(lhs);
                result += std::move(rhs);
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT, traits, Alloc>&& lhs, const basic_string<charT, traits, Alloc>& rhs) {
                basic_string<charT, traits, Alloc> result = std::move(lhs);
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT, traits, Alloc>& lhs, basic_string<charT, traits, Alloc>&& rhs) {
                basic_string<charT, traits, Alloc> result = lhs;
                result += std::move(rhs);
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                basic_string<charT, traits, Alloc> result = lhs;
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT, traits, Alloc>&& lhs, const charT* rhs) {
                basic_string<charT, traits, Alloc> result = std::move(lhs);
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const charT* lhs, const basic_string<charT, traits, Alloc>& rhs) {
                basic_string<charT, traits, Alloc> result = lhs;
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const charT* lhs, basic_string<charT, traits, Alloc>&& rhs) {
                basic_string<charT, traits, Alloc> result = lhs;
                result += std::move(rhs);
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(const basic_string<charT, traits, Alloc>& lhs, charT rhs) {
                basic_string<charT, traits, Alloc> result = lhs;
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(basic_string<charT, traits, Alloc>&& lhs, charT rhs) {
                basic_string<charT, traits, Alloc> result = std::move(lhs);
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(charT lhs, const basic_string<charT, traits, Alloc>& rhs) {
                basic_string<charT, traits, Alloc> result(1, lhs);
                result += rhs;
                return result;
            }

            template <class charT, class traits, class Alloc>
            basic_string<charT, traits, Alloc> operator+(charT lhs, basic_string<charT, traits, Alloc>&& rhs) {
                basic_string<charT, traits, Alloc> result(1, lhs);
                result += std::move(rhs);
                return result;
            }        
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // relational operators
            
            template <class charT, class traits, class Alloc>
            bool operator==(const cpstd::basic_string<charT, traits, Alloc>& lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) noexcept {
                return lhs.compare(rhs) == 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator==(const charT* lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) {
                return rhs.compare(lhs) == 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator==(const cpstd::basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                return lhs.compare(rhs) == 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator!=(const cpstd::basic_string<charT, traits, Alloc>& lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) noexcept {
                return lhs.compare(rhs) != 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator!=(const charT* lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) {
                return rhs.compare(lhs) != 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator!=(const cpstd::basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                return lhs.compare(rhs) != 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator<(const cpstd::basic_string<charT, traits, Alloc>& lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) noexcept {
                return lhs.compare(rhs) < 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator<(const charT* lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) {
                return rhs.compare(lhs) > 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator<(const cpstd::basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                return lhs.compare(rhs) < 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator<=(const cpstd::basic_string<charT, traits, Alloc>& lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) noexcept {
                return lhs.compare(rhs) <= 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator<=(const charT* lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) {
                return rhs.compare(lhs) >= 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator<=(const cpstd::basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                return lhs.compare(rhs) <= 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator>(const cpstd::basic_string<charT, traits, Alloc>& lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) noexcept {
                return lhs.compare(rhs) > 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator>(const charT* lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) {
                return rhs.compare(lhs) < 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator>(const cpstd::basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                return lhs.compare(rhs) > 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator>=(const cpstd::basic_string<charT, traits, Alloc>& lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) noexcept {
                return lhs.compare(rhs) >= 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator>=(const charT* lhs, const cpstd::basic_string<charT, traits, Alloc>& rhs) {
                return rhs.compare(lhs) <= 0;
            }

            template <class charT, class traits, class Alloc>
            bool operator>=(const cpstd::basic_string<charT, traits, Alloc>& lhs, const charT* rhs) {
                return lhs.compare(rhs) >= 0;
            }
        // 
        //////////////////////////////////////////////////////////////////////////////////////////
        // swap
        
            template <class charT, class traits, class Alloc>
            void swap(basic_string<charT, traits, Alloc>& a, basic_string<charT, traits, Alloc>& b) noexcept
            {
                a.swap(b);
            }

        // 
        //////////////////////////////////////////////////////////////////////////////////////////
        // operator>> (cpstd::basic_istream) and operator << (cpstd::basic_ostream)
         
            /*template <class charT, class traits, class Alloc>  
            basic_istream<charT, traits>& operator>>(basic_istream<charT, traits>& is, basic_string<charT, traits, Alloc>& str) {

            }*/
        
            //template <class charT, class traits, class Alloc>
            //basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>& os, const basic_string<charT,traits,Alloc>& str);
        // 
        //////////////////////////////////////////////////////////////////////////////////////////
        // operator>> (std::basic_istream) and operator << (std::basic_ostream)
         
            #if __has_include(<ios>)
            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT, std::char_traits<charT>>& operator>>(std::basic_istream<charT, std::char_traits<charT>>& is, cpstd::basic_string<charT, traits, Alloc>& str) {
                charT ch;
                str.clear(); // Clear the existing content of the string

                // Read characters from the input stream until whitespace is encountered
                while (is.get(ch) && !traits::eq(ch, is.widen(' ')) && !traits::eq(ch, is.widen('\n')) && !traits::eq(ch, is.widen('\t'))) {
                    str.push_back(ch);
                }

                // If reading stopped due to whitespace or newline, put the character back into the stream
                if (is) {
                    is.putback(ch);
                }

                return is;
            }

            template <class charT, class traits, class Alloc>
            std::basic_ostream<charT, std::char_traits<charT>>& operator<<(std::basic_ostream<charT, std::char_traits<charT>>& os, const cpstd::basic_string<charT, traits, Alloc>& str){
                for (const auto& ch : str) {
                    os.put(ch);
                }
                return os;
            }
            #endif
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        // getline (cpstd::basic_istream) 
        /*
            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>& is, basic_string<charT,traits,Alloc>& str, charT delim) {
                str.clear(); // Clear the existing content of the string

                charT ch;
                while (is.get(ch) && ch != delim) {
                    str.push_back(ch);
                }

                // If the delimiter was encountered, consume it but do not add it to the string
                if (ch == delim) {
                    is.get();
                }

                return is;
            }

            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>&& is, basic_string<charT,traits,Alloc>& str, charT delim) {
                return getline(is, str, delim);
            }

            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>& is, basic_string<charT,traits,Alloc>& str) {
                return getline(is, str, is.widen('\n')); // Use newline character as default delimiter
            }

            template <class charT, class traits, class Alloc>  
            basic_istream<charT,traits>& getline(basic_istream<charT,traits>&& is, basic_string<charT,traits,Alloc>& str) {
                return getline(is, str, is.widen('\n')); // Use newline character as default delimiter
            } */
        // 
        //////////////////////////////////////////////////////////////////////////////////////////
        // getline (std::basic_istream) 
        
            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>& is, basic_string<charT,traits,Alloc>& str, charT delim) {
                str.clear(); // Clear the existing content of the string

                charT ch;
                while (is.get(ch) && ch != delim) {
                    str.push_back(ch);
                }

                // If the delimiter was encountered, consume it but do not add it to the string
                if (ch == delim) {
                    is.get();
                }

                return is;
            }

            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>&& is, basic_string<charT,traits,Alloc>& str, charT delim) {
                return getline(is, str, delim);
            }

            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>& is, basic_string<charT,traits,Alloc>& str) {
                return getline(is, str, is.widen('\n')); // Use newline character as default delimiter
            }

            template <class charT, class traits, class Alloc>  
            std::basic_istream<charT,std::char_traits<charT>>& getline(std::basic_istream<charT,std::char_traits<charT>>&& is, basic_string<charT,traits,Alloc>& str) {
                return getline(is, str, is.widen('\n')); // Use newline character as default delimiter
            } 
        // 
        //////////////////////////////////////////////////////////////////////////////////////////   
    //
    //////////////////////////////////////////////////////////////////////////////////////////////

#endif
}
