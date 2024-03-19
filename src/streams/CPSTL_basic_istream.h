#ifndef CPSTL_ISTREAM_HEADER
#define CPSTL_ISTREAM_HEADER


    #include <CPSTL_BuildSettings.h>
    #include <CPios.h>

    #ifdef CPSTL_USING_STL
        #include <ios>
    #endif
    
    namespace cpstd{
    #if __has_include(<istream>)
        
        template <class charT, class Traits = char_traits<charT> >
        using basic_istream = std::basic_istream<charT, Traits>;
    #else

        template <class charT, class Traits = cpstd::char_traits<charT>>
        class basic_istream : virtual public basic_ios<charT, Traits> {
            
            //////////////////////////////////////////////////////////////////////////////////////
            // types
            
                using char_type = charT;
                using Traits_type = Traits;
                using int_type = typename Traits_type::int_type;
                using pos_type = typename Traits_type::pos_type;
                using off_type = typename Traits_type::off_type;
            // 
            //////////////////////////////////////////////////////////////////////////////////////
            // Sentry Class

                public:

                    class sentry {
                    public:
                      explicit sentry (basic_istream& is, bool noskipws = false);
                      ~sentry();
                      explicit operator bool() const;
                      sentry (const sentry&) = delete;
                      sentry& operator= (const sentry&) = delete;
                    };
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Constructors and destructor

                public:

                    explicit basic_istream(basic_streambuf<charT, Traits>* sb);

                    // Deleted copy constructor
                    basic_istream(const basic_istream&) = delete;

                    // Destructor (no implementation provided)
                    virtual ~basic_istream();

                protected:
                    // Move constructor
                    basic_istream(basic_istream&& x);
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Move assignment
            
                protected:
                    basic_istream& operator=(const basic_istream&) = delete;
                    basic_istream& operator=(basic_istream&& rhs);
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // swap
            
                protected:
                    void swap (basic_istream& x);
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // formatted input
            
                public:
                    basic_istream& operator>>(bool& val);
                    basic_istream& operator>>(short& val);
                    basic_istream& operator>>(unsigned short& val);
                    basic_istream& operator>>(int& val);
                    basic_istream& operator>>(unsigned int& val);
                    basic_istream& operator>>(long& val);
                    basic_istream& operator>>(unsigned long& val);
                    basic_istream& operator>>(long long& val);
                    basic_istream& operator>>(unsigned long long& val);
                    basic_istream& operator>>(float& val);
                    basic_istream& operator>>(double& val);
                    basic_istream& operator>>(long double& val);
                    basic_istream& operator>>(void*& val);
                    basic_istream& operator>>(basic_streambuf<charT, Traits>* sb);
                    basic_istream& operator>>(basic_istream& (*pf)(basic_istream&));
                    basic_istream& operator>>(basic_ios<charT, Traits>& (*pf)(basic_ios<charT, Traits>&));
                    basic_istream& operator>>(ios_base& (*pf)(ios_base&));
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Unformatted input:
            
                public:
                    streamsize gcount() const;

                    typename basic_ios<charT, Traits>::int_type get();
                    basic_istream& get (typename basic_ios<charT, Traits>::char_type& c);
                    basic_istream& get(typename basic_ios<charT, Traits>::char_type* s, streamsize n);
                    basic_istream& get(typename basic_ios<charT, Traits>::char_type* s, streamsize n, charT delim);
                    basic_istream& get(basic_streambuf<charT,traits>& sb);
                    basic_istream& get(basic_streambuf<charT,traits>& sb, typename basic_ios<charT, Traits>::char_type delim);

                    basic_istream& getline(typename basic_ios<charT, Traits>::char_type* s, streamsize n );
                    basic_istream& getline(typename basic_ios<charT, Traits>::char_type* s, streamsize n, typename basic_ios<charT, Traits>::char_type delim);

                    basic_istream& ignore(streamsize n = 1, typename basic_ios<charT, Traits>::int_type delim = Traits::eof());

                    typename basic_ios<charT, Traits>::int_type peek();

                    basic_istream& read(typename basic_ios<charT, Traits>::char_type* s, streamsize n);

                    streamsize readsome(typename basic_ios<charT, Traits>::char_type* s, streamsize n);

                    basic_istream& putback(typename basic_ios<charT, Traits>::char_type c);
                    basic_istream& unget();
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Positioning:
            
                public:
                    pos_type tellg();

                    basic_istream& seekg (pos_type pos);
                    basic_istream& seekg (off_type off, ios_base::seekdir way);
            //
            //////////////////////////////////////////////////////////////////////////////////////
            // Synchronization:
                
                public:
                    int sync();
            //
            //////////////////////////////////////////////////////////////////////////////////////                

        };
    #endif
    }

    #include "CPSTL_basic_istream.tpp"

#endif//CPSTL_ISTREAM_HEADER
