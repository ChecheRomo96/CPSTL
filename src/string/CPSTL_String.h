#ifndef CPSTL_STRING_CLASS_H
#define CPSTL_STRING_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <utility/CPSTL_Move.h>
    

    #if defined(CPSTL_STRING_EXCEPTIONS_ENABLED) && defined(CPSTL_EXCEPTIONS_ENABLED)
        #include <CPexception.h>
    #endif

    namespace cpstd{  

        #ifdef CPSTL_USING_STL

            template <typename CharType>
            using char_traits = std::char_traits<CharType>;

            template < class charT, class traits = std::char_traits<charT>, class Alloc = std::allocator<charT> >
            using basic_string = std::basic_string< charT, traits, Alloc>;

            class string : public std::string {
            public:
                // Inherit constructors from std::string
                using std::string::string;

                // Constructor for implicit conversion from std::string
                string(const std::string& str) : std::string(str) {}

                // Conversion operator from cpstd::string to std::string
                operator std::string() const {
                    return static_cast<const std::string&>(*this);
                }

                ////////////////////////////////////////////////////////////////////////////////////////
                // formatted
                    
                    void formatted(const char* Format, ...){
                        va_list arg;
                        va_start( arg, Format );
                        
                        auto sz = vsnprintf(NULL, 0, Format, arg);
                        resize(sz);
                        vsnprintf(&((*this)[0]), size()+1, Format, arg);

                    }
                // 
                ////////////////////////////////////////////////////////////////////////////////////////
            };
        #else

            template <typename CharType>
            struct char_traits {
                using char_type = CharType;
                using int_type = int;
                using size_type = size_t;

                static size_type length(const char_type* str) {
                    size_type len = 0;
                    while (*str != '\0') {
                        ++len;
                        ++str;
                    }
                    return len;
                }

                static int_type compare(const char_type* str1, const char_type* str2, size_type count) {
                    for (size_type i = 0; i < count; ++i) {
                        if (str1[i] < str2[i]) return -1;
                        if (str1[i] > str2[i]) return 1;
                    }
                    return 0;
                }

                static char_type* copy(char_type* dest, const char_type* src, size_type count) {
                    for (size_type i = 0; i < count; ++i) {
                        dest[i] = src[i];
                    }
                    return dest;
                }

                static char_type* move(char_type* dest, const char_type* src, size_type count) {
                    for (size_type i = 0; i < count; ++i) {
                        dest[i] = src[i];
                    }
                    return dest;
                }
            };

            class string{
                protected:

                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // C String
                    
                        #if defined(CPSTL_STRING_USING_C_ALLOCATION)
                            size_t _size;
                            size_t _capacity;
                            char* _buffer;
                        #endif
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // std::string
                    
                        #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                            std::string _string;
                        #endif
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                public:

                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // Member Constants

                        #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
                            static constexpr size_t npos = std::string::npos;
                        #else
                            static constexpr size_t npos = -1;
                        #endif
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // Constructors 
                    
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Default Constructor 

                            string();
                            ~string();
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // substring 

                            string(const cpstd::string& str, size_t pos, size_t len = npos);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // fill constructor

                            string(size_t n, char c);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // cpstd::initializer_list<char> 

                            string(cpstd::initializer_list<char> il);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Copy Constructors
                        
                            string(const string& Source);
                            string(const char* Source);
                            string(const char* Source, size_t Size);
                            string(const char& Source);

                            #if defined(CPSTL_USING_STL)
                                string(const std::string& Source);
                            #endif

                            #if defined(ARDUINO)
                                string(const String& Source);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Move Constructors
                            
                            string(string&& Source) noexcept;
                               
                            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                explicit string(std::string&& Source) noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // Capacity
                    
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // size 
                            
                            size_t size() const noexcept;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // length 
                            
                            size_t length() const noexcept;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // capacity 
                            
                            size_t capacity() const noexcept;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // resize 
                            
                            void resize(size_t Size, char new_chars = '\0');
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // reserve 
                            
                            void reserve(size_t n);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // clear 

                            void clear();
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // empty 

                            bool empty() const noexcept;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // shrink_to_fit 

                            void shrink_to_fit();
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // Element Access

                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Subsctipt Array Operator

                            char& operator[](const size_t i);
                            const char operator[](const size_t i) const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // at

                            char& at(size_t n);
                            const char& at(size_t n) const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // back

                            char& back();
                            const char& back() const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // front

                            char& front();
                            const char& front() const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // Modifiers
                    
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // addition assignment operator ( += )

                            cpstd::string& operator+=(const cpstd::string& rhs);
                            cpstd::string& operator+=(const char* rhs);
                            cpstd::string& operator+=(char c);
                            cpstd::string& operator+=(cpstd::initializer_list<char> rhs);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Assignment operator ( = )

                            string& operator=(const string& Source);
                            string& operator=(const char* Source);
                            string& operator=(char Source);
                            string& operator=(cpstd::initializer_list<char> il);

                            #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
                                string& operator=(const std::string& Source);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Move Assignment operators ( = rValue)

                            string& operator=(cpstd::string&& Source) noexcept;

                            #if defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                string& operator=(std::string&& Source);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // append
                        
                            cpstd::string& append(const cpstd::string& str);
                            cpstd::string& append(const cpstd::string& str, size_t subpos, size_t sublen = npos);cpstd::string& append(const char* s);
                            cpstd::string& append(const char* s, size_t n);
                            cpstd::string& append(size_t n, char c);
                            cpstd::string& append(cpstd::initializer_list<char> il);
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                cpstd::string& append(const std::string& str);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // push_back
                        
                            void push_back (char c);
                        // 
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // assign

                            cpstd::string& assign(const cpstd::string& str);
                            cpstd::string& assign(const cpstd::string& str, size_t subpos, size_t sublen);
                            cpstd::string& assign(const char* s);
                            cpstd::string& assign(const char* s, size_t n);
                            cpstd::string& assign(size_t n, char c);
                            cpstd::string& assign(cpstd::string&& str) noexcept;
                            cpstd::string& assign(cpstd::initializer_list<char> il);

                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                cpstd::string& assign(const std::string& str);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // insert

                            cpstd::string& insert(size_t pos, const cpstd::string& str);
                            cpstd::string& insert(size_t pos, const cpstd::string& str, size_t subpos, size_t sublen);
                            cpstd::string& insert(size_t pos, const char* s);
                            cpstd::string& insert(size_t pos, const char* s, size_t n);
                            cpstd::string& insert(size_t pos, size_t n, char c);
                            cpstd::string& insert(size_t pos, cpstd::initializer_list<char> il);
                                
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                cpstd::string& insert(size_t pos, const std::string& str);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // erase

                            cpstd::string& erase(size_t pos, size_t len = cpstd::string::npos);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // replace

                            cpstd::string& replace(size_t pos, size_t len, const cpstd::string& str);
                            cpstd::string& replace(size_t pos, size_t len, const cpstd::string& str, size_t subpos, size_t sublen);
                            cpstd::string& replace(size_t pos, size_t len, const char* s);
                            cpstd::string& replace(size_t pos, size_t len, const char* s, size_t n);
                            cpstd::string& replace(size_t pos, size_t len, size_t n, char c);
                            cpstd::string& replace(size_t pos, size_t len, cpstd::initializer_list<char> il);

                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                cpstd::string& replace(size_t pos, size_t len, const std::string& str);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // swap
                        
                            void swap (cpstd::string& str);
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                void swap (std::string& str);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // pop_back

                            void pop_back();
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // formatted
                            
                            void formatted(const char* Format, ...);
                        // 
                        ////////////////////////////////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // String operations

                        ////////////////////////////////////////////////////////////////////////////////////////
                        // std::string cast

                            #if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
                                operator std::string() const;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // c_str

                            const char* c_str() const noexcept;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // data

                            const char* data() const noexcept;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // copy

                            size_t copy(char* s, size_t len, size_t pos = 0) const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // find

                            size_t find(const cpstd::string& str, size_t pos = 0) const noexcept;
                            size_t find(const char* s, size_t pos = 0) const;
                            size_t find(const char* s, size_t pos, size_t n) const;
                            size_t find(char c, size_t pos = 0) const noexcept;

                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                size_t find(const std::string& str, size_t pos = 0) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // rfind

                            size_t rfind(const cpstd::string& str, size_t pos = cpstd::string::npos) const noexcept;
                            size_t rfind(const char* s, size_t pos = cpstd::string::npos) const;
                            size_t rfind(const char* s, size_t pos, size_t n) const;
                            size_t rfind(char c, size_t pos = cpstd::string::npos) const noexcept;

                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                size_t rfind(const std::string& str, size_t pos = cpstd::string::npos) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // find_first_of

                            size_t find_first_of(const cpstd::string& str, size_t pos = 0) const noexcept;
                            size_t find_first_of(const char* s, size_t pos = 0) const;
                            size_t find_first_of(const char* s, size_t pos, size_t n) const;
                            size_t find_first_of(char c, size_t pos = 0) const noexcept;

                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                size_t find_first_of(const std::string& str, size_t pos = 0) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // find_last_of

                            size_t find_last_of(const cpstd::string& str, size_t pos = cpstd::string::npos) const noexcept;
                            size_t find_last_of(const char* s, size_t pos = cpstd::string::npos) const;
                            size_t find_last_of(const char* s, size_t pos, size_t n) const;
                            size_t find_last_of(char c, size_t pos = cpstd::string::npos) const noexcept;
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                size_t find_last_of(const std::string& str, size_t pos = cpstd::string::npos) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // find_first_not_of

                            size_t find_first_not_of(const cpstd::string& str, size_t pos = 0) const noexcept;
                            size_t find_first_not_of(const char* s, size_t pos = 0) const;
                            size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
                            size_t find_first_not_of(char c, size_t pos = 0) const noexcept;

                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                size_t find_first_not_of(const std::string& str, size_t pos = 0) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // find_last_not_of

                            size_t find_last_not_of(const cpstd::string& str, size_t pos = cpstd::string::npos) const noexcept;
                            size_t find_last_not_of(const char* s, size_t pos = cpstd::string::npos) const;
                            size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
                            size_t find_last_not_of(char c, size_t pos = cpstd::string::npos) const noexcept;
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                size_t find_last_not_of(const std::string& str, size_t pos = cpstd::string::npos) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // substr
                        
                            cpstd::string substr(size_t pos = 0, size_t len = cpstd::string::npos) const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // compare

                            int compare(const cpstd::string& str) const noexcept;
                            int compare(size_t pos, size_t len, const string& str) const;
                            int compare(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen) const;
                            int compare(const char* s) const;
                            int compare(size_t pos, size_t len, const char* s) const;
                            int compare(size_t pos, size_t len, const char* s, size_t n) const;
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                int compare(const std::string& str) const noexcept;
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
                    // Non-member function overloads
                     
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // operator+ - Concatenate Strings

                            ////////////////////////////////////////////////////////////////////////////////////
                            // CPString

                                friend cpstd::string operator+(const cpstd::string& lhs, const cpstd::string& rhs);
                                friend cpstd::string operator+(cpstd::string&& lhs, cpstd::string&& rhs);
                                friend cpstd::string operator+(const cpstd::string& lhs, cpstd::string&& rhs);
                                friend cpstd::string operator+(cpstd::string&& lhs, const cpstd::string& rhs);
                            //
                            ////////////////////////////////////////////////////////////////////////////////////
                            // C string
                                
                                
                                friend cpstd::string operator+(const cpstd::string& lhs, const char* rhs);
                                friend cpstd::string operator+(cpstd::string&& lhs, const char* rhs);
                                friend cpstd::string operator+(const char* lhs, const cpstd::string& rhs);
                                friend cpstd::string operator+(const char* lhs, cpstd::string&& rhs);
                            //
                            ////////////////////////////////////////////////////////////////////////////////////
                            // char
                    
                                friend cpstd::string operator+ (const cpstd::string& lhs, char rhs);
                                friend cpstd::string operator+ (cpstd::string&& lhs, char rhs);
                                friend cpstd::string operator+ (char lhs, const cpstd::string& rhs);
                                friend cpstd::string operator+ (char lhs, cpstd::string&& rhs);
                            //
                            ////////////////////////////////////////////////////////////////////////////////////
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // Relational operators (cpstd::string)
                        // 
                            friend bool operator==(const cpstd::string& lhs, const cpstd::string& rhs) noexcept;
                            friend bool operator==(const char* lhs, const cpstd::string& rhs);
                            friend bool operator==(const cpstd::string& lhs, const char* rhs);

                            friend bool operator!=(const cpstd::string& lhs, const cpstd::string& rhs) noexcept;
                            friend bool operator!=(const char* lhs, const cpstd::string& rhs);
                            friend bool operator!=(const cpstd::string& lhs, const char* rhs);

                            friend bool operator<(const cpstd::string& lhs, const cpstd::string& rhs) noexcept;
                            friend bool operator<(const char* lhs, const cpstd::string& rhs);
                            friend bool operator<(const cpstd::string& lhs, const char* rhs);

                            friend bool operator<=(const cpstd::string& lhs, const cpstd::string& rhs) noexcept;
                            friend bool operator<=(const char* lhs, const cpstd::string& rhs);
                            friend bool operator<=(const cpstd::string& lhs, const char* rhs);

                            friend bool operator>(const cpstd::string& lhs, const cpstd::string& rhs) noexcept;
                            friend bool operator>(const char* lhs, const cpstd::string& rhs);
                            friend bool operator>(const cpstd::string& lhs, const char* rhs);

                            friend bool operator>=(const cpstd::string& lhs, const cpstd::string& rhs) noexcept;
                            friend bool operator>=(const char* lhs, const cpstd::string& rhs);
                            friend bool operator>=(const cpstd::string& lhs, const char* rhs);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // swap
                
                            friend void swap(cpstd::string& x, cpstd::string& y);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // operator>> (Extract  string from stream)
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                friend std::istream& operator>>(std::istream& os, cpstd::string& String);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // operator<< (Insert string into stream)
                            
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                friend std::ostream& operator<<(std::ostream& os, const cpstd::string& String);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////
                        // getline
                        // 
                            #if defined(CPSTL_USING_STL) || defined(CPSTL_STRING_USING_STD_ALLOCATION)
                                friend std::istream& getline (std::istream&  is, cpstd::string& str, char delim);
                                friend std::istream& getline (std::istream&& is, cpstd::string& str, char delim);
                                
                                friend std::istream& getline (std::istream&  is, cpstd::string& str);
                                friend std::istream& getline (std::istream&& is, cpstd::string& str);
                            #endif
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////            
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////
            };
        #endif



    }
    
#endif//CPSTL_STRING_CLASS_H