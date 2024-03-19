#ifndef CPSTL_CHAR_TRAITS_H
#define CPSTL_CHAR_TRAITS_H

    #include <CPSTL_BuildSettings.h>

    namespace cpstd{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // char_traits

        #ifdef CPSTL_STRING_USING_STL_ALLOCATION

            template <typename charT>
            using char_traits = std::char_traits<charT>;
        #else
            template <class charT> 
            struct char_traits {};

            template <>
            struct char_traits<char> {
                using char_type = char;
                using int_type = int;
                //using off_type = streamoff;
                //using pos_type = streampos;
                using state_type = mbstate_t;

                static constexpr bool eq (char_type c1, char_type c2) noexcept{ return c1 == c2; }
                static constexpr bool lt(char_type c1, char_type c2) noexcept{ return c1 < c2; }
                static void assign(char_type& r, const char_type& c) noexcept{ r = c; }
                static constexpr int_type eof() noexcept{ return static_cast<int_type>(-1); }
                static constexpr int_type not_eof(int_type c) noexcept{ return (c != eof()) ? c : 0; }
                static constexpr char_type to_char_type(int_type c) noexcept{ return static_cast<char_type>(c); }
                static constexpr int_type to_int_type(char_type c) noexcept{ return static_cast<int_type>(c); }
                static constexpr bool eq_int_type(int_type x, int_type y) noexcept{ return x == y; }

                static size_t length(const char_type* str){
                    size_t  len = 0;
                    while (*str++ != '\0')
                        ++len;
                    return len;
                }


                static char_type* assign(char_type* p, size_t n, char_type c){
                    for (size_t i = 0; i < n; ++i) {
                        p[i] = c; // Assigns the character 'c' to the first 'n' characters pointed to by 'p'
                    }
                    return p;
                }

                static int_type compare(const char_type* p, const char_type* q, size_t n){
                    while (n--) {
                        if (*p != *q) return (*p < *q) ? -1 : 1; // Compares characters pointed by 'p' and 'q'
                        ++p; ++q;
                    }
                    return 0; // Characters are equal for the first 'n' characters
                }

                static const char_type* find(const char_type* p, size_t n, const char_type& c){
                    for (size_t i = 0; i < n; ++i) {
                        if (p[i] == c) {
                            return &p[i]; // Return a pointer to the first occurrence of c
                        }
                    }
                    return nullptr; // Return nullptr if c is not found within the first n characters of p
                }

                static char_type* move(char_type* dest, const char_type* src, size_t count){
                    memmove(dest, src, count * sizeof(char_type));
                    return dest;
                }

                static char_type* copy(char_type* dest, const char_type* src, size_t count){
                    memcpy(dest, src, count * sizeof(char_type));
                    return dest;
                }

            };
                
            template <>
            struct char_traits<wchar_t> {
                using char_type = wchar_t;
                using int_type = wint_t;
                //using off_type = streamoff;
                //using pos_type = streampos;
                using state_type = mbstate_t;

                static constexpr bool eq (char_type c1, char_type c2) noexcept{ return c1 == c2; }
                static constexpr bool lt(char_type c1, char_type c2) noexcept{ return c1 < c2; }
                static void assign(char_type& r, const char_type& c) noexcept{ r = c; }
                static constexpr int_type eof() noexcept{ return static_cast<int_type>(-1); }
                static constexpr int_type not_eof(int_type c) noexcept{ return (c != eof()) ? c : 0; }
                static constexpr char_type to_char_type(int_type c) noexcept{ return static_cast<char_type>(c); }
                static constexpr int_type to_int_type(char_type c) noexcept{ return static_cast<int_type>(c); }
                static constexpr bool eq_int_type(int_type x, int_type y) noexcept{ return x == y; }

                static size_t length(const char_type* str){
                    size_t  len = 0;
                    while (*str++ != L'\0')
                        ++len;
                    return len;
                }


                static char_type* assign(char_type* p, size_t n, char_type c){
                    for (size_t i = 0; i < n; ++i) {
                        p[i] = c; // Assigns the character 'c' to the first 'n' characters pointed to by 'p'
                    }
                    return p;
                }

                static int_type compare(const char_type* p, const char_type* q, size_t n){
                    while (n--) {
                        if (*p != *q) return (*p < *q) ? -1 : 1; // Compares characters pointed by 'p' and 'q'
                        ++p; ++q;
                    }
                    return 0; // Characters are equal for the first 'n' characters
                }

                static const char_type* find(const char_type* p, size_t n, const char_type& c){
                    for (size_t i = 0; i < n; ++i) {
                        if (p[i] == c) {
                            return &p[i]; // Return a pointer to the first occurrence of c
                        }
                    }
                    return nullptr; // Return nullptr if c is not found within the first n characters of p
                }

                static char_type* move(char_type* dest, const char_type* src, size_t count){
                    memmove(dest, src, count * sizeof(char_type));
                    return dest;
                }

                static char_type* copy(char_type* dest, const char_type* src, size_t count){
                    memcpy(dest, src, count * sizeof(char_type));
                    return dest;
                }
            };

            template <>
            struct char_traits<char16_t> {
                using char_type = char16_t;
                using int_type = uint_least16_t;
                //using off_type = u16streamoff; // Type that behaves like streamoff for char16_t
                //using pos_type = u16streampos; // Type that behaves like streampos for char16_t
                using state_type = mbstate_t;

                static constexpr bool eq (char_type c1, char_type c2) noexcept{ return c1 == c2; }
                static constexpr bool lt(char_type c1, char_type c2) noexcept{ return c1 < c2; }
                static void assign(char_type& r, const char_type& c) noexcept{ r = c; }
                static constexpr int_type eof() noexcept{ return static_cast<int_type>(-1); }
                static constexpr int_type not_eof(int_type c) noexcept{ return (c != eof()) ? c : 0; }
                static constexpr char_type to_char_type(int_type c) noexcept{ return static_cast<char_type>(c); }
                static constexpr int_type to_int_type(char_type c) noexcept{ return static_cast<int_type>(c); }
                static constexpr bool eq_int_type(int_type x, int_type y) noexcept{ return x == y; }

                static size_t length(const char_type* str){
                    size_t  len = 0;
                    while (*str++ != u'\0')
                        ++len;
                    return len;
                }


                static char_type* assign(char_type* p, size_t n, char_type c){
                    for (size_t i = 0; i < n; ++i) {
                        p[i] = c; // Assigns the character 'c' to the first 'n' characters pointed to by 'p'
                    }
                    return p;
                }

                static int_type compare(const char_type* p, const char_type* q, size_t n){
                    while (n--) {
                        if (*p != *q) return (*p < *q) ? -1 : 1; // Compares characters pointed by 'p' and 'q'
                        ++p; ++q;
                    }
                    return 0; // Characters are equal for the first 'n' characters
                }

                static const char_type* find(const char_type* p, size_t n, const char_type& c){
                    for (size_t i = 0; i < n; ++i) {
                        if (p[i] == c) {
                            return &p[i]; // Return a pointer to the first occurrence of c
                        }
                    }
                    return nullptr; // Return nullptr if c is not found within the first n characters of p
                }

                static char_type* move(char_type* dest, const char_type* src, size_t count){
                    memmove(dest, src, count * sizeof(char_type));
                    return dest;
                }

                static char_type* copy(char_type* dest, const char_type* src, size_t count){
                    memcpy(dest, src, count * sizeof(char_type));
                    return dest;
                }
            };

            // Specialization for char32_t
            template <>
            struct char_traits<char32_t> {
                using char_type = char32_t;
                using int_type = uint_least32_t;
                //using off_type = u32streamoff; // Type that behaves like streamoff for char32_t
                //using pos_type = u32streampos; // Type that behaves like streampos for char32_t
                using state_type = mbstate_t;

                static constexpr bool eq (char_type c1, char_type c2) noexcept{ return c1 == c2; }
                static constexpr bool lt(char_type c1, char_type c2) noexcept{ return c1 < c2; }
                static void assign(char_type& r, const char_type& c) noexcept{ r = c; }
                static constexpr int_type eof() noexcept{ return static_cast<int_type>(-1); }
                static constexpr int_type not_eof(int_type c) noexcept{ return (c != eof()) ? c : 0; }
                static constexpr char_type to_char_type(int_type c) noexcept{ return static_cast<char_type>(c); }
                static constexpr int_type to_int_type(char_type c) noexcept{ return static_cast<int_type>(c); }
                static constexpr bool eq_int_type(int_type x, int_type y) noexcept{ return x == y; }

                static size_t length(const char_type* str){
                    size_t  len = 0;
                    while (*str++ != U'\0')
                        ++len;
                    return len;
                }


                static char_type* assign(char_type* p, size_t n, char_type c){
                    for (size_t i = 0; i < n; ++i) {
                        p[i] = c; // Assigns the character 'c' to the first 'n' characters pointed to by 'p'
                    }
                    return p;
                }

                static int_type compare(const char_type* p, const char_type* q, size_t n){
                    while (n--) {
                        if (*p != *q) return (*p < *q) ? -1 : 1; // Compares characters pointed by 'p' and 'q'
                        ++p; ++q;
                    }
                    return 0; // Characters are equal for the first 'n' characters
                }

                static const char_type* find(const char_type* p, size_t n, const char_type& c){
                    for (size_t i = 0; i < n; ++i) {
                        if (p[i] == c) {
                            return &p[i]; // Return a pointer to the first occurrence of c
                        }
                    }
                    return nullptr; // Return nullptr if c is not found within the first n characters of p
                }

                static char_type* move(char_type* dest, const char_type* src, size_t count){
                    memmove(dest, src, count * sizeof(char_type));
                    return dest;
                }

                static char_type* copy(char_type* dest, const char_type* src, size_t count){
                    memcpy(dest, src, count * sizeof(char_type));
                    return dest;
                }
            };
        #endif
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    }
    
#endif//CPSTL_CHAR_TRAITS_H