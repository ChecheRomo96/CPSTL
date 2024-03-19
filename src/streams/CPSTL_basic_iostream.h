#ifndef CPSTL_IOSTREAM_H
#define CPSTL_IOSTREAM_H

    #include <CPSTL_BuildSettings.h>
    #include <CPstring.h>

    #include <CPostream.h>
    #include <CPistream.h>

    #ifdef CPSTL_USING_STL
        #include <ios>
    #endif
    
    namespace cpstd{
    #if __has_include(<istream>)
        template <class charT, class traits = char_traits<charT> >
        using basic_iostream = std::basic_iostream<charT, traits>;
    #else
        template <typename CharT, typename Traits>
        class basic_iostream : public cpstd::basic_istream<CharT, Traits>,
                               public cpstd::basic_ostream<CharT, Traits> {
        public:
            // Constructors, member functions, and other declarations

            explicit basic_iostream (basic_streambuf<char_type,traits_type>* sb);
            basic_iostream& (const basic_iostream&) = delete;

        protected: 
            basic_iostream& (basic_iostream&& x);

        public:
            virtual ~basic_iostream();

        protected:
            basic_iostream& operator= (const basic_iostream&) = delete;
            basic_iostream& operator= (basic_iostream&& rhs);
            void swap (basic_iostream& x);
        };
    #endif
    }

#endif