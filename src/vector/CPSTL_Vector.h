#ifndef CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H
#define CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H

    #include <CPSTL_BuildSettings.h>
    #include <utility/CPSTL_Move.h>
    #include <CPinitializer_list>

    #if defined CPSTL_USING_STL
        #include <iostream>
    #endif

    #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
        #include "CPVector_Exceptions.h"
    #endif


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
    
        namespace cpstd {


            template <class T>
            class  vector;

            template <class T>
            void swap(cpstd::vector<T>& lhs, cpstd::vector<T>& rhs);

            template <class T>
            class  vector{
            protected:

                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Instance Variables

                    #if defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                        size_t _Size;
                        size_t _Capacity;
                        T * _Buffer;
                    #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                        size_t _Size;
                        size_t _Capacity;
                        T * _Buffer;
                    #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                        std::vector < T > _Vector;
                    #endif
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:
                    
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Constructors, Destructor, and Assignment Operator
                //! @{
                    
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Default constructor
                    //!
                    //! Initializes the vector to have size() = 0, the Capacity value is undefined, it's value is only bigger than size at all times. In order to reduce 
                    //! the capacity of the vector see shrink_to_fit() or clear().
                    
                        vector() {
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                            _Buffer = NULL;
                            _Size = 0;
                            _Capacity = 0;
                        #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            _Buffer = nullptr;
                            _Size = 0;
                            _Capacity = 0;
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.resize(0);
                            shrink_to_fit();
                        #endif
                        }     
                    //!
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Resize constructor. 
                    //!
                    //! Resizes the container to contain count elements, does nothing if count == 0.\n\n
                    //! If value parameter is not given additional default-inserted elements are appended\n 
                    //! If value parameter is given additional copies of value are appended.\n
                    //! @tparam count New size of the conatainer
                    //! @tparam value The value to initialize the elements with

                        vector(unsigned int count, const T& value = T()) : vector(){

                            resize(count, value);
                        }
                    //!
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Copy constructor.
                    //!
                    //! Constructs the container with the copy of the contents of other
                    //! @tparam other another container to be used as source to initialize the elements of the container with
                    
                        vector(const vector<T>& other) : vector(){

                            resize(other.size());
                            
                            for(unsigned int i = 0; i < size(); i++)
                            {
                                (*this)[i] = other[i];
                            }
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Copy constructor.
                    //!
                    //! Constructs the container with the copy of the contents of an array of objects of type T.
                    //! @tparam pointer location of the data to copy
                    //! @tparam len number of elements to copy

                        vector(const T* pointer, unsigned int len): vector(){

                            resize(len);
                            
                            for(unsigned int i = 0; i < size(); i++)
                            {
                                (*this)[i] = pointer[i];
                            }
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Move constructor. 
                    //!
                    //! Constructs the container with the copy of the contents of other
                    //! @tparam pointer location of the data to copy
                    //! @tparam len number of elements to copy
                    
                        vector(vector<T>&& source) noexcept: vector(){
                            clear();

                        #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector = std::move(source._Vector); //Moving an object
                        #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) | defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                            _Buffer = source._Buffer;   // Copying the pointer to the buffer allocated by source
                            _Size = source._Size;
                            _Capacity = source._Capacity;

                            source._Size = 0;
                            source._Capacity = 0;

                            #if defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            source._Buffer = nullptr;
                            #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                            source._Buffer = NULL;
                            #endif
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Move constructor. 
                    //!
                    //! Constructs the container with the copy of the contents of other
                    //! @tparam pointer location of the data to copy
                    //! @tparam len number of elements to copy
                        
                        #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            vector(std::vector<T>&& source) noexcept: vector(){
                                clear();
                                _Vector = std::move(source);
                            }
                        #endif
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief cpstd::initializer list constructor. 
                    //!
                    //! Constructs the container with an initializer list
                    //! @tparam list std::initializer list with matching template argument
                    //
                        vector(cpstd::initializer_list<T> list): vector(){
                        #ifdef CPSTL_VECTOR_USING_STD_ALLOCATION 
                            resize(list.size());
                            std::copy(list.begin(), list.end(), _Vector.begin());
                        #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) || defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                            resize(list.size());
                            for (size_t i = 0; i < size(); i++) {
                                (*this)[i] = *(list.begin() + i);
                            }
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Destructor. 
                    //!
                    //! Destroys all the elements amd changes the size and capacity to 0. (Releases the used memory)
                    
                        ~vector(){
                            clear();
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Assignment Operators

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Assignment operator.
                        //! 
                        //! This operator is used to assign new contents to the container by replacing the existing contents.
                        //! @tparam source Another container of the same type.
                        
                            vector& operator=(const vector& source){
                                if(this == &source){return *this;}
                                
                                if(resize(source.size())){
                                    for(unsigned int i = 0; i < size(); i++){
                                        (*this)[i] = source[i];
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
                         
                            vector& operator=(vector&& source){

                                if(this == &source){return *this;}
                                clear();

                            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector = std::move(source._Vector); //Moving an object
                            #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) | defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                                _Buffer = source._Buffer;   // Copying the pointer to the buffer allocated by source
                                _Size = source._Size;
                                _Capacity = source._Capacity;

                                source._Size = 0;
                                source._Capacity = 0;

                                #if defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                source._Buffer = nullptr;
                                #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                                source._Buffer = NULL;
                                #endif
                            #endif

                                return *this;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief cpstd::initializer list constructor
                        //!
                        //! Constructs the container with an initializer list
                        //! @tparam list std::initializer list with matching template argument
                        //
                            vector& operator=(cpstd::initializer_list<T> il) { 
                            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector = il;
                            #else
                                resize(il.size());
                                for(size_t i = 0; i < size(); i++){
                                    (*this)[i] = *(il.begin()+i);
                                }
                            #endif
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
                    
                        size_t size() const noexcept{
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            return _Size;
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            return _Vector.size();
                        #endif
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
                     
                        bool resize(size_t new_size, const T& value = T()){

                            if(size() == new_size){return 1;}
                            
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            
                            if(new_size == 0){ clear(); return 1;}
                            if(new_size > _Capacity)
                            { 
                                
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{
                            #endif
                                    reserve(new_size); 

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const cpstd::bad_alloc& ex){
                                    throw;
                                }
                                catch(...){
                                    throw;
                                }
                            #endif

                                if(new_size < _Capacity)
                                {
                                    return 0;
                                }
                            }

                            for(size_t i = new_size; i < _Size; i++)
                            {
                                _Buffer[i].~T();
                            }

                            auto min = (_Size<new_size) ? _Size : new_size;

                            for(size_t i = min; i < new_size; i++)
                            {
                                _Buffer[i] = value;
                            }

                            _Size = new_size;
                            
                            return 1;
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                
                                auto OldSize = _Vector.size();

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{ 
                            #endif
                                    _Vector.resize(new_size, value);
                            
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const std::bad_alloc& ex){
                                    throw cpstd::bad_alloc();
                                }
                                catch(const std::length_error& ex){
                                    throw cpstd::length_error("Attempted to exceed implementation defined length limits");
                                }
                                catch(const std::logic_error& ex){
                                    throw cpstd::logic_error("Faulty logic detected");
                                }
                                catch(const std::exception& ex){
                                    throw cpstd::exception();
                                }
                                catch(...){
                                    throw;
                                }
                            #endif

                                return ((_Vector.size() == new_size) ? true : false );
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
                    //!
                    //! This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
                    //! Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
                    //! The capacity of a vector can be explicitly altered by calling member vector::reserve.
                    
                        size_t capacity() const noexcept{
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            return _Capacity;
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            return _Vector.capacity();
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Checks if the vector is empty.
                    //!
                    //! This function determines whether the vector contains any elements.
                    //! @return true if the vector is empty, false otherwise.

                        bool empty() const {
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            return (_Size == 0) ? true : false;
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            return _Vector.empty();
                        #endif
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
                    
                        void reserve(size_t new_cap){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) 

                            if(new_cap < _Size){ return;}
                            if(new_cap == 0){ clear(); return;}

                            if(_Buffer == NULL){

                                _Buffer = (T*)calloc(new_cap, sizeof(T));

                                if(_Buffer == NULL){
                                    _Size = 0;
                                    _Capacity = 0;

                                #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                    throw cpstd::bad_alloc();
                                #endif

                                    return;
                                }
                                else{
                                    for (size_t i = 0; i < new_cap; i++) {
                                        _Buffer[i] = cpstd::move(T());
                                        _Buffer[i].~T();
                                    }
                                    _Capacity = new_cap;
                                }
                            }
                            else{

                                T* ptr = NULL;
                                
                                if((ptr = (T*)calloc(new_cap, sizeof(T)) ) != NULL){

                                    for(uint32_t i = 0; i < _Size; i++){
                                        ptr[i] = _Buffer[i];
                                    }

                                    free(_Buffer );
                                    _Buffer = ptr;
                                    _Capacity = new_cap;
                                }
                                else{
                                #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                    throw cpstd::bad_alloc();
                                #endif
                                }
                            }
                        #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                            if(new_cap <= _Size){ return;}
                            if(new_cap == 0){ clear(); return;}

                            if(_Buffer == nullptr){

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{
                            #endif
                                
                                _Buffer = new T[new_cap]; 
                            
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const std::bad_alloc& ex){
                                    throw cpstd::bad_alloc();
                                }
                                catch(...){
                                    throw;
                                }
                            #endif

                                _Capacity = new_cap;
                            }
                            else{

                                T* ptr = nullptr;
                                
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{ 
                            #endif
                                    ptr = new T[new_cap]; 
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const std::bad_alloc& ex){
                                    throw cpstd::bad_alloc();
                                }
                                catch(...){
                                    throw;
                                }
                            #endif

                                if (ptr != nullptr) {
                                    for (size_t i = 0; i < _Size; i++) {
                                        ptr[i] = cpstd::move(_Buffer[i]);
                                    }

                                    delete(_Buffer);
                                    _Buffer = ptr;
                                    _Capacity = new_cap;
                                }

                            }
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{ 
                            #endif
                                    _Vector.reserve(new_cap);
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const std::bad_alloc& ex){
                                    throw cpstd::bad_alloc();
                                }
                                catch(const std::length_error& ex){
                                    throw cpstd::length_error("Attempted to exceed implementation defined length limits");
                                }
                                catch(const std::logic_error& ex){
                                    throw cpstd::logic_error("Faulty logic detected");
                                }
                                catch(const std::exception& ex){
                                    throw cpstd::exception();
                                }
                                catch(...){
                                    throw;
                                }
                            #endif
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Requests the container to reduce its capacity to fit its size.
                    //!
                    //! The request is non-binding, and the container implementation is free to optimize otherwise and leave the vector with a capacity greater than its size.\n
                    //! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.                     
                     
                        void shrink_to_fit(){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                            if(_Capacity > _Size)
                            {
                                T* ptr = NULL;
                                
                                if((ptr = (T*)malloc(_Size * sizeof(T)) ) != NULL)
                                {

                                    for(uint32_t i = 0; i < _Size; i++)
                                    {
                                        ptr[i] = _Buffer[i];
                                    }

                                    free(_Buffer );
                                    _Buffer = ptr;
                                    _Capacity = _Size;
                                }
                                else
                                {
                                #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                    throw cpstd::bad_alloc();
                                #endif
                                }
                            }
                        #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            if(_Capacity > _Size)
                            {
                                T* ptr = nullptr;

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{
                            #endif
                                    ptr = new T[_Size];

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const std::bad_alloc& ex){
                                    throw cpstd::bad_alloc();
                                }
                                catch(...){
                                    throw;
                                }
                            #endif

                                for(unsigned int i = 0; i < _Size; i++){
                                    ptr[i] = _Buffer[i];
                                }

                                delete[] _Buffer;

                                _Buffer = ptr;
                                _Capacity = _Size;
                            }
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                try{
                            #endif

                                    _Vector.shrink_to_fit();

                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                }
                                catch(const std::bad_alloc& ex){
                                    throw cpstd::bad_alloc();
                                }
                                catch(...){
                                    throw;
                                }
                            #endif              
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @}
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Element Access
                //! @{
                
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Subscript Array Operators
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.
                        
                            T& operator[](size_t position) {
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[position];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector[position];
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.

                            const T& operator[](size_t position) const {
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[position];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector[position];
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // at
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.
                        
                            T& at(size_t position) {
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                if(position >= size()){
                                    throw cpstd::out_of_range("Index requested on subscript array does not exists");
                                }
                            #endif
                                
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[position];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.at(position);
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.

                            const T& at(size_t position) const {
                            #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                                if(position >= size()){
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
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // front
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.
                        
                            T& front() {
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[0];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.front();
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.

                            const T& front() const {
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[0];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.front();
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // back
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.
                        
                            T& back() {
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[_Size-1];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.back();
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.

                            const T& back() const {
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer[_Size-1];
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.back();
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // data
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.
                        
                            T* data() noexcept{
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer;
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.data();
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
                        //!
                        //! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
                        //! @tparam position Position of the element to be fetched.

                            const T* data() const noexcept{
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                 return _Buffer;
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return _Vector.data();
                            #endif
                            }
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
                        //! @brief  the new contents are n elements, each initialized to a copy of val
                        //! @tparam n New size for the container.
                        //! @tparam val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
                        
                            void assign(size_t n, const T& val) {
                            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.assign(n, val);
                            #else
                                resize(n);
                                for (size_t i = 0; i < n; i++) {
                                    (*this)[i] = val;
                                }
                            #endif        
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Used to assign new contents to the container by replacing the existing contents.
                        //! @tparam source Another container of the same type.
                         
                            void assign(cpstd::initializer_list<T> il){
                            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                resize(il.size());
                                std::copy(il.begin(), il.end(), _Vector.begin());
                            #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION) | defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                                resize(il.size());
                                for (size_t i = 0; i < size(); i++) {
                                    (*this)[i] = *(il.begin() + i);
                                }
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // push_back
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Appends the given element value to the end of the container.
                        //!
                        //! If after the operation the new size() is greater than old capacity() a reallocation takes place.
                        //! @tparam value the value of the element to append.

                            void push_back(const T& value){
                            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.push_back(value);

                            #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                resize(size() + 1);
                                _Buffer[size() - 1] = value;
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Appends the given element value to the end of the container.
                        //!
                        //! If after the operation the new size() is greater than old capacity() a reallocation takes place.
                        //! The class used must implement the proper move semantics in order for this method to be able to call a move assignment operator.
                        //! @tparam value the value of the element to append.

                            void push_back(T&& Rvalue){
                            #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.push_back(std::move(Rvalue));
                            #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                resize(size() + 1);
                                _Buffer[size() - 1] = cpstd::move(Rvalue);
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Delete the last elemnt
                    //!
                    //! When you call this method on an empty vector, it leads to undefined behavior. The C++ standard does not specify what should happen in this scenario. Attempting to remove an element from an empty container is an error and can cause the program to crash or produce incorrect results.
                    //! @tparam value The value of the element to append.
                    //! @return Returns the poped value
                    
                        void pop_back(){
                        #ifdef CPSTL_VECTOR_EXCEPTIONS_ENABLED
                            if(size() == 0){
                                throw cpstd::out_of_range("Index requested on subscript array does not exists");
                            }
                        #endif

                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            resize(size() - 1);
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.pop_back();
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // insert


                        void insert(size_t position, const T& val){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            resize(_Size + 1);

                            for(size_t i = _Size - 1; i > position; i--){
                                (*this)[i] = cpstd::move((*this)[i-1]);
                            }

                            (*this)[position] = val;

                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.insert(_Vector.begin()+position, val);
                        #endif
                        }

                        void insert(size_t position, T&& val){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                            resize(_Size + 1);

                            for(size_t i = _Size - 1; i > position; i--){
                                (*this)[i] = cpstd::move((*this)[i-1]);
                            }

                            (*this)[position] = cpstd::move(val);

                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.insert(_Vector.begin()+position, val);
                        #endif
                        }

                        void insert(size_t position, size_t n, const T& val){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                            resize(_Size + n);

                            for(size_t i = _Size - 1; i > position; i--){
                                (*this)[i] = cpstd::move((*this)[i-n]);
                            }

                            for(size_t i = position; i < position+n; i++){
                                (*this)[i] = val;
                            }

                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.insert(_Vector.begin()+position, n, val);
                        #endif
                        }

                        void insert(size_t position, cpstd::initializer_list<T> il){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            
                            resize(_Size + il.size());

                            for(size_t i = _Size - 1; i > position; i--){
                                (*this)[i] = cpstd::move((*this)[i-il.size()]);
                            }

                            for(size_t i = position; i < position+il.size(); i++){
                                (*this)[i] = *((il.begin()+(i-position)));
                            }

                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.insert(_Vector.begin()+position, il);
                        #endif
                        }
                    // 
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Deletes the element at the given index from the list, if index >= size the method does nothing.
                    //!
                    //! The element is destroyed and erased.
                    //! @tparam index The index of the element to be erased.

                        void erase(unsigned int index){
                        if(index>=size()){return;}

                        #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.erase(_Vector.begin()+index);
                        #endif

                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            for(unsigned int i = index; i < _Size-1 ;i++) {
                                (*this)[i] = cpstd::move((*this)[i+1]);
                            }
                            resize(size()-1);
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Erases the elements between both given indices
                    //!
                    //! The elements are destroyed and erased. The elemnts erased include (this*)[first] and (this*)[last]. If (last<=first) or (first>=size()) the method does nothing.
                    //! @tparam first The index of the first element to be erased.
                    //! @tparam last The index of the last element to be erased.

                        void erase(size_t first, size_t last){

                            auto sz = size();

                            if((last<=first) || (first>=sz)){return;}
                            if(last>=sz){last = sz-1;}

                        #if defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.erase(_Vector.begin()+first, _Vector.begin()+last);
                        #elif defined(CPSTL_VECTOR_USING_C_ALLOCATION) || defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            auto end = (_Size < last) ? _Size : last;
                            auto range = end - first;


                            for(size_t i = first; i < end ; i++){
                                (*this)[i] = (*this)[i+range];
                            }
                            resize(sz-range);
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Swaps the elements at index_a and index_b
                    //!
                    //! The element is constructed through std::allocator_traits::construct, which typically uses placement-new to construct the element in-place at a location provided by the container. However, if the required location has been occupied by an existing element, the inserted element is constructed at another location at first, and then move assigned into the required location.
                    //! The class used must implement the proper move semantics in order for this method to be able to call a move assignment operator.
                    //! @tparam index_a the value of the first element to swap.

                        void swap(vector& x){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                            auto tmp = x._Buffer;
                            auto sz = x._Size;
                            auto cp = x._Capacity;

                            x._Buffer = _Buffer;
                            x._Size = _Size;
                            x._Capacity = _Capacity;

                            _Buffer = tmp;
                            _Size = sz;
                            _Capacity = cp;

                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            _Vector.swap(x._Vector);
                        #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //! @brief Removes all elements from the vector (which are destroyed), leaving the container with a size and capacity of 0.
                    //!
                    //! if ( capacity > 0 ) A reallocation is guaranteed to happen, and the vector capacity is guaranteed to change due to calling this function.
                     
                        void clear(){
                        #if defined(CPSTL_VECTOR_USING_C_ALLOCATION)
                            for(uint8_t i = 0; i < _Size; i++){
                                _Buffer[i].~T();
                            }

                            free(_Buffer);
                            _Buffer = NULL;
                            _Size = 0;
                            _Capacity = 0;
                        #elif defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                            for(uint8_t i = 0; i < _Size; i++){
                                _Buffer[i].~T();
                            }

                            delete[] _Buffer;
                            _Buffer = nullptr;
                            _Size = 0;
                            _Capacity = 0;
                        #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                            if(_Vector.size() != 0)
                            {
                                _Vector.resize(0);
                            }
                            
                            _Vector.shrink_to_fit();
                        #endif
                        } 
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // emplace
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Inserts a new element into the container directly before pos.
                        //!
                        //! The element is inserted 
                        //! @tparam value The value of the element to append.
                        //! @tparam pos Index where the element will be appended append.

                            void emplace(size_t pos, const T& value){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                resize(_Size+1);
                                for(size_t i = _Size-1 ; i > pos ; i--){
                                    (*this)[i] = cpstd::move( (*this)[i-1] );
                                }

                                (*this)[pos] = value;
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.emplace(_Vector.begin()+pos,value);
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Inserts a new element into the container directly before pos.
                        //!
                        //! The element is inserted 
                        //! @tparam value The value of the element to append.
                        //! @tparam pos Index where the element will be appended append.

                            void emplace(size_t pos, T&& value){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)
                                resize(_Size+1);
                                for(size_t i = _Size-1 ; i > pos ; i--){
                                    (*this)[i] = cpstd::move( (*this)[i-1] );
                                }

                                (*this)[pos] = cpstd::move(value);
                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.emplace(_Vector.begin()+pos,std::move(value));
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // emplace_back
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Inserts a new element into the container directly before pos.
                        //!
                        //! The element is inserted 
                        //! @tparam value The value of the element to append.
                        //! @tparam pos Index where the element will be appended append.

                            void emplace_back(const T& value){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                resize(_Size + 1);
                                (*this)[_Size - 1] = value;


                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.emplace_back(value);
                            #endif
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Inserts a new element into the container directly before pos.
                        //!
                        //! The element is inserted 
                        //! @tparam value The value of the element to append.
                        //! @tparam pos Index where the element will be appended append.

                            void emplace_back(T&& value){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                resize(_Size + 1);
                                (*this)[_Size - 1] = cpstd::move(value);

                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                _Vector.emplace_back(std::move(value));
                            #endif
                            }
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
                        //! Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
                        //! @tparam source Another container of the same type.
                         
                            friend bool operator==(const cpstd::vector<T>& lhs, const cpstd::vector<T>& rhs){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                if( lhs.size() == rhs.size() ){
                                    for(size_t i = 0; i < lhs.size(); i++){
                                        if(lhs[i] != rhs[i]){
                                            return 0;
                                        }
                                    }
                                }
                                else {
                                    return 0;
                                }

                                return 1;

                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return lhs._Vector == rhs._Vector;
                            #endif
                                return 0;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Equal to.
                        //! Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
                        //! @tparam source Another container of the same type.
                        
                            friend bool operator!=(const cpstd::vector<T>& lhs, const cpstd::vector<T>& rhs){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                return !(lhs == rhs);

                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return lhs._Vector != rhs._Vector;
                            #endif
                                return 0;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Equal to.
                        //! Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
                        //! @tparam source Another container of the same type.
                        
                            friend bool operator<(const cpstd::vector<T>& lhs, const cpstd::vector<T>& rhs){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                size_t last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                                for(size_t i = 0; i < last; i++){
                                    if(lhs[i] < rhs[i]){return 1;}
                                }

                                if(lhs.size() < rhs.size()){return 1;}

                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return lhs._Vector < rhs._Vector;
                            #endif
                                return 0;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Equal to.
                        //! Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
                        //! @tparam source Another container of the same type.
                        
                            friend bool operator<=(const cpstd::vector<T>& lhs, const cpstd::vector<T>& rhs){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                size_t last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                                for (size_t i = 0; i < last; i++) {
                                    if (lhs[i] < rhs[i]) { return 1; }
                                }

                                if (lhs.size() <= rhs.size()) { return 1; }

                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return lhs._Vector <= rhs._Vector;
                            #endif
                                return 0;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Equal to.
                        //! Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
                        //! @tparam source Another container of the same type.
                        
                            friend bool operator>(const cpstd::vector<T>& lhs, const cpstd::vector<T>& rhs){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                size_t last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                                for(size_t i = 0; i < last; i++){
                                    if(lhs[i] > rhs[i]){return 1;}
                                }

                                if(lhs.size() > rhs.size()){return 1;}

                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return lhs._Vector > rhs._Vector;
                            #endif
                                return 0;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //! @brief Equal to.
                        //! Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
                        //! @tparam source Another container of the same type.
                        
                            friend bool operator>=(const cpstd::vector<T>& lhs, const cpstd::vector<T>& rhs){
                            #if defined(CPSTL_VECTOR_USING_C_ALLOCATION) | defined(CPSTL_VECTOR_USING_CPP_ALLOCATION)

                                size_t last = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();

                                for (size_t i = 0; i < last; i++) {
                                    if (lhs[i] > rhs[i]) { return 1; }
                                }

                                if (lhs.size() >= rhs.size()) { return 1; }


                            #elif defined(CPSTL_VECTOR_USING_STD_ALLOCATION)
                                return lhs._Vector >= rhs._Vector;
                            #endif
                                return 0;
                            }
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Swap
                        
                        
                    
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @}
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            };

            template<class T>
            void swap(cpstd::vector<T>& lhs, cpstd::vector<T>& rhs) {
                lhs.swap(rhs);
            }
        }
    //!
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






#endif//CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H