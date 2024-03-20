#ifndef CPSTL_BASIC_STREAM_BUFFER_H
#define CPSTL_BASIC_STREAM_BUFFER_H

    #include <CPSTL_BuildSettings.h>
    #include <CPstring.h>
    #include "CPSTL_ios_base.h"

    #if __has_include(<streambuf>)
        #include <streambuf>
    #endif

    namespace cpstd{

        #if __has_include(<streambuf>)
            template<typename CharT, typename Traits = std::char_traits<CharT>>
            using basic_streambuf = std::basic_streambuf<CharT, Traits>;

        #else 

            template <class charT, class traits = cpstd::char_traits<charT> >  
            class basic_streambuf{
            ////////////////////////////////////////////////////////////////////////////////////
            // public types

                public:
                    using char_type = charT;
                    using traits_type = traits;
                    using int_type = typename traits_type::int_type;
                    using pos_type = typename traits_type::pos_type;
                    using off_type = typename traits_type::off_type;
            //
            ////////////////////////////////////////////////////////////////////////////////////
            // Protected Members

                protected:
                    char_type* eback_;  // Pointer to the beginning of the input sequence buffer
                    char_type* gptr_;   // Pointer to the current get pointer position
                    char_type* egptr_;  // Pointer to the end of the input sequence buffer


                    char_type* pbase_;  // Pointer to the beginning of the output sequence buffer
                    char_type* pptr_;   // Pointer to the current get pointer position
                    char_type* epptr_;  // Pointer to the end of the output sequence buffer
            //
            ////////////////////////////////////////////////////////////////////////////////////
            // Constructors and destructor
                
                protected:
                    basic_streambuf();
                    basic_streambuf(const basic_streambuf& x);

                public:
                    virtual ~basic_streambuf(){}
            //
            ////////////////////////////////////////////////////////////////////////////////////
            // Public member functions
                
                public:

                ////////////////////////////////////////////////////////////////////////////////
                // Buffer management and positioning:

                    basic_streambuf* pubsetbuf(char_type* s, streamsize n);
                    pos_type pubseekoff(off_type off, ios_base::seekdir way, ios_base::openmode which = ios_base::in | ios_base::out);
                    pos_type pubseekpos(pos_type pos, ios_base::openmode which = ios_base::in | ios_base::out);
                    int pubsync();
                //
                ////////////////////////////////////////////////////////////////////////////////
                // Input functions (get):
                
                    streamsize in_avail(){
                        return egptr() - gptr();
                    }

                    int_type snextc(){
                        // Check if we are at the end of the buffer
                        if (this->gptr() == this->egptr()) {
                            // Input sequence exhausted
                            return traits_type::eof();
                        }
                        // Advance the get pointer and return the next character
                        return traits_type::to_int_type(*this->gptr());
                    }

                    int_type sbumpc() {
                        if (this->gptr() < this->egptr()) {
                            return traits_type::to_int_type(*this->gptr()++);
                        }
                        return traits_type::eof(); // Input sequence exhausted
                    }

                    int_type sgetc() {
                        if (this->gptr() < this->egptr()) {
                            return traits_type::to_int_type(*this->gptr());
                        }
                        return traits_type::eof(); // Input sequence exhausted
                    }

                    streamsize sgetn(char_type* s, streamsize n) {
                        streamsize count = 0;
                        while (count < n) {
                            int_type ch = sgetc();
                            if (ch == traits_type::eof()) {
                                break; // Reached end of input sequence
                            }
                            *s++ = traits_type::to_char_type(ch);
                            ++count;
                        }
                        return count;
                    }

                    int_type sputbackc(char_type c) {
                        if (this->gptr() > this->eback()) {
                            this->gbump(-1); // Move back one position in the input sequence
                            *this->gptr() = c; // Put back the character
                            return traits_type::to_int_type(c);
                        }
                        return traits_type::eof(); // Cannot put back character, already at beginning of input sequence
                    }

                    int_type sungetc() {
                        if (this->gptr() > this->eback()) {
                            return traits_type::to_int_type(*--this->gptr()); // Move back one position and return the character
                        }
                        return traits_type::eof(); // Cannot unget character, already at beginning of input sequence
                    }
                //
                ////////////////////////////////////////////////////////////////////////////////
                // Output functions (put):

                    int_type sputc(char_type c) {
                        if (this->pptr() < this->epptr()) {
                            *this->pptr() = c; // Write character to current put pointer position
                            this->pbump(1); // Increment put pointer
                            return traits_type::to_int_type(c);
                        }
                        return traits_type::eof(); // Output sequence full
                    }

                    streamsize sputn(const char_type* s, streamsize n) {
                        streamsize count = 0;
                        while (count < n) {
                            if (sputc(*s++) == traits_type::eof()) {
                                break; // Output sequence full
                            }
                            ++count;
                        }
                        return count;
                    }
                //
                ////////////////////////////////////////////////////////////////////////////////
            //
            ////////////////////////////////////////////////////////////////////////////////////
            // Protected member functions 
            protected:
                // Input sequence (get):
                    char_type* eback() const {
                        return eback_; // Return pointer to the beginning of the input sequence buffer
                    }

                    char_type* gptr() const {
                        return gptr_; // Return pointer to the current get pointer position
                    }

                    char_type* egptr() const {
                        return egptr_; // Return pointer to the end of the input sequence buffer
                    }

                    void gbump(int n) {
                        gptr_ += n; // Move the get pointer by 'n' positions
                    }

                    void setg(char_type* new_eback, char_type* new_gptr, char_type* new_egptr) {
                        eback_ = new_eback; // Set the beginning of the input sequence
                        gptr_ = new_gptr;   // Set the current get pointer
                        egptr_ = new_egptr; // Set the end of the input sequence
                    }

                // Output sequence (put):

                    char_type* pbase() const {
                        return pbase_; // Return pointer to the beginning of the output sequence buffer
                    }

                    char_type* pptr() const {
                        return pptr_; // Return pointer to the current put pointer position
                    }

                    char* epptr() const {
                        return epptr_; // Return pointer to the end of the output sequence buffer
                    }

                    void pbump(int n) {
                        pptr_ += n; // Move the put pointer by 'n' positions
                    }

                    void setp(char_type* new_pbase, char_type* new_epptr) {
                        pbase_ = pptr_ = new_pbase; // Set the beginning and current put pointer
                        epptr_ = new_epptr; // Set the end of the output sequence buffer
                    }

                // Copying:

                    basic_streambuf& operator=(const basic_streambuf& rhs) {
                        if (this != &rhs) {
                            // Copy state from rhs to *this
                            eback_ = rhs.eback_;
                            gptr_ = rhs.gptr_;
                            egptr_ = rhs.egptr_;
                        }
                        return *this;
                    }

                    // Swap function
                    void swap(basic_streambuf& x) {
                        // Swap state with another basic_streambuf object
                        cpstd::swap(eback_, x.eback_);
                        cpstd::swap(gptr_, x.gptr_);
                        cpstd::swap(egptr_, x.egptr_);
                    }

            // Virtual protected member functions
            protected:
                // Buffer Management and Positioning
                    virtual basic_streambuf* setbuf (char_type* s, streamsize n){
                        return this;
                    }
                    
                    virtual pos_type seekoff (off_type off, ios_base::seekdir way, ios_base::openmode which = ios_base::in | ios_base::out){
                        return -1;
                    }

                    virtual pos_type seekpos (pos_type pos, ios_base::openmode which = ios_base::in | ios_base::out){
                        return -1;
                    }

                    virtual int sync(){
                        return 0;
                    }

                // Input functions (get):
                    virtual streamsize showmanyc(){
                        return 0;
                    }

                    virtual streamsize xsgetn (char_type* s, streamsize n){
                        streamsize count = 0;
                        for (streamsize i = 0; i < n; ++i) {
                            int_type ch = sbumpc();
                            if (ch == traits_type::eof()) {
                                break; // Reached end of input sequence
                            }
                            s[i] = traits_type::to_char_type(ch);
                            ++count;
                        }
                        return count;
                    }

                    virtual int_type underflow(){
                        return traits_type::eof();
                    }

                    virtual int_type uflow(){
                        if ( underflow() == traits_type::eof() ){ return traits_type::eof(); }
                        gbump(1);
                        return traits_type::to_int_type(gptr()[-1]);
                    }

                    virtual int_type pbackfail (int_type c = traits_type::eof()){
                        return traits_type::eof();
                    }


                // Output functions (put):
                        virtual streamsize xsputn (const char_type* s, streamsize n){
                            streamsize count = 0;
                            for (streamsize i = 0; i < n; ++i) {
                                int_type result = sputc(s[i]);
                                if (result == traits_type::eof()) {
                                    break; // Error occurred while writing
                                }
                                ++count;
                            }
                            return count;
                        }

                        virtual int_type overflow (int_type c = traits_type::eof()){
                            // If the character is not EOF, attempt to write it
                            if (!traits_type::eq_int_type(c, traits_type::eof())) {
                                char_type ch = traits_type::to_char_type(c);
                                if (sputc(ch) == traits_type::eof()) {
                                    return traits_type::eof(); // Error occurred during writing
                                }
                            }
                            
                            return traits_type::not_eof(c);
                        }
            };
            
        #endif
    }

    #include "CPSTL_basic_streambuf.tpp"

#endif//CPSTL_BASIC_STREAM_BUFFER_H
