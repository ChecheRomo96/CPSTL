#include "CPSTL_basic_ostream.h"

namespace cpstd{
#if !__has_include(<ostream>)
    
    //////////////////////////////////////////////////////////////////////////////////////
    // Constructors and destructor

        //////////////////////////////////////////////////////////////////////////////////
        // Default 

            template <class charT, class traits>
            basic_ostream<charT, traits>::basic_ostream(basic_streambuf<char_type, traits_type>* sb)
                : basic_ios<char_type, traits_type>(sb) {
                // Initialize additional members if needed
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // Move 

            template <class charT, class traits>
            basic_ostream<charT, traits>::basic_ostream(basic_ostream<charT, traits>&& x)
                : basic_ios<charT, traits>(cpstd::move(x)) {
                // Move additional resources owned by basic_ostream if any
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // Destructor

            template <class charT, class traits>
            basic_ostream<charT, traits>::~basic_ostream() {
                // No specific destructor logic needed
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Move assignment

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator=(basic_ostream&& rhs) {
            if (this != &rhs) {
                // Call base class move assignment operator
                basic_ios<charT, traits>::operator=(std::move(rhs));
                // Move additional resources owned by basic_ostream if any
            }
            return *this;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // swap

        template <class charT, class traits>
        void basic_ostream<charT, traits>::swap(basic_ostream& x) {
            // Call base class swap function
            basic_ios<charT, traits>::swap(x);
            // Swap additional resources owned by basic_ostream if any
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // formatted output 

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(bool val){
            if (this->good()) {
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    charT ch = val ? '1' : '0';
                    if (sb->sputc(ch) == traits::eof()) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(short val) {
            if (this->good()) {
                // Convert short to string using stringstream
                std::basic_stringstream<charT> ss;
                ss << val;
                std::basic_string<charT> str = ss.str();
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(unsigned short val) {
            if (this->good()) {
                // Convert unsigned short to string using stringstream
                std::basic_stringstream<charT> ss;
                ss << val;
                std::basic_string<charT> str = ss.str();
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(int val) {
            if (this->good()) {
                // Convert int to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(unsigned int val) {
            if (this->good()) {
                // Convert unsigned int to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(long val) {
            if (this->good()) {
                // Convert long to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(unsigned long val) {
            if (this->good()) {
                // Convert unsigned long to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(long long val) {
            if (this->good()) {
                // Convert long long to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(unsigned long long val) {
            if (this->good()) {
                // Convert unsigned long long to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(float val) {
            if (this->good()) {
                // Convert float to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(double val) {
            if (this->good()) {
                // Convert double to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(long double val) {
            if (this->good()) {
                // Convert long double to string
                std::basic_string<charT> str = std::to_string(val);
                
                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(void* ptr) {
            if (this->good()) {
                // Convert the pointer address to a string
                std::basic_stringstream<charT> ss;
                ss << ptr;
                std::basic_string<charT> str = ss.str();

                // Write the string to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::streamsize len = str.length();
                    if (sb->sputn(str.data(), len) != len) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(basic_streambuf<char_type, traits_type>* sb) {
            if (this->good()) {
                // Output the content of the stream buffer to the current stream
                if (sb) {
                    charT buffer[1024]; // Example buffer size
                    while (std::streamsize count = sb->sgetn(buffer, sizeof(buffer))) {
                        if (this->rdbuf()->sputn(buffer, count) != count) {
                            this->setstate(std::ios_base::badbit);
                            break;
                        }
                    }
                    if (sb->pubsync() == -1) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    // If the stream buffer is null, set the badbit
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(basic_ostream& (*pf)(basic_ostream&)) {
            // Call the provided function pointer with the current stream
            return (*pf)(*this);
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(basic_ios<char_type, traits_type>& (*pf)(basic_ios<char_type, traits_type>&)) {
            // Call the provided function pointer with the current stream's basic_ios
            return (*pf)(*this);
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::operator<<(ios_base& (*pf)(ios_base&)) {
            // Call the provided function pointer with the current stream's ios_base
            return (*pf)(*this);
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Unformatted output
        
        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::put(char_type c) {
            if (this->good()) {
                // Write a single character to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    if (sb->sputc(c) == traits::eof()) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::write(const char_type* s, std::streamsize n) {
            if (this->good() && n >= 0) {
                // Write a sequence of characters to the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    if (sb->sputn(s, n) != n) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Positioning
    
        template <class charT, class traits>
        typename basic_ostream<charT, traits>::pos_type basic_ostream<charT, traits>::tellp() {
            if (this->good()) {
                // Get the current position of the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    return sb->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
                }
            }
            return traits_type::pos_type(-1);
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::seekp(typename basic_ostream<charT, traits>::pos_type pos) {
            if (this->good()) {
                // Seek to the specified position in the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    if (sb->pubseekpos(pos, std::ios_base::out) == pos_type(off_type(-1))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::seekp(typename basic_ostream<charT, traits>::off_type off, std::ios_base::seekdir way) {
            if (this->good()) {
                // Seek relative to the specified position in the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    if (sb->pubseekoff(off, way, std::ios_base::out) == pos_type(off_type(-1))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Synchronization
    
        template <class charT, class traits>
        basic_ostream<charT, traits>& basic_ostream<charT, traits>::flush() {
            if (this->good()) {
                // Flush the output buffer associated with the stream buffer
                std::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    if (sb->pubsync() == -1) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////



#endif
}