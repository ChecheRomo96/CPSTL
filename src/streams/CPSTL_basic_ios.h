#ifndef CPSTL_BASIC_IOS_H
#define CPSTL_BASIC_IOS_H

    #include <CPSTL_BuildSettings.h>

    #include <CPvector.h>

    #include "CPSTL_ios_base.h"
    #include "CPSTL_basic_streambuf.h"

    namespace cpstd{
    #if __has_include(<ios>)

        template <class charT, class traits = cpstd::char_traits<charT> >
        using basic_ios = std::basic_ios<charT, traits>;

    #else

        template <class charT, class traits = cpstd::char_traits<charT> >
        class basic_ostream;

        template <class charT, class traits = cpstd::char_traits<charT>>
        class basic_istream;

        template <class charT, class traits>
        class basic_ios : virtual public cpstd::ios_base{
        public:
            using char_type = charT;
            using traits_type = traits;
            using ostream_type = cpstd::basic_ostream<char_type, traits_type>;
            using int_type = typename traits_type::int_type;
            using pos_type = typename traits_type::pos_type;
            using off_type = typename traits_type::off_type;

        protected:
            iostate state_;
            iostate exceptions_;
            char_type fill_;
            ostream_type* tie_;

            
            basic_streambuf<charT, traits>* streambuf_;
            cpstd::vector<void*> _internalBuffer; // Define _internalBuffer here
            cpstd::vector<event_callback> _CallbackVector; // Define _CallbackVector here


        public:
            explicit basic_ios(cpstd::basic_streambuf<char_type, traits_type>* sb);
            virtual ~basic_ios();

        protected: 
            basic_ios();
            basic_ios(const basic_ios&) = delete; 
            basic_ios& operator= (const basic_ios&) = delete;

        public:

            // State flag functions:

                bool good() const;
                bool eof() const;
                bool fail() const;
                bool bad() const;
                bool operator!() const;
                explicit operator bool() const;
                iostate rdstate() const;
                void setstate (iostate state);
                void clear (iostate state = goodbit);

            // Formatting:

                basic_ios& copyfmt (const basic_ios& rhs);
                char_type fill() const;
                char_type fill (char_type fillch);

            // Other:

                iostate exceptions() const;
                void exceptions (iostate except);

                // locale imbue (const locale& loc){
                //
                //}
                
                basic_ostream<char_type,traits_type>* tie() const;
                basic_ostream<char_type,traits_type>* tie (basic_ostream<char_type,traits_type>* tiestr);

                basic_streambuf<char_type,traits_type>* rdbuf() const;
                basic_streambuf<char_type,traits_type>* rdbuf (basic_streambuf<char_type,traits_type>* sb);
                
                //char narrow (char_type wc, char dfault) const;
                //char_type widen (char c) const;
            
            protected:
                
                //Protected member functions

                void init (basic_streambuf<char_type,traits_type>* sb);
                void move (basic_ios&  x);
                void move (basic_ios&& x);
                void swap (basic_ios& x) noexcept;
                void set_rdbuf(basic_streambuf<char_type,traits_type>* sb);
        };
    
    #endif
    }

    #include "CPSTL_basic_ios.tpp"

#endif//CPSTL_BASIC_IOS_H