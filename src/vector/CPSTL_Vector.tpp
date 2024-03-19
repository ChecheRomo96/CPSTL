#include "CPSTL_Vector.h"

namespace cpstd{
#ifndef CPSTL_USING_STL_ALLOCATION
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // iterators

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // begin

            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() noexcept{
                return iterator(_Buffer);
            }


            template <class T, class Alloc>
            typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const noexcept{
                return const_iterator(_Buffer);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // end 
        
            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::end() noexcept{
                return iterator(_Buffer + _Size);
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const noexcept{
                return const_iterator(_Buffer + _Size);

            }   
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // rbegin 

            template <class T, class Alloc>
            typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() noexcept{
                return reverse_iterator(_Buffer + _Size);
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const noexcept{
                return const_reverse_iterator(_Buffer + _Size);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // rend 
        
            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::rend() noexcept{
                return iterator(_Buffer);
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_iterator vector<T, Alloc>::rend() const noexcept{
                return const_iterator(_Buffer);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // cbegin 
        
            template <class T, class Alloc>
            typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin() const noexcept{
                return const_iterator(_Buffer);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // cend
         
            template <class T, class Alloc>
            typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend() const noexcept{
                return const_iterator(_Buffer + _Size);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // crbegin
        
            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crbegin() const noexcept{
                return const_reverse_iterator(_Buffer + _Size);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // crend
        
            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crend() const noexcept{
                return const_reverse_iterator(_Buffer);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors, Destructor, and Assignment Operator
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
            
            template <class T, class Alloc>
            vector<T, Alloc>::vector() {
                _Buffer = nullptr;
                _Size = 0;
                _Capacity = 0;
            }   
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Fill constructor
            
            template <class T, class Alloc>
            vector<T, Alloc>::vector(size_type n, const allocator_type& alloc) : vector(){

                resize(n);
            }
            
            template <class T, class Alloc>
            vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) : vector(){

                resize(n, val);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // range constructor
        
            template <class T, class Alloc>
            template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>*>  
            vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc) : vector(){
                _Alloc = alloc;
                assign(first, last);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Range constructor
        
            template <class T, class Alloc>
            vector<T, Alloc>::vector(const vector<value_type, allocator_type>& other) : vector(){
                resize(other.size());
                for (size_type i = 0; i < size(); ++i) {
                    _Alloc.construct(&_Buffer[i], other[i]);
                }
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy constructor
        
            template <class T, class Alloc>
            vector<T, Alloc>::vector(const vector& x, const allocator_type& alloc) : vector() {
                _Alloc = alloc;
                resize(x.size());
                cpstd::uninitialized_copy(x._Buffer, x._Buffer + x._Size, _Buffer);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Move constructor
        
            template <class T, class Alloc>
            vector<T, Alloc>::vector(vector<value_type, allocator_type>&& source) noexcept: vector(){
                cpstd::swap(_Buffer, source._Buffer);
                cpstd::swap(_Size, source._Size);
                cpstd::swap(_Capacity, source._Capacity);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::initializer list constructor
        
            template <class T, class Alloc>
            vector<T, Alloc>::vector(cpstd::initializer_list<T> list): vector(){
                resize(list.size());
                auto it = begin();
                for (const auto& item : list) {
                    *it = item;
                    ++it;
                }
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Destructor
        
            template <class T, class Alloc>
            vector<T, Alloc>::~vector(){
                if (_Buffer) {
                    for (size_type i = 0; i < _Size; ++i) {
                        _Alloc.destroy(&_Buffer[i]);  // Call the destructor for each element
                    }
                    _Alloc.deallocate(_Buffer, _Capacity);  // Deallocate the memory
                }
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // Assignment Operators
    // 
    
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Assignment operator
            
            template <class T, class Alloc>
            vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& source){
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
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Move Assignment operator
            
            template <class T, class Alloc>
            vector<T, Alloc>& vector<T, Alloc>::operator=(vector<T, Alloc>&& source) noexcept{
                if (this != &source) {
                    cpstd::swap(_Buffer, source._Buffer);
                    cpstd::swap(_Size, source._Size);
                    cpstd::swap(_Capacity, source._Capacity);
                }
                return *this;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Move Assignment operator
            
            template <class T, class Alloc>
            vector<T, Alloc>& vector<T, Alloc>::operator=(cpstd::initializer_list<T> il) { 
                resize(il.size());
                auto it = begin();
                for (const auto& item : il) {
                    *it = item;
                    ++it;
                }
                return *this;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // Capacity
    // 
    
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // size
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const noexcept{
                return _Size;
            }  
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // resize
            
            template <class T, class Alloc>
            void vector<T, Alloc>::resize(size_type new_size, const_reference value){
                if (new_size < _Size) {
                    // Destruct elements if resizing to a smaller size
                    for (size_type i = new_size; i < _Size; ++i) {
                        _Alloc.destroy(&_Buffer[i]);
                    }
                } else if (new_size > _Size) {
                    if (new_size > _Capacity) {
                        // Reallocate memory if necessary
                        size_type new_capacity = new_size * 2;  // Or any suitable strategy
                        T* new_buffer = _Alloc.allocate(new_capacity);
                        
                        for (size_type i = 0; i < _Size; ++i) {
                            _Alloc.construct(&new_buffer[i], cpstd::move(_Buffer[i])); // Move old elements to the new memory
                            _Alloc.destroy(&_Buffer[i]);  // Destroy the old elements
                        }
                        _Alloc.deallocate(_Buffer, _Capacity);  // Deallocate the old memory
                        _Buffer = new_buffer;
                        _Capacity = new_capacity;
                    }
                    // Initialize new elements if resizing to a larger size
                    for (size_type i = _Size; i < new_size; ++i) {
                        _Alloc.construct(&_Buffer[i]);
                    }
                }
                _Size = new_size;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // capacity
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const noexcept{
                return _Capacity;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // empty
            
            template <class T, class Alloc>
            bool vector<T, Alloc>::empty() const {
                return (_Size == 0) ? true : false;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // reserve
            
            template <class T, class Alloc>
            void vector<T, Alloc>::reserve(size_type new_cap){
                if (new_cap > _Capacity) {
                    // Reallocate memory if necessary
                    pointer new_buffer = _Alloc.allocate(new_cap);
                    for (size_type i = 0; i < _Size; ++i) {
                        _Alloc.construct(&new_buffer[i], cpstd::move(_Buffer[i]));  // Move old elements to the new memory
                        _Alloc.destroy(&_Buffer[i]);  // Destroy the old elements
                    }
                    _Alloc.deallocate(_Buffer, _Capacity);  // Deallocate the old memory
                    _Buffer = new_buffer;
                    _Capacity = new_cap;
                }
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // capacity
            
            template <class T, class Alloc>
            void vector<T, Alloc>::shrink_to_fit(){
                if (_Capacity > _Size) {
                    pointer newBuffer = _Alloc.allocate(_Size);
                    if (newBuffer) {
                        cpstd::uninitialized_move(_Buffer, _Buffer + _Size, newBuffer);
                        for (size_type i = 0; i < _Size; ++i) {
                            _Buffer[i].~T();
                        }
                        _Alloc.deallocate(_Buffer, _Capacity);
                        _Buffer = newBuffer;
                        _Capacity = _Size;
                    }
                }
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // Element Access
    
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Subscript Array Operators
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type position) {
                return _Buffer[position];
            }


            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type position) const {
                return _Buffer[position];
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // at
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type position) {
            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                if(position >= _Size){
                    throw cpstd::out_of_range("Index requested on subscript array does not exists");
                }
            #endif
                
                return _Buffer[position];
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type position) const {
            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                if(position >= _Size){
                    throw cpstd::out_of_range("Index requested on subscript array does not exists");
                }
            #endif

            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                 return _Buffer[position];
            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                return _Vector.at();
            #endif
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // front
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
                return _Buffer[0];
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
                return _Buffer[0];
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // back

            template <class T, class Alloc>
            typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
                return _Buffer[_Size-1];
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
                return _Buffer[_Size-1];
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // data

            template <class T, class Alloc>
            typename vector<T, Alloc>::pointer vector<T, Alloc>::data() noexcept{
                return _Buffer;
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::const_pointer vector<T, Alloc>::data() const noexcept{
                return _Buffer;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // Modifiers
    
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // assign
            
            template <class T, class Alloc>
            template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>*>  
            void vector<T, Alloc>::assign (InputIterator first, InputIterator last){
                resize(cpstd::distance(first, last));
                cpstd::copy(first, last, _Buffer);
            }

            template <class T, class Alloc>
            void vector<T, Alloc>::assign(size_type n, const value_type& val) {
                resize(n);
                for (size_type i = 0; i < size(); i++) {
                    _Buffer[i] = val;
                }
            }

            template <class T, class Alloc>
            void vector<T, Alloc>::assign(cpstd::initializer_list<T> il) {
                resize(il.size());
                size_type i = 0;
                for (const auto& elem : il) {
                    _Buffer[i++] = elem;
                }
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // push_back
            
            template <class T, class Alloc>
            void vector<T, Alloc>::push_back(const_reference value){
                resize(size() + 1);
                _Buffer[_Size-1] = value;
            }

            template <class T, class Alloc>
            void vector<T, Alloc>::push_back(value_type&& Rvalue){
                resize(size() + 1);
                _Buffer[_Size-1] = cpstd::move(Rvalue);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // pop_back
            
            template <class T, class Alloc>
            void vector<T, Alloc>::pop_back(){
            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                if (size() == 0) {
                    throw cpstd::out_of_range("Index requested on subscript array does not exist");
                }
            #endif

                resize(size() - 1);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // insert
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, const value_type& val) {
                size_type index = position - _Buffer;
                resize(size() + 1);

                for (size_type i = _Size - 1; i > index; --i) {
                    _Buffer[i] = cpstd::move(_Buffer[i - 1]);
                }

                _Buffer[index] = val;

                return _Buffer + index;
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, size_type n, const value_type& val){
                size_type index = position - _Buffer;
                resize(_Size + n);

                for (size_type i = _Size - 1; i >= index + n; --i) {
                    _Buffer[i] = cpstd::move(_Buffer[i - n]);
                }

                for (size_type i = index; i < index + n; ++i) {
                    _Buffer[i] = val;
                }

                return _Buffer + index;
            }

            template <class T, class Alloc>
            template <class InputIterator, cpstd::enable_if_t<cpstd::is_pointer_v<InputIterator>>*>  
            typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, InputIterator first, InputIterator last){
                resize(cpstd::distance(first, last));

                for (size_t i = 0; first != last; ++first, ++i) {
                    _Buffer[i] = *first;
                }
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, value_type&& val){
                size_type index = position - _Buffer;
                resize(size() + 1);

                for (size_type i = _Size - 1; i > index; --i) {
                    _Buffer[i] = cpstd::move(_Buffer[i - 1]);
                }

                _Buffer[index] = cpstd::move(val);
                
                return _Buffer + index;
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator position, cpstd::initializer_list<T> il){
                size_type index = position - _Buffer;
                resize(size() + il.size());

                // Shift elements to make space for the new ones
                for (size_type i = size() - 1; i >= index + il.size(); --i) {
                    _Buffer[i] = cpstd::move(_Buffer[i - il.size()]);
                }

                // Copy elements from the initializer_list
                size_type i = index;
                for (const auto& elem : il) {
                    _Buffer[i++] = elem;
                }

                return _Buffer + index; 
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // erase
            
            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(const_iterator position){
                size_t index = position - begin();

                if (index < _Size) {
                    for (size_t i = index; i < _Size - 1; i++) {
                        _Buffer[i] = cpstd::move(_Buffer[i + 1]);
                    }
                    resize(size() - 1);
                }

                return begin() + index;
            }

            template <class T, class Alloc>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(const_iterator first, const_iterator last) {
                const_iterator beginIt = begin();  // iterator to the beginning of the container
                const_iterator endIt = end();      // iterator to the end of the container

                if (first >= last) {
                    return end();  // Return iterator to the end as an indication of an error or no change
                }

                auto range = cpstd::min(last, endIt) - first;

                // Move elements to fill the erased range
                for (auto it = first; it + range < endIt; ++it) {
                    *const_cast<T*>(it) = cpstd::move(*(it + range));
                }

                // Resize the container
                resize(size() - range);

                return (iterator)beginIt + static_cast<size_type>(cpstd::distance(beginIt, first));
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // swap
            
            template <class T, class Alloc>
            void vector<T, Alloc>::swap(vector<value_type, allocator_type>& x) noexcept {
                cpstd::swap(_Size, x._Size);
                cpstd::swap(_Capacity, x._Capacity);
                cpstd::swap(_Buffer, x._Buffer);
                cpstd::swap(_Alloc, x._Alloc);
            }
        // 
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // clear
            
            template <class T, class Alloc>
            void vector<T, Alloc>::clear() noexcept{
                for (size_type i = 0; i < _Size; ++i) {
                    _Alloc.destroy(_Buffer + i);
                }
                _Size = 0;
            } 
        // 
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // emplace
            
            template <class T, class Alloc>
            template <class... Args>
            typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(const_iterator position, Args&&... args) {
                // Convert the const_iterator to an iterator using const_cast
                auto pos = begin() + cpstd::distance(cbegin(), position);

                // Resize the vector to accommodate the new element
                size_type index = pos - _Buffer;
                resize(_Size + 1);

                // Shift elements to make space for the new one
                for (size_type i = _Size - 1; i > index; --i) {
                    _Buffer[i] = cpstd::move(_Buffer[i - 1]);
                }

                // Construct the new element in place at the specified position
                _Alloc.construct(_Buffer + index, cpstd::forward<Args>(args)...);

                return _Buffer + index;
            }
        // 
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // emplace_back
            
            template <class T, class Alloc>
            template <class... Args>
            void vector<T, Alloc>::emplace_back(Args&&... args) {
                if (_Size == _Capacity) {
                    // If the vector is full, reallocate the buffer to accommodate the new element
                    reserve(_Size == 0 ? 1 : 2 * _Size);
                }

                // Construct the new element in place at the end of the vector
                _Alloc.construct(_Buffer + _Size, cpstd::forward<Args>(args)...);

                // Increment the size
                ++_Size;
            }
        // 
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
    // Non Member Functions
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Relational Operators

            template <class T, class Alloc>
            bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
                if( lhs.size() == rhs.size() ){
                    for(typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++){
                        if(lhs[i] != rhs[i]){
                            return false;
                        }
                    }
                }
                else {
                    return false;
                }
                return true;
            }

            template <class T, class Alloc>
            bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
                return !(lhs == rhs);
            }

            template <class T, class Alloc>
            bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
                typename vector<T, Alloc>::size_type last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                for(typename vector<T, Alloc>::size_type i = 0; i < last; i++){
                    if(lhs[i] < rhs[i]){return 1;}
                }

                if(lhs.size() < rhs.size()){return 1;}
                return 0;
            }

            template <class T, class Alloc>
            bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
                typename vector<T, Alloc>::size_type last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                for (typename vector<T, Alloc>::size_type i = 0; i < last; i++) {
                    if (lhs[i] < rhs[i]) { return 1; }
                }

                if (lhs.size() <= rhs.size()) { return 1; }
                return 0;
            }

            template <class T, class Alloc>
            bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
                typename vector<T, Alloc>::size_type last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                for(typename vector<T, Alloc>::size_type i = 0; i < last; i++){
                    if(lhs[i] > rhs[i]){return 1;}
                }

                if(lhs.size() > rhs.size()){return 1;}
                return 0;
            }

            template <class T, class Alloc>
            bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
                typename vector<T, Alloc>::size_type last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                for (typename vector<T, Alloc>::size_type i = 0; i < last; i++) {
                    if (lhs[i] > rhs[i]) { return 1; }
                }

                if (lhs.size() >= rhs.size()) { return 1; }
                return 0;
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // swap

            template <class T, class Alloc>
            void swap(vector<T, Alloc>& x){
                swap(x);
            } 

            template <class T, class Alloc>
            void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) noexcept{
                lhs.swap(rhs);
            }
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
#endif
}
