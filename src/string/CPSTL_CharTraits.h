#ifndef CPSTL_CHARTRAITS_CLASS_H
#define CPSTL_CHARTRAITS_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPiterator.h>
    #include <CPmemory.h>
    #include <utility/CPSTL_types.h>
    #include <utility/CPSTL_Move.h>
    



    #ifdef CPSTL_USING_STL
        #include <string>
        #include <stdexcept>
        #include <cstdarg>
        #include <cstdio>
    #endif  


    namespace cpstd{  

        #ifdef CPSTL_USING_STL

            
            template <typename CharT>
            using char_traits = std::char_traits<CharT>;


        #else

            
            template <typename CharT>
            struct char_traits {
                using char_type = CharT;
                using int_type = int;
                using off_type = cpstd::ptrdiff_t;  // placeholder
                using pos_type = cpstd::size_t;     // placeholder
                using state_type = int;             // placeholder

                static bool eq(const char_type& c1, const char_type& c2);

                static bool lt(const char_type& c1, const char_type& c2);

                static cpstd::size_t length(const char_type* str);

                static void assign(char_type& c1, const char_type& c2);

                static char_type* assign(char_type* dest, cpstd::size_t count, char_type ch);
                
                static int_type compare(const char_type* str1, const char_type* str2, cpstd::size_t count);

                static const char_type* find(const char_type* s, cpstd::size_t count, const char_type& ch);

                static char_type* move(char_type* dest, const char_type* src, cpstd::size_t count);

                static char_type* copy(char_type* dest, const char_type* src, cpstd::size_t count);

                static int_type eof();

                static int_type not_eof(const int_type& c);

                static char_type to_char_type(const int_type& c);

                static int_type to_int_type(const char_type& ch);
                
                static bool eq_int_type(const int_type& c1, const int_type& c2);
            };

        #endif
    }

    #include "CPSTL_CharTraits.tpp"

#endif //CPSTL_CHARTRAITS_CLASS_H