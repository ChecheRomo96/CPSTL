#include "CPSTL_basic_istream.h"
#include "CPSTL_basic_streambuf.h"

namespace cpstd{
#if !__has_include(<istream>)
    
    //////////////////////////////////////////////////////////////////////////////////////
    // Constructors and destructor

        template <class charT, class traits>
        basic_istream<charT, traits>::basic_istream(cpstd::basic_streambuf<charT, traits>* sb) 
        : basic_ios<charT, traits>(sb) {

        }

        // Move constructor
        template <class charT, class traits>
        basic_istream<charT, traits>::basic_istream(basic_istream&& x)
        : basic_ios<charT, traits>(cpstd::move(x)) {

        }

        // Move constructor
        template <class charT, class traits>
        basic_istream<charT, traits>:: ~basic_istream(){

        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Move assignment

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator= (basic_istream<charT, traits>&& rhs) {

        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // swap

        template <class charT, class traits>
        void basic_istream<charT, traits>::swap(basic_istream<charT, traits>& x) {

        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // forrmatted input
    
        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(bool& val){
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    // Read a single character from the stream
                    charT ch;
                    if (sb->sgetc() != traits::eof()) {
                        ch = sb->sbumpc();
                        // Set val based on the character read
                        val = (ch == '1' || ch == 't' || ch == 'T');
                    } else {
                        // End of file encountered
                        this->setstate(std::ios_base::eofbit);
                    }
                } else {
                    // Stream buffer is invalid
                    this->setstate(std::ios_base::badbit);
                }
            }
        return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(short& val){
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(unsigned short& val){
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }


        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(int& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(unsigned int& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(long& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(unsigned long& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(long long& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(unsigned long long& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(float& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(double& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(long double& val) {
            if (this->good()) {
                cpstd::basic_streambuf<charT, traits>* sb = this->rdbuf();
                if (sb) {
                    std::basic_ostringstream<charT> ss;
                    ss << val;
                    std::basic_string<charT> str = ss.str();
                    
                    // Write the string to the stream
                    if (!(this->operator<<(str))) {
                        this->setstate(std::ios_base::badbit);
                    }
                } else {
                    this->setstate(std::ios_base::badbit);
                }
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(basic_streambuf<charT, traits>* sb) {
            if (this->good() && sb) {
                // Use the provided stream buffer for input
                charT buffer[1024]; // Example buffer size
                std::streamsize bytesRead;
                while ((bytesRead = this->readsome(buffer, sizeof(buffer))) > 0) {
                    // Write the read data into the provided stream buffer
                    std::streamsize written = sb->sputn(buffer, bytesRead);
                    if (written != bytesRead) {
                        // If not all bytes are written, set failbit
                        this->setstate(std::ios_base::failbit);
                        break;
                    }
                }
                if (bytesRead == -1) {
                    // If an error occurs during reading, set failbit
                    this->setstate(std::ios_base::failbit);
                }
            } else {
                // If the input stream is not good or provided stream buffer is null, set failbit
                this->setstate(std::ios_base::failbit);
            }
            return *this;
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(basic_istream<charT, traits>& (*pf)(basic_istream<charT, traits>&)) {
            // Call the manipulator function with the reference to this stream
            return pf(*this);
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(basic_ios<charT, traits>& (*pf)(basic_ios<charT, traits>&)) {
            // Call the manipulator function with the reference to this stream
            return pf(*this);
        }

        template <class charT, class traits>
        basic_istream<charT, traits>& basic_istream<charT, traits>::operator>>(ios_base& (*pf)(ios_base&)) {
            // Call the manipulator function with the reference to the stream's ios_base
            pf(ios_base::fmtflags());
            return *this;
        }
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Unformatted input

        //////////////////////////////////////////////////////////////////////////////////
        // gcount

            template <class charT, class traits>
            streamsize basic_istream<charT, traits>::gcount() const {
                return this->traits_type::length(this->gptr(), this->egptr()) - this->traits_type::length(this->eback(), this->gptr());
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // get
       
            // 1. typename basic_ios<charT, traits>::int_type get();
            template <class charT, class traits>
            typename basic_ios<charT, traits>::int_type basic_istream<charT, traits>::get() {
                typename traits::int_type c = this->rdbuf()->sbumpc();
                return c;
            }

            // 2. basic_istream& get (typename basic_ios<charT, traits>::char_type& c);
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::get(typename basic_ios<charT, traits>::char_type& c) {
                typename traits::int_type ic = this->rdbuf()->sbumpc();
                if (traits::eq_int_type(ic, traits::eof()))
                    this->setstate(ios_base::eofbit);
                else
                    c = traits::to_char_type(ic);
                return *this;
            }

            // 3. basic_istream& get(typename basic_ios<charT, traits>::char_type* s, streamsize n);
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::get(typename basic_ios<charT, traits>::char_type* s, streamsize n) {
                streamsize extracted = 0;
                typename traits::int_type c = this->rdbuf()->sbumpc();
                while (extracted < n && !traits::eq_int_type(c, traits::eof())) {
                    *s++ = traits::to_char_type(c);
                    ++extracted;
                    c = this->rdbuf()->sbumpc();
                }
                if (traits::eq_int_type(c, traits::eof()))
                    this->setstate(ios_base::eofbit);
                return *this;
            }

            // 4. basic_istream& get(typename basic_ios<charT, traits>::char_type* s, streamsize n, charT delim);
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::get(typename basic_ios<charT, traits>::char_type* s, streamsize n, charT delim) {
                streamsize extracted = 0;
                typename traits::int_type c = this->rdbuf()->sbumpc();
                while (extracted < n && !traits::eq_int_type(c, traits::eof()) && !traits::eq(c, delim)) {
                    *s++ = traits::to_char_type(c);
                    ++extracted;
                    c = this->rdbuf()->sbumpc();
                }
                if (traits::eq(c, delim))
                    this->rdbuf()->sputbackc(c);
                if (traits::eq_int_type(c, traits::eof()))
                    this->setstate(ios_base::eofbit);
                return *this;
            }

            // 5. basic_istream& get(basic_streambuf<charT,traits>& sb);
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::get(basic_streambuf<charT, traits>& sb) {
                typename traits::int_type c = this->rdbuf()->sbumpc();
                while (!traits::eq_int_type(c, traits::eof())) {
                    sb.sputc(c);
                    c = this->rdbuf()->sbumpc();
                }
                if (traits::eq_int_type(c, traits::eof()))
                    this->setstate(ios_base::eofbit);
                return *this;
            }

            // 6. basic_istream& get(basic_streambuf<charT,traits>& sb, typename basic_ios<charT, traits>::char_type delim);
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::get(basic_streambuf<charT, traits>& sb, typename basic_ios<charT, traits>::char_type delim) {
                typename traits::int_type c = this->rdbuf()->sbumpc();
                while (!traits::eq_int_type(c, traits::eof()) && !traits::eq(c, delim)) {
                    sb.sputc(c);
                    c = this->rdbuf()->sbumpc();
                }
                if (traits::eq(c, delim))
                    this->rdbuf()->sputbackc(c);
                if (traits::eq_int_type(c, traits::eof()))
                    this->setstate(ios_base::eofbit);
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // getline

            // 1. basic_istream& getline(typename basic_ios<charT, traits>::char_type* s, streamsize n );
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::getline(typename basic_ios<charT, traits>::char_type* s, streamsize n) {
                return this->getline(s, n, this->widen('\n')); // Delegate to the version with delimiter
            }

            // 2. basic_istream& getline(typename basic_ios<charT, traits>::char_type* s, streamsize n, typename basic_ios<charT, traits>::char_type delim);
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::getline(typename basic_ios<charT, traits>::char_type* s, streamsize n, typename basic_ios<charT, traits>::char_type delim) {
                streamsize extracted = 0;
                typename traits::int_type c = this->rdbuf()->sgetc(); // Peek at the next character
                while (extracted + 1 < n && !traits::eq_int_type(c, traits::eof()) && !traits::eq(c, delim)) {
                    *s++ = traits::to_char_type(c);
                    ++extracted;
                    c = this->rdbuf()->snextc(); // Move to the next character
                }
                if (traits::eq(c, delim)) {
                    // Consume the delimiter if found
                    this->rdbuf()->sbumpc();
                }
                if (extracted == 0 && traits::eq_int_type(c, traits::eof())) {
                    // If no characters were extracted and we reached EOF, set the fail bit
                    this->setstate(ios_base::failbit);
                }
                *s = charT(); // Null-terminate the string
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // ignore
        
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::ignore(streamsize n, typename basic_ios<charT, traits>::int_type delim) {
                streamsize count = 0;
                typename traits::int_type c;
                while (count < n && ((c = this->rdbuf()->sbumpc()) != traits::eof())) {
                    if (traits::eq_int_type(c, delim))
                        break;
                    ++count;
                }
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // peek

            template <class charT, class traits>
            typename basic_ios<charT, traits>::int_type basic_istream<charT, traits>::peek() {
                typename traits::int_type c = this->rdbuf()->sgetc(); // Peek at the next character
                return c;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // read

            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::read(typename basic_ios<charT, traits>::char_type* s, streamsize n) {
                streamsize extracted = 0;
                typename traits::int_type c = this->rdbuf()->sbumpc(); // Get the next character
                while (extracted < n && !traits::eq_int_type(c, traits::eof())) {
                    *s++ = traits::to_char_type(c); // Store the character in the buffer
                    ++extracted;
                    c = this->rdbuf()->sbumpc(); // Get the next character
                }
                if (traits::eq_int_type(c, traits::eof())) {
                    // If EOF is reached, set the fail bit
                    this->setstate(ios_base::eofbit);
                }
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // readsome


            template <class charT, class traits>
            streamsize basic_istream<charT, traits>::readsome(typename basic_ios<charT, traits>::char_type* s, streamsize n) {
                streamsize extracted = 0;
                streamsize available = this->rdbuf()->in_avail(); // Get the number of available characters in the input buffer
                while (extracted < n && available > 0) {
                    *s++ = this->rdbuf()->sbumpc(); // Read a character from the input buffer
                    ++extracted;
                    --available;
                }
                return extracted;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // putback

            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::putback(typename basic_ios<charT, traits>::char_type c) {
                if (!this->rdbuf()->sputbackc(c)) {
                    // If sputbackc fails (e.g., buffer is full), set the fail bit
                    this->setstate(ios_base::failbit);
                }
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // unget
            
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::unget() {
                if (!this->rdbuf()->sungetc()) {
                    // If sungetc fails (e.g., buffer is empty), set the fail bit
                    this->setstate(ios_base::failbit);
                }
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        
    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Positioning

        //////////////////////////////////////////////////////////////////////////////////
        // tellg

            template <class charT, class traits>
            typename basic_istream<charT, traits>::pos_type basic_istream<charT, traits>::tellg() {
                return this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::in);
            }
        //
        //////////////////////////////////////////////////////////////////////////////////
        // seekg
        
            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::seekg(typename basic_istream<charT, traits>::pos_type pos) {
                this->rdbuf()->pubseekpos(pos, ios_base::in);
                return *this;
            }

            template <class charT, class traits>
            basic_istream<charT, traits>& basic_istream<charT, traits>::seekg(typename basic_istream<charT, traits>::off_type off, ios_base::seekdir way) {
                this->rdbuf()->pubseekoff(off, way, ios_base::in);
                return *this;
            }
        //
        //////////////////////////////////////////////////////////////////////////////////

    //
    //////////////////////////////////////////////////////////////////////////////////////
    // Synchronization
        
        template <class charT, class traits>
        int basic_istream<charT, traits>::sync() {
            if (this->rdbuf()) {
                // Synchronize the associated input stream buffer
                if (this->rdbuf()->pubsync() == -1) {
                    // If synchronization fails, return -1
                    return -1;
                }
            }
            return 0; // Return 0 on success
        }
    // 
    //////////////////////////////////////////////////////////////////////////////////////

#endif
}