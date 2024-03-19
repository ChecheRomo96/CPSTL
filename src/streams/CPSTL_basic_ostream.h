#ifndef CPSTL_OSTREAM_HEADER
#define CPSTL_OSTREAM_HEADER


    #include <CPSTL_BuildSettings.h>

    #include "CPSTL_basic_ios.h"

    #if __has_include(<ostream>)
        #include <ios>
        #include <ostream>
    #endif
    
    namespace cpstd{

        #if __has_include(<ostream>)
            
            template <class charT, class traits = char_traits<charT> >
            using basic_ostream = std::basic_ostream<charT, traits>;

        #else

        template <class charT, class traits>
        class basic_ostream : virtual public basic_ios<charT, traits> {

                //////////////////////////////////////////////////////////////////////////////////////
                // types
                
                    using char_type = charT;
                    using traits_type = traits;
                    using int_type = typename traits_type::int_type;
                    using pos_type = typename traits_type::pos_type;
                    using off_type = typename traits_type::off_type;
                // 
                //////////////////////////////////////////////////////////////////////////////////////
                // Sentry Class

                    public:

                        class sentry {
                        public:
                          explicit sentry (basic_ostream& os);
                          ~sentry();
                          explicit operator bool() const;
                          sentry (const sentry&) = delete;
                          sentry& operator= (const sentry&) = delete;
                        };
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // Constructors and destructor

                    public:
                        explicit basic_ostream(basic_streambuf<char_type,traits_type>* sb);

                        // Deleted copy constructor
                        basic_ostream(const basic_ostream&) = delete;

                        // Destructor (no implementation provided)
                        virtual ~basic_ostream();

                    protected:
                        // Move constructor
                        basic_ostream(basic_ostream&& x);
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // Move assignment
                
                    protected:

                        basic_ostream& operator= (const basic_ostream&) = delete;
                        basic_ostream& operator= (basic_ostream&& rhs);
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // swap
                
                    protected:

                        void swap (basic_ostream& x);
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // formatted output
                    
                    public:

                        basic_ostream& operator<<(bool val);
                        basic_ostream& operator<<(short val);
                        basic_ostream& operator<<(unsigned short val);
                        basic_ostream& operator<<(int val);
                        basic_ostream& operator<<(unsigned int val);
                        basic_ostream& operator<<(long val);
                        basic_ostream& operator<<(unsigned long val);
                        basic_ostream& operator<<(long long val);
                        basic_ostream& operator<<(unsigned long long val);
                        basic_ostream& operator<<(float val);
                        basic_ostream& operator<<(double val);
                        basic_ostream& operator<<(long double val);
                        basic_ostream& operator<<(void* val);
                        basic_ostream& operator<<(basic_streambuf<char_type, traits_type>* sb);
                        basic_ostream& operator<<(basic_ostream& (*pf)(basic_ostream&));
                        basic_ostream& operator<<(basic_ios<char_type, traits_type>& (*pf)(basic_ios<char_type, traits_type>&));
                        basic_ostream& operator<<(ios_base& (*pf)(ios_base&));
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // Unformatted output:
                    
                    public:
                
                        basic_ostream& put (char_type c);
                        basic_ostream& write (const char_type* s, streamsize n);
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // Positioning:
                    
                    public:
                
                        pos_type tellp();
                        
                        basic_ostream& seekp (pos_type pos);
                        basic_ostream& seekp (off_type off, ios_base::seekdir way);
                //
                //////////////////////////////////////////////////////////////////////////////////////
                // Synchronization:
                    
                    public:
                
                        basic_ostream& flush();
                //
                //////////////////////////////////////////////////////////////////////////////////////
                
        };

        #endif
    }

    #include "CPSTL_basic_ostream.tpp"

#endif//CPSTL_OSTREAM_HEADER