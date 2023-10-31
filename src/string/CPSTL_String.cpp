#include "CPSTL_String.h"

namespace {
    static const char EmptyCString[] = {'\0'};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Default Constructor

        cpstd::string::string(){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string = std::string("");
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            _buffer = NULL;
            _size = 0;
            _capacity = 0;

            reserve(0);
            resize(0);
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

        cpstd::string::~string(){
            clear();

        #if defined (CPSTL_STRING_USING_C_ALLOCATION)
            if(_buffer != NULL){
                free(_buffer);
            }
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // substring

        cpstd::string::string(const cpstd::string& str, size_t pos, size_t len) : string(){
            if (pos < str.length()){
                if (len == npos){
                    (*this) = str.substr(pos , str.length() - pos);
                    return;
                }
                else if (len <= (str.length() - pos)){
                    (*this) = str.substr(pos , len);
                    return;
                }
            }
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // fill constructor

        cpstd::string::string(size_t n, char c) : string(){
            resize(n,c);
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // cpstd::initializer_list<char> 

        cpstd::string::string(cpstd::initializer_list<char> il) : string(){
            resize(il.size());

        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            std::copy(il.begin(), il.end(), _string.begin());
        #else
            for(size_t i = 0; i < size(); i++){
                (*this)[i] = *(il.begin()+i);
            }
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Copy Constructors
                
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPstring

            cpstd::string::string(const cpstd::string& Source) : string(){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string = Source;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                resize(Source.length());
                for(uint16_t i = 0; i < _size; i++){
                    _buffer[i] = Source[i];
                }
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            cpstd::string::string(const char& Source) : string(){
                resize(1);
                (*this)[0] = Source;
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string

            cpstd::string::string(const char* Source) : string(){
                if(Source == NULL){
                    resize(0);
                }

                else{
                    auto len = static_cast<size_t>(strlen(Source));
                    resize(len);
                    for(size_t i = 0; i < size() ; i++){
                        (*this)[i] = Source[i];
                    }
                }
            }

            cpstd::string::string(const char* Source, size_t Size) : string(){
                if(Source == NULL){
                    return;
                }
            
                else{
                    resize(Size);

                    for(size_t i = 0; i < Size; i++){
                        (*this)[i] = Source[i];
                    }
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string

            #if defined(CPSTL_USING_STL)
                cpstd::string::string(const std::string& Source) : string(){
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    _string = Source;
                #else
                    resize(Source.size());

                    for(size_t i = 0; i < size(); i++)
                    {
                        (*this)[i] = Source[i];
                    }
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Arduino String

            #if defined(Arduino_h)
                cpstd::string::string(const String& Source) : string(){
                    resize(Source.size());

                    for(size_t i = 0; i < size(); i++){
                        (*this)[i] = Source[i];
                    }
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Move Constructors
                
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPstring

            cpstd::string::string(cpstd::string&& Source) noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string = std::move(Source._string);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                _buffer = Source._buffer;
                _size = Source._size;
                _capacity = Source._capacity;

                Source._buffer = NULL;
                Source._size = 0;
                Source._capacity = 0;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                cpstd::string::string(std::string&& Source) noexcept{
                    _string = Source;
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Capacity
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // size
    
        size_t cpstd::string::size() const noexcept{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.length();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            return _size;
        #endif
            return 0;
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // length
    
        size_t cpstd::string::length() const noexcept{
            return size();
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // resize
    
        void cpstd::string::resize(size_t new_size, char new_chars){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.resize(new_size, new_chars);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)

            if(new_size > _capacity){ 
                reserve(new_size);
                if (_capacity < new_size) { return; }
            }
            else if (new_size < _capacity) { _buffer[new_size] = '\0'; }
            

            if(new_size > _size){
                for(size_t i = _size; i < new_size; i++){
                    _buffer[i] = new_chars;
                }
            }
            _size = new_size;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // capacity
    
        size_t cpstd::string::capacity() const noexcept{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.capacity();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            return _capacity;
        #endif
            return 0;
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // reserve
    
        void cpstd::string::reserve(size_t n){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.reserve(n);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            
            if (n == 0) {
                if (_buffer == NULL) {
                    char* tmp = NULL;
                    tmp = (char*)malloc(sizeof(char));
                    if (tmp != NULL){
                        tmp[0] = '\0';
                        _buffer = tmp;
                    }
                }
                return;
            }

            if(_capacity >= n){ return; }
            char* tmp = NULL;
            tmp = (char*)calloc(n + 1, sizeof(char));
            if(tmp != NULL){
                size_t MaintainedData = (n < _size) ? n : _size;

                for (size_t i = 0; i < MaintainedData; i++) {
                    tmp[i] = _buffer[i];
                }

                if (_buffer != NULL) { free(_buffer); }
                _capacity = n;
                _buffer = tmp;
            }

        #endif

        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // clear

        void cpstd::string::clear(){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.clear();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            resize(0);
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // empty 

        bool cpstd::string::empty() const noexcept{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.empty();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            if(_size == 0){return 1;}
        #endif
            return 0;
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // shrink_to_fit 

        void cpstd::string::shrink_to_fit(){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.shrink_to_fit();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            if(capacity() > _size)
            {
                char* ptr = NULL;
                ptr = (char*)calloc(_size + 1, sizeof(char));

                if (ptr != NULL) {
                    for (size_t i = 0; i < _size; i++) {
                        ptr[i] = _buffer[i];
                    }

                    free(_buffer);
                    _buffer = ptr;
                    _capacity = _size;
            }
                else
                {
                #ifdef CPSTL_STRING_EXCEPTIONS_ENABLED
                    //throw cpstd::bad_alloc();
                #endif
                }
            }
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Element Access
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Subsctipt Array Operator

        char& cpstd::string::operator[](const size_t i){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string[i];
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            return _buffer[i];
        #endif
        }

        const char cpstd::string::operator[](const size_t i) const{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string[i];
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            return _buffer[i];
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // at

        char& cpstd::string::at(size_t n){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.at(n);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            //if(n >= _size) exception
            return _buffer[n];
        #endif
        }

        const char& cpstd::string::at(size_t n) const{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.at(n);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            //if(n >= _size) exception
            return _buffer[n];
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // back

        char& cpstd::string::back(){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.back();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            //if(_size == 0) exception
            return _buffer[_size-1];
        #endif
        }

        const char& cpstd::string::back() const{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.back();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            return _buffer[_size-1];
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // front

        char& cpstd::string::front(){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.front();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            //if(_size == 0) exception
            return _buffer[0];
        #endif
        }

        const char& cpstd::string::front() const{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.front();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            //if(_size == 0) exception
            return _buffer[0];
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Modifiers

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // addition assignment operator ( += )

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPString

            cpstd::string& cpstd::string::operator+=(const cpstd::string& rhs){
                size_t a = length();
                size_t b = rhs.length();

                if(b == 0){
                    return (*this);
                }
                else{
                    resize( a + b );

                    for(size_t i = a; i < a+b; i++){
                        (*this)[i] = rhs[i-a];
                    }
                }

                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string

            cpstd::string& cpstd::string::operator+=(const char* rhs){
                size_t a = length();
                size_t b = strlen(rhs);

                if(b == 0){
                    return (*this);
                }
                else{
                    resize( a + b );

                    for(size_t i = a; i < a+b; i++){
                        (*this)[i] = rhs[i-a];
                    }
                }

                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            cpstd::string& cpstd::string::operator+=(char c){
                size_t a = length();

                resize( a + 1 );
                (*this)[a] = c;

                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // initializer list

            cpstd::string& cpstd::string::operator+=(cpstd::initializer_list<char> il){
                size_t a = length();
                size_t b = il.size();

                if(b == 0){
                    return (*this);
                }
                else{
                    resize( a + b );

                    for(size_t i = a; i < a+b; i++){
                        (*this)[i] = *(il.begin()+(i-a));
                    }
                }

                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Assignment operator ( = )
    
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            cpstd::string& cpstd::string::operator=(const cpstd::string& Source){
                if(this != &Source){
                    resize(Source.length());
                    for(size_t i = 0; i < Source.length(); i++){
                        (*this)[i] = Source[i];
                    }
                }
                return *this;
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string

            cpstd::string& cpstd::string::operator=(const char* Source){
                if(Source == NULL){
                    resize(0); 
                }
                else{
                    resize(strlen(Source));
                    for (uint16_t i = 0; i < size(); i++) {
                        (*this)[i] = Source[i];
                    }
                }

                
                return *this;
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            cpstd::string& cpstd::string::operator=(char c){
                resize( 1 );
                (*this)[0] = c;
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // initializer list

            cpstd::string& cpstd::string::operator=(cpstd::initializer_list<char> il){
                size_t b = il.size();

                if(b == 0){
                    return (*this);
                }
                else{
                    resize( b );

                    for(uint8_t i = 0; i < b; i++){
                        (*this)[i] = *(il.begin()+i);
                    }
                }

                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string
                        
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
                cpstd::string& cpstd::string::operator=(const std::string& Source){
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    if (&_string == &Source) {  return *this; }
                #endif
                    resize(Source.length());
                    for (uint16_t i = 0; i < Source.length(); i++) {
                        (*this)[i] = Source[i];
                    }

                    return *this;
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Move Assignment operator ( = rvalue)
    
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            cpstd::string& cpstd::string::operator=(cpstd::string&& Source) noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string = Source._string;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (_buffer != NULL) {
                    free(_buffer);
                }

                _buffer = Source._buffer;
                _size = Source._size;
                _capacity = Source._capacity;

                Source._buffer = NULL;
                Source._size = 0;
                Source._capacity = 0;
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                cpstd::string& cpstd::string::operator=(std::string&& Source){
                    _string = Source;
                    return (*this);
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // append 
     
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPString
                
            cpstd::string& cpstd::string::append(const cpstd::string& str) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.append(str._string);
                return (*this);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t offset = _size;

                resize(_size + str.size());

                for (size_t i = 0; i < str.size(); i++) {
                    (*this)[offset + i] = str[i];
                }

                return (*this);
            #endif
            }
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
                
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                cpstd::string& cpstd::string::append(const std::string& str) {
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    _string.append(str);
                    return (*this);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    size_t offset = _size;

                    resize(_size + str.size());

                    for (size_t i = 0; i < str.size(); i++) {
                        (*this)[offset + i] = str[i];
                    }
                    return (*this);
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // substring
                
            cpstd::string& cpstd::string::append(const cpstd::string& str, size_t subpos, size_t sublen) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.append(cpstd::string::string(str, subpos, sublen));
                return (*this);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)

                if (str.size() >= subpos) {
                    size_t offset = _size;
                    size_t end = (str.size() < subpos + sublen) ? str.size() : subpos + sublen;
                    size_t len = (str.size() < subpos + sublen) ? str.size() - subpos : sublen;

                    resize(_size + len);

                    for (size_t i = 0; i < len; i++) {
                        (*this)[offset + i] = str[subpos + i];
                    }
                }
                return (*this);
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string
                
            cpstd::string& cpstd::string::append(const char* s) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.append(s);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t offset = _size;
                size_t len = strlen(s);
                if (len != 0) {
                    resize(_size + len);

                    for (size_t i = 0; i < len; i++) {
                        _buffer[offset + i] = s[i];
                    }
                }
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer 

            cpstd::string& cpstd::string::append(const char* s, size_t n){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.append(s,n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t offset = _size;
                if (n != 0) {
                    resize(_size + n);

                    for (size_t i = 0; i < n; i++) {
                        _buffer[offset + i] = s[i];
                    }
            }
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // fill

            cpstd::string& cpstd::string::append(size_t n, char c){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.append(n,c);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t offset = _size;
                if (n != 0) {
                    resize(_size + n);

                    for (size_t i = 0; i < n; i++) {
                        _buffer[offset + i] = c;
                    }
                }
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // initializer list

            cpstd::string& cpstd::string::append(cpstd::initializer_list<char> il){

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.append(il);
            #else
                size_t offset = size();
                resize(size()+il.size());

                for(size_t i = offset; i < size(); i++){
                    (*this)[i] = *(il.begin()+(i-offset));
                }
            #endif

                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // push_back 
     
        void cpstd::string::push_back(char c){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.push_back(c);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            size_t oldSz = _size;
            resize(_size + 1);
            if (_size > oldSz) {
                _buffer[_size - 1] = c;
            }
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // assign 
     
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPString
                
            cpstd::string& cpstd::string::assign(const cpstd::string& str) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(str._string);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                (*this) = str;
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // substring
                
            cpstd::string& cpstd::string::assign(const cpstd::string& str, size_t subpos, size_t sublen) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(cpstd::string::string(str, subpos, sublen));
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                cpstd::string tmp = str.substr(subpos, sublen);
                (*this) = cpstd::move(tmp);
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string
                
            cpstd::string& cpstd::string::assign(const char* s) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(s);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                (*this) = cpstd::move(cpstd::string(s));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer
                
            cpstd::string& cpstd::string::assign(const char* s, size_t n) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(s,n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                (*this) = cpstd::move(cpstd::string(s,n));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // fill
                
            cpstd::string& cpstd::string::assign(size_t n, char c) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(n,c);
                return (*this);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                (*this) = cpstd::move(cpstd::string(n,c));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // move
                
            cpstd::string& cpstd::string::assign(cpstd::string&& str) noexcept {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(std::move(str._string));
                return (*this);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                (*this) = cpstd::move(str);
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // initializer list

            cpstd::string& cpstd::string::assign(cpstd::initializer_list<char> il){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.assign(il);
            #else
                (*this) = cpstd::move(cpstd::string(il));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // assign
                
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                cpstd::string& cpstd::string::assign(const std::string& str) {
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    _string.assign(str);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    (*this) = cpstd::move(cpstd::string(str));
                #endif
                    return (*this);
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // insert 
     
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPString
                
            cpstd::string& cpstd::string::insert(size_t pos, const cpstd::string& str) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.insert(pos, str._string);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if(!str.empty()){
                    if(pos < _size){

                        auto oldSize = _size;
                        resize(_size + str._size);
                        auto offset = _size - oldSize;

                        for(size_t i =_size-1; i > pos; i--){
                            _buffer[i] = _buffer[i - offset];
                        }


                        for(size_t i = 0; i < str._size; i++){
                            _buffer[pos + i] = str._buffer[i];
                        }
                    }
                }
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // substring
                
            cpstd::string& cpstd::string::insert(size_t pos, const cpstd::string& str, size_t subpos, size_t sublen) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.insert(pos, cpstd::string::string(str, subpos, sublen));
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                insert(pos, str.substr(subpos, sublen));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string
                
            cpstd::string& cpstd::string::insert(size_t pos, const char* s) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.insert(pos, s);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                insert(pos, cpstd::string(s));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer
                
            cpstd::string& cpstd::string::insert(size_t pos, const char* s, size_t n) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.insert(pos, s,n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                insert(pos, cpstd::string(s,n));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // fill
                
            cpstd::string& cpstd::string::insert(size_t pos, size_t n, char c) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.insert(pos, n,c);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                insert(pos, cpstd::string(n,c));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // initializer list

            cpstd::string& cpstd::string::insert(size_t pos, cpstd::initializer_list<char> il){

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.insert(pos, il);
            #else
                insert(pos, cpstd::string(il));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
            
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)    
                cpstd::string& cpstd::string::insert(size_t pos, const std::string& str) {
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    _string.insert(pos, str);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    insert(pos, cpstd::string(str));
                #endif
                    return (*this);
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // erase

        cpstd::string& cpstd::string::erase(size_t pos, size_t len) {
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.erase(pos, len);
            return (*this);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)

            if(pos < _size){
                auto length = (len != npos) ? ((_size < pos + len) ? _size - pos : len) : _size - pos;

                for(size_t i = pos + length; i < _size; i++){
                    _buffer[i - length] = _buffer[i];
                }
                resize(_size - length);
            }

            return (*this);

        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // replace 
     
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // CPString
                
            cpstd::string& cpstd::string::replace(size_t pos, size_t len, const cpstd::string& str) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.replace(pos, len, str._string);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (pos < _size) {
                    auto removeLength = (_size < pos + len) ? _size - pos : len;
                    auto newLength = str.size();

                    if (newLength < removeLength) {
                        size_t difference = removeLength - newLength;
                        memmove(_buffer + pos + newLength, _buffer + pos + removeLength, _size - (pos + removeLength));
                        resize(_size - difference);
                    }
                    else if (newLength > removeLength) {
                        size_t difference = newLength - removeLength;
                        resize(_size + difference);
                        memmove(_buffer + pos + newLength, _buffer + pos + removeLength, _size - (pos + removeLength + difference));
                    }

                    if (newLength != 0) {
                        memcpy(_buffer + pos, str.c_str(), newLength);
                    }
                }
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // substring
                
            cpstd::string& cpstd::string::replace(size_t pos, size_t len, const cpstd::string& str, size_t subpos, size_t sublen) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.replace(pos, len, cpstd::string::string(str, subpos, sublen));
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                replace(pos, len, cpstd::string(str, subpos, sublen));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string
                
            cpstd::string& cpstd::string::replace(size_t pos, size_t len, const char* s) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.replace(pos, len, s);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                replace(pos, len, cpstd::string(s));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer
                
            cpstd::string& cpstd::string::replace(size_t pos, size_t len, const char* s, size_t n) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.replace(pos, len, s,n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                replace(pos, len, cpstd::string(s,n));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // fill
                
            cpstd::string& cpstd::string::replace(size_t pos, size_t len, size_t n, char c) {
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.replace(pos,len,n,c);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                replace(pos, len, cpstd::string(n,c));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // initializer list

            cpstd::string& cpstd::string::replace(size_t pos, size_t len, cpstd::initializer_list<char> il){

            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                _string.replace(pos, len, il);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                replace(pos, len, cpstd::string(il));
            #endif
                return (*this);
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
                
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                cpstd::string& cpstd::string::replace(size_t pos, size_t len, const std::string& str) {
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    _string.replace(pos, len, str);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    replace(pos,len,cpstd::string(str));
                #endif
                    return (*this);
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // swap
    
        void cpstd::string::swap (cpstd::string& str){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.swap(str._string);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            cpstd::string tmp = cpstd::move(str);
            str = cpstd::move(*this);
            (*this) = cpstd::move(tmp);
        #endif
        }
        
        #if defined (CPSTL_STRING_USING_STD_ALLOCATION)
            void cpstd::string::swap (std::string& str){
                _string.swap(str);
            }
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // pop_back

        void cpstd::string::pop_back(){
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            _string.pop_back();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            resize(_size-1);
        #endif

        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // formatted 
     
        void cpstd::string::formatted(const char* Format, ... ){
            va_list arg;
            va_start( arg, Format );
            
            auto sz = vsnprintf(NULL, 0, Format, arg);
            resize(sz);
            vsnprintf(&((*this)[0]), size()+1, Format, arg);

        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////
// String operations

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // std::string cast operator

        #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
            cpstd::string::operator std::string() const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                return std::string(_buffer, _size);
            #endif
            }
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // c_str

        const char* cpstd::string::c_str() const noexcept{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.c_str();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            if(_buffer == NULL){return EmptyCString;}
            return _buffer;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // data

        const char* cpstd::string::data() const noexcept{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.data();
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            return _buffer;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // copy

        size_t cpstd::string::copy(char* s, size_t len, size_t pos) const{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return _string.copy(s, len, pos);
        #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
            if(pos<_size){
                auto length = (_size < pos + len) ? _size - pos : len;

                for(auto i = pos; i < pos + length; i++){
                    s[i-pos] = _buffer[i];
                }
                return length;
            }
            return 0;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // find

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            size_t cpstd::string::find(const cpstd::string& str, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.find(str._string, pos);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t substringLength = str.size();

                if (substringLength > _size || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i <= _size - substringLength; ++i) {
                    size_t j;
                    for (j = 0; j < substringLength; ++j) {
                        if (_buffer[i + j] != str._buffer[j]) {break;}
                    }
                    if (j == substringLength) {return i;}
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C String

            size_t cpstd::string::find(const char* s, size_t pos) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.find(s, pos);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t substringLength =  strlen(s);

                if (substringLength > _size || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i <= _size - substringLength; ++i) {
                    size_t j;
                    for (j = 0; j < substringLength; ++j) {
                        if (_buffer[i + j] != s[j]) {break;}
                    }
                    if (j == substringLength) {return i;}
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            size_t cpstd::string::find(const char* s, size_t pos, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.find(s, pos, n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t substringLength =  n;

                if (substringLength > _size || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i <= _size - substringLength; ++i) {
                    size_t j;
                    for (j = 0; j < substringLength; ++j) {
                        if (_buffer[i + j] != s[j]) {break;}
                    }
                    if (j == substringLength) {return i;}
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            size_t cpstd::string::find(char c, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.find(c, pos);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                for (size_t i = pos; i < _size; ++i) {
                    if (_buffer[i] == c) {
                        return i; 
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
        // 
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t cpstd::string::find(const std::string& str, size_t pos) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    return _string.find(str, pos);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    return find(cpstd::string(str),pos);
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // rfind

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            size_t cpstd::string::rfind(const cpstd::string& str, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.rfind(str._string, pos);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t substringLength = str.size();
                
                if (substringLength > _size || substringLength == 0) {
                    return cpstd::string::npos;
                }

                if (pos > _size - substringLength) {
                    pos = _size - substringLength;
                }

                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    size_t j;
                    for (j = 0; j < substringLength; ++j) {
                        if (_buffer[i + j] != str[j]) {
                            break;
                        }
                    }
                    if (j == substringLength) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C String

            size_t cpstd::string::rfind(const char* s, size_t pos) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.rfind(s, pos);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t substringLength = strlen(s);
                
                if (substringLength > _size || substringLength == 0) {
                    return cpstd::string::npos;
                }

                if (pos > _size - substringLength) {
                    pos = _size - substringLength;
                }

                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    size_t j;
                    for (j = 0; j < substringLength; ++j) {
                        if (_buffer[i + j] != s[j]) {
                            break;
                        }
                    }
                    if (j == substringLength) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            size_t cpstd::string::rfind(const char* s, size_t pos, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.rfind(s, pos, n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)                
                size_t substringLength = n;
                
                if (substringLength > _size || substringLength == 0) {
                    return cpstd::string::npos;
                }

                if (pos > _size - substringLength) {
                    pos = _size - substringLength;
                }

                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    size_t j;
                    for (j = 0; j < substringLength; ++j) {
                        if (_buffer[i + j] != s[j]) {
                            break;
                        }
                    }
                    if (j == substringLength) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            size_t cpstd::string::rfind(char c, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.rfind(c, pos);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t cpstd::string::rfind(const std::string& str, size_t pos) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    return _string.rfind(str, pos);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    size_t substringLength = str.size();
                    size_t _size = size();
                    
                    if (substringLength > _size || substringLength == 0) {
                        return cpstd::string::npos;
                    }

                        if (pos > _size - substringLength) {
                        pos = _size - substringLength;
                    }

                    for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                        size_t j;
                        for (j = 0; j < substringLength; ++j) {
                            if (_buffer[i + j] != str[j]) {
                                break;
                            }
                        }
                        if (j == substringLength) {
                            return i;
                        }
                    }
                    return cpstd::string::npos;
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // find_first_of

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            size_t cpstd::string::find_first_of(const cpstd::string& str, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_first_of(str._string, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = str.size();

                if (strLength == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i < _size; ++i) {
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == str[j]) {
                            return i;
                        }
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C String

            size_t cpstd::string::find_first_of(const char* s, size_t pos) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                auto ret =_string.find_first_of(s, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = strlen(s);

                if (strLength == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i < _size; ++i) {
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == s[j]) {
                            return i; 
                        }
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            size_t cpstd::string::find_first_of(const char* s, size_t pos, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_first_of(s, pos, n);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (n == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i < _size; ++i) {
                    for (size_t j = 0; j < n; ++j) {
                        if (_buffer[i] == s[j]) {
                            return i; 
                        }
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            size_t cpstd::string::find_first_of(char c, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_first_of(c, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i < _size; ++i) {
                    if (_buffer[i] == c) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t cpstd::string::find_first_of(const std::string& str, size_t pos) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    size_t ret = _string.find_first_of(str, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    // Not Yet Implemented
                    return cpstd::string::npos;
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // find_last_of

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            size_t cpstd::string::find_last_of(const cpstd::string& str, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_last_of(str._string, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = str.size();

                if (strLength == 0 || _size == 0) {
                    return cpstd::string::npos;
                }

                pos = (pos >= _size) ? _size - 1 : pos;
                
                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == str[j]) {
                            return i;
                        }
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C String

            size_t cpstd::string::find_last_of(const char* s, size_t pos) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                auto ret =_string.find_last_of(s, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = strlen(s);

                if (strLength == 0 || _size == 0) {
                    return cpstd::string::npos;
                }

                pos = (pos >= _size) ? _size - 1 : pos;
                
                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == s[j]) {
                            return i;
                        }
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            size_t cpstd::string::find_last_of(const char* s, size_t pos, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_last_of(s, pos, n);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            size_t cpstd::string::find_last_of(char c, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_last_of(c, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t cpstd::string::find_last_of(const std::string& str, size_t pos) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    size_t ret = _string.find_last_of(str, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    size_t strLength = str.size();

                    if (strLength == 0 || pos >= _size) {
                        return cpstd::string::npos;
                    }

                    for (size_t i = pos; i < _size; ++i) {
                        for (size_t j = 0; j < strLength; ++j) {
                            if (_buffer[i] == str[j]) {
                                return i;
                            }
                        }
                    }

                    return cpstd::string::npos;
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // find_first_not_of

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            size_t cpstd::string::find_first_not_of(const cpstd::string& str, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_first_not_of(str._string, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = str.size();

                if (strLength == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                bool found = false;
                for (size_t i = pos; i < _size; ++i) {
                    found = false;
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == str[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C String

            size_t cpstd::string::find_first_not_of(const char* s, size_t pos) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                auto ret =_string.find_first_not_of(s, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = strlen(s);

                if (strLength == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                bool found = false;
                for (size_t i = pos; i < _size; ++i) {
                    found = false;
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == s[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            size_t cpstd::string::find_first_not_of(const char* s, size_t pos, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_first_not_of(s, pos, n);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)

                if (n == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                bool found = false;
                for (size_t i = pos; i < _size; ++i) {
                    found = false;
                    for (size_t j = 0; j < n; ++j) {
                        if (_buffer[i] == s[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            size_t cpstd::string::find_first_not_of(char c, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_first_not_of(c, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i < _size; ++i) {
                    if (_buffer[i] != c) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t cpstd::string::find_first_not_of(const std::string& str, size_t pos) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    size_t ret = _string.find_first_not_of(str, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    size_t strLength = str.size();

                    if (strLength == 0 || pos >= _size) {
                        return cpstd::string::npos;
                    }

                    bool found = false;
                    for (size_t i = pos; i < _size; ++i) {
                        found = false;
                        for (size_t j = 0; j < strLength; ++j) {
                            if (_buffer[i] == str[j]) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            return i;
                        }
                    }
                    return cpstd::string::npos;
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // find_last_not_of

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            size_t cpstd::string::find_last_not_of(const cpstd::string& str, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_last_not_of(str._string, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = str.size();

                if (strLength == 0) {
                    return (_size > 0) ? _size - 1 : cpstd::string::npos;
                }

                size_t searchStart = (pos == cpstd::string::npos || pos >= _size) ? _size - 1 : std::min(pos, _size - 1);

                for (size_t i = searchStart; i != static_cast<size_t>(-1); --i) {
                    bool found = false;
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == str[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        return i;
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C String

            size_t cpstd::string::find_last_not_of(const char* s, size_t pos) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                auto ret =_string.find_last_not_of(s, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                size_t strLength = strlen(s);

                if (strLength == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    bool found = false;
                    for (size_t j = 0; j < strLength; ++j) {
                        if (_buffer[i] == s[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        return i;
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            size_t cpstd::string::find_last_not_of(const char* s, size_t pos, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_last_not_of(s, pos, n);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (n == 0 || pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    bool found = false;
                    for (size_t j = 0; j < n; ++j) {
                        if (_buffer[i] == s[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        return i;
                    }
                }

                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            size_t cpstd::string::find_last_not_of(char c, size_t pos) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t ret = _string.find_last_not_of(c, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                if (pos >= _size) {
                    return cpstd::string::npos;
                }

                for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                    if (_buffer[i] != c) {
                        return i;
                    }
                }
                return cpstd::string::npos;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                size_t cpstd::string::find_last_not_of(const std::string& str, size_t pos) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    size_t ret = _string.find_last_not_of(str, pos);
                return (ret == std::string::npos) ? cpstd::string::npos : ret;
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    size_t strLength = str.size();

                    if (strLength == 0 || pos >= _size) {
                        return cpstd::string::npos;
                    }

                    for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
                        bool found = false;
                        for (size_t j = 0; j < strLength; ++j) {
                            if (_buffer[i] == str[j]) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            return i;
                        }
                    }

                    return cpstd::string::npos;
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // substr
        
        cpstd::string cpstd::string::substr(size_t pos, size_t len) const{
        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
            return cpstd::string::string(_string.substr(pos, len));
        #else
            cpstd::string ret;
            if (pos < _size) {
                auto length = (len != npos) ? ((_size < pos + len) ? _size - pos : len ) : _size - pos;
                ret = cpstd::move(cpstd::string(_buffer + pos, length));
            }
            return ret;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // compare

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // cpstd::string::string

            int cpstd::string::compare(const cpstd::string& str) const noexcept{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.compare(str._string);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                for (size_t i = 0; (i < _size) && (i < str.size()); ++i) {
                    if (_buffer[i] != str[i]) {
                        return _buffer[i] - str[i];
                    }
                }

                if (_size != str.size()) {
                    return (_size < str.size()) ? -1 : 1;
                }

                return 0;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // substrings

            int cpstd::string::compare(size_t pos, size_t len, const cpstd::stringstring& str) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.compare(pos, len, str);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                const size_t thisSize = _size;
                if (pos >= thisSize || len == 0) {
                    if (len > thisSize)
                        return 1;
                    return 0;
                }

                const size_t compareLen = (len == npos || pos + len > thisSize) ? thisSize - pos : len;

                for (size_t i = 0; i < compareLen && i < str.size(); ++i) {
                    if (_buffer[pos + i] != str[i]) {
                        return _buffer[pos + i] - str[i];
                    }
                }

                if (compareLen < str.size()) {
                    return (compareLen < str.size()) ? -1 : 1;
                }

                return 0;
            #endif
            }

            int cpstd::string::compare(size_t pos, size_t len, const cpstd::stringstring& str, size_t subpos, size_t sublen) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.compare(pos, len, str, subpos, sublen);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return 0;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string

            int cpstd::string::compare(const char* s) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.compare(s);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return 0;
            #endif
            }

            int cpstd::string::compare(size_t pos, size_t len, const char* s) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.compare(pos, len, s);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return 0;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // buffer

            int cpstd::string::compare(size_t pos, size_t len, const char* s, size_t n) const{
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return _string.compare(pos, len, s, n);
            #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                // Not Yet Implemented
                return 0;
            #endif
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // std::string
        
            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                int cpstd::string::compare(const std::string& str) const noexcept{
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    return _string.compare(str);
                #elif defined(CPSTL_STRING_USING_C_ALLOCATION)
                    // Not Yet Implemented
                    return 0;
                #endif
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Non-member functions

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // operator+ - Concatenate Strings

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // string

            namespace cpstd{
                string operator+(const string& lhs, const string& rhs){
                    string toReturn = lhs;
                    toReturn += rhs;
                    return toReturn;
                }

                string operator+(string&& lhs, string&& rhs){
                    lhs.append(rhs);
                    rhs.clear();
                    return move(lhs);
                }

                string operator+(const string& lhs, string&& rhs){
                    string toReturn = lhs;
                    toReturn.append(rhs);
                    rhs.clear();
                    return toReturn;
                }

                string operator+(string&& lhs, const string& rhs){
                    lhs.append(rhs);
                    return move(lhs);
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // C string

            namespace cpstd{
                string operator+(const string& lhs, const char* rhs){
                    string toReturn = lhs;
                    toReturn.append(rhs);
                    return toReturn;
                }

                string operator+(string&& lhs, const char* rhs){
                    lhs.append(rhs);
                    return move(lhs);
                }

                string operator+(const char* lhs, const string& rhs){
                    string toReturn = lhs;
                    toReturn.append(rhs);
                    return toReturn;
                }

                string operator+(const char* lhs, string&& rhs){
                    string toReturn = lhs;
                    toReturn.append(rhs);
                    rhs.clear();
                    return toReturn;
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // char

            namespace cpstd{
                string operator+ (const string& lhs, char rhs){
                    string toReturn = lhs;
                    toReturn.append(1,rhs);
                    return toReturn;
                }

                string operator+ (string&& lhs, char rhs){
                    lhs.append(1,rhs);
                    return move(lhs);
                }

                string operator+ (char lhs, const string& rhs){
                    string toReturn(lhs);
                    toReturn.append(rhs);
                    return toReturn;
                }

                string operator+ (char lhs, string&& rhs){
                    string toReturn(lhs);
                    toReturn.append(rhs);
                    rhs.clear();
                    return toReturn;
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Relational operators (string::string)

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Equality

            namespace cpstd{
                bool operator==(const string& lhs, const string& rhs) noexcept{
                    if(strcmp(lhs.c_str(), rhs.c_str()) == 0) { return 1; }
                    else{return 0;}
                }

                bool operator==(const char* lhs, const string& rhs){
                    if(strcmp(lhs, rhs.c_str()) == 0) { return 1; }
                    else{return 0;}
                }

                bool operator==(const string& lhs, const char* rhs){
                    if(strcmp(lhs.c_str(), rhs) == 0) { return 1; }
                    else{return 0;}
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Inequality

            namespace cpstd{
                bool operator!=(const string& lhs, const string& rhs) noexcept{
                    if(strcmp(lhs.c_str(), rhs.c_str()) == 0) { return 0; }
                    else{return 1;}
                }

                bool operator!=(const char* lhs, const string& rhs){
                    if(strcmp(lhs, rhs.c_str()) == 0) { return 0; }
                    else{return 1;}
                }

                bool operator!=(const string& lhs, const char* rhs){
                    if(strcmp(lhs.c_str(), rhs) == 0) { return 0; }
                    else{return 1;}
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Less than

            namespace cpstd{
                bool operator<(const string& lhs, const string& rhs) noexcept{
                    if(strcmp(lhs.c_str(), rhs.c_str()) < 0) { return 1; }
                    else{return 0;}
                }

                bool operator<(const char* lhs, const string& rhs){
                    if(strcmp(lhs, rhs.c_str()) < 0) { return 1; }
                    else{return 0;}
                }

                bool operator<(const string& lhs, const char* rhs){
                    if(strcmp(lhs.c_str(), rhs) < 0) { return 1; }
                    else{return 0;}
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Less or equal than

            namespace cpstd{
                bool operator<=(const string& lhs, const string& rhs) noexcept{
                    if(strcmp(lhs.c_str(), rhs.c_str()) <= 0) { return 1; }
                    else{return 0;}
                }

                bool operator<=(const char* lhs, const string& rhs){
                    if(strcmp(lhs, rhs.c_str()) <= 0) { return 1; }
                    else{return 0;}
                }

                bool operator<=(const string& lhs, const char* rhs){
                    if(strcmp(lhs.c_str(), rhs) <= 0) { return 1; }
                    else{return 0;}
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Greater than

            namespace cpstd{
                bool operator>(const string& lhs, const string& rhs) noexcept{
                    if(strcmp(lhs.c_str(), rhs.c_str()) > 0) { return 1; }
                    else{return 0;}
                }

                bool operator>(const char* lhs, const string& rhs){
                    if(strcmp(lhs, rhs.c_str()) > 0) { return 1; }
                    else{return 0;}
                }

                bool operator>(const string& lhs, const char* rhs){
                    if(strcmp(lhs.c_str(), rhs) > 0) { return 1; }
                    else{return 0;}
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // Greater or equal than

            namespace cpstd{
                bool operator>=(const string& lhs, const string& rhs) noexcept{
                    if(strcmp(lhs.c_str(), rhs.c_str()) >= 0) { return 1; }
                    else{return 0;}
                }

                bool operator>=(const char* lhs, const string& rhs){
                    if(strcmp(lhs, rhs.c_str()) >= 0) { return 1; }
                    else{return 0;}
                }

                bool operator>=(const string& lhs, const char* rhs){
                    if(strcmp(lhs.c_str(), rhs) >= 0) { return 1; }
                    else{return 0;}
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////
        // swap
        // 
            namespace cpstd{
                void swap(string& x, string& y){
                #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                    std::swap(x._string, y._string);
                #else
                    string tmp = cpstd::move(x);
                    x = cpstd::move(y);
                    y = cpstd::move(tmp);
                #endif
                }
            }
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // operator>> (Insert string into stream)

        #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
            
            std::istream& cpstd::operator>>(std::istream& is, cpstd::string& String){
#           if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return is >> String._string;
            #else
                return is >> std::string(String.c_str(), String.size());
            #endif  
            }
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // operator<< (Insert string into stream)

        #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
            
            std::ostream& cpstd::operator<<(std::ostream& os, const cpstd::string& String){
                return os << String.c_str();
            }
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // getline
    // 
        #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
            std::istream& cpstd::getline (std::istream&  is, cpstd::string& str, char delim){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return std::getline(is, str._string, delim);
            #else
                return std::getline(is, std::string(str.c_str(), str.size()), delim);
            #endif  
            }

            std::istream& cpstd::getline (std::istream&& is, cpstd::string& str, char delim){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return std::getline(is, str._string, delim);
            #else
                return std::getline(is, std::string(str.c_str(), str.size()), delim);
            #endif  
            }
            
            std::istream& cpstd::getline (std::istream&  is, cpstd::string& str){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return std::getline(is, str._string);
            #else
                return std::getline(is, std::string(str.c_str(), str.size()));
            #endif  
            }

            std::istream& cpstd::getline (std::istream&& is, cpstd::string& str){
            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                return std::getline(is, str._string);
            #else
                return std::getline(is, std::string(str.c_str(), str.size()));
            #endif  
            }
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
