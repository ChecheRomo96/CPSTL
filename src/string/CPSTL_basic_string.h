#ifndef CPSTL_BASIC_STRING_CLASS_H
#define CPSTL_BASIC_STRING_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPiterator.h>
    #include <CPmemory.h>
    #include <utility/CPSTL_types.h>
    #include <utility/CPSTL_Move.h>
    

    #if defined(CPSTL_STRING_EXCEPTIONS_ENABLED) && defined(CPSTL_EXCEPTIONS_ENABLED)
        #include <CPexception.h>           
    #endif  


    #ifdef CPSTL_USING_STL
        #include <string>
    #endif  

    #include "CPSTL_CharTraits.h"


    namespace cpstd{  

        #ifdef CPSTL_USING_STL

            template < class CharT, class Traits = std::char_traits<CharT>, class Alloc = std::allocator<CharT> >
            using basic_string = std::basic_string< CharT, Traits, Alloc>;

        #else

            
            template < class CharT, class Traits = cpstd::char_traits<CharT>, class Alloc = cpstd::allocator<CharT> >
            class basic_string {
            public:
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Typdefs and aliases
                    
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Value Types
                            
                            using traits_type       = Traits;
                            using allocator_type    = Alloc;
                            using value_type        = typename Traits::char_type;
                            using reference         = value_type&;
                            using const_reference   = const value_type&;
                            using pointer           = typename cpstd::allocator_traits<allocator_type>::pointer;
                            using const_pointer     = typename cpstd::allocator_traits<allocator_type>::const_pointer;
                            using size_type         = typename cpstd::allocator_traits<allocator_type>::size_type;
                            using difference_type   = typename cpstd::allocator_traits<allocator_type>::difference_type;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Iterator Types
                            
                            using iterator               = pointer;
                            using const_iterator         = const_pointer;
                            using reverse_iterator       = cpstd::reverse_iterator<iterator>;
                            using const_reverse_iterator = cpstd::reverse_iterator<const_iterator>;
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                static constexpr size_type npos = static_cast<size_type>(-1);

            private:
            
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Instance Variables

                        pointer        _buffer;
                        size_type      _size;
                        size_type      _capacity;
                        allocator_type _alloc;
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


            private:
                void InitEmpty();
                void DestroyBuffer();
                void EnsureCapacity(size_type required);
                void AssignFromBuffer(const_pointer s, size_type n);
                void AssignFill(size_type n, value_type ch);

            public:

                // Constructors
                    basic_string();
                    explicit basic_string(const allocator_type& alloc);

                    basic_string(const basic_string& str);
                    basic_string(const basic_string& str, const allocator_type& alloc);

                    basic_string(const basic_string& str, size_type pos, size_type len = npos, const allocator_type& alloc = allocator_type());

                    basic_string(const CharT* s, const allocator_type& alloc = allocator_type());
                    basic_string(const CharT* s, size_type n, const allocator_type& alloc = allocator_type());

                    basic_string(size_type n, CharT c,
                                const allocator_type& alloc = allocator_type());

                    template <class InputIterator>
                    basic_string(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

                    basic_string(cpstd::initializer_list<CharT> il, const allocator_type& alloc = allocator_type());

                    basic_string(basic_string&& str) noexcept;
                    basic_string(basic_string&& str, const allocator_type& alloc);

				// Destructor

                    ~basic_string();

                // Iterators

                    iterator begin() noexcept;
                    const_iterator begin() const noexcept;

                    iterator end() noexcept;
                    const_iterator end() const noexcept;

                    reverse_iterator rbegin() noexcept;
                    const_reverse_iterator rbegin() const noexcept;

                    reverse_iterator rend() noexcept;
                    const_reverse_iterator rend() const noexcept;

                    const_iterator cbegin() const noexcept;
                    
                    const_iterator cend() const noexcept;
                    
                    const_reverse_iterator crbegin() const noexcept;
                    
                    const_reverse_iterator crend() const noexcept;

                // Capacity

                    size_type size() const noexcept;

                    size_type length() const noexcept;

                    size_type max_size() const noexcept;

                    void resize(size_type n);
                    void resize(size_type n, CharT c);

                    size_type capacity() const noexcept;

                    void reserve(size_type n = 0);

                    void clear() noexcept;

                    bool empty() const noexcept;

                    void shrink_to_fit();

                // Element Access

                    reference operator[] (size_type pos);
                    const_reference operator[] (size_type pos) const;

                    reference at(size_type pos);
                    const_reference at(size_type pos) const;

                    CharT& back();
                    const CharT& back() const;

                    CharT& front();
                    const CharT& front() const;

                // Modifiers

                    basic_string& operator+= (const basic_string& str);
                    basic_string & operator+= (const CharT* s);
                    basic_string& operator+= (CharT c);
                    basic_string& operator+= (cpstd::initializer_list<CharT> il);

                    basic_string& append(const basic_string& str);
                    basic_string& append(const basic_string& str, size_type subpos, size_type sublen = npos);
                    basic_string & append(const CharT* s);
                    basic_string& append(const CharT* s, size_type n);
                    basic_string& append(size_type n, CharT c);
                    template <class InputIterator>   basic_string& append(InputIterator first, InputIterator last);
                    basic_string& append(cpstd::initializer_list<CharT> il);

                    void push_back(CharT c);

                    basic_string& assign(const basic_string& str);
                    basic_string& assign(const basic_string& str, size_type subpos, size_type sublen = npos);
                    basic_string & assign(const CharT* s);
                    basic_string& assign(const CharT* s, size_type n);
                    basic_string& assign(size_type n, CharT c);
                    template <class InputIterator>   basic_string& assign(InputIterator first, InputIterator last);
                    basic_string& assign(cpstd::initializer_list<CharT> il);
                    basic_string& assign(basic_string&& str) noexcept;

                    basic_string& insert(size_type pos, const basic_string& str);
                    basic_string& insert(size_type pos, const basic_string& str, size_type subpos, size_type sublen = npos);
                    basic_string & insert(size_type pos, const CharT* s);
                    basic_string& insert(size_type pos, const CharT* s, size_type n);
                    basic_string& insert(size_type pos, size_type n, CharT c);
                    iterator insert(const_iterator p, size_type n, CharT c);
                    iterator insert(const_iterator p, CharT c);
                    template <class InputIterator>
                    iterator insert(iterator p, InputIterator first, InputIterator last);
                    basic_string& insert(const_iterator p, cpstd::initializer_list<CharT> il);

                    basic_string& erase(size_type pos = 0, size_type len = npos);
                    iterator erase(const_iterator p);
                    iterator erase(const_iterator first, const_iterator last);

                    basic_string& replace(size_type pos, size_type len, const basic_string& str);
                    basic_string& replace(const_iterator i1, const_iterator i2, const basic_string& str);
                    basic_string& replace(size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen);
                    basic_string & replace(size_type pos, size_type len, const CharT * s);
                    basic_string& replace(const_iterator i1, const_iterator i2, const CharT* s);
                    basic_string& replace(size_type pos, size_type len, const CharT* s, size_type n);
                    basic_string& replace(const_iterator i1, const_iterator i2, const CharT* s, size_type n);
                    basic_string& replace(size_type pos, size_type len, size_type n, CharT c);
                    basic_string& replace(const_iterator i1, const_iterator i2, size_type n, CharT c);
                    template <class InputIterator>  basic_string& replace(const_iterator i1, const_iterator i2, InputIterator first, InputIterator last);
                    basic_string& replace(const_iterator i1, const_iterator i2, cpstd::initializer_list<CharT> il);

                    void swap(basic_string& str);

                    void pop_back();

                // String Operations

                    const CharT* c_str() const noexcept;

                    const CharT* data() const noexcept;

                    allocator_type get_allocator() const noexcept;

                    size_type copy(CharT* s, size_type len, size_type pos = 0) const;

                    size_type find(const basic_string& str, size_type pos = 0) const noexcept;
                    size_type find(const CharT * s, size_type pos = 0) const;
                    size_type find(const CharT* s, size_type pos, size_type n) const;
                    size_type find(CharT c, size_type pos = 0) const noexcept;

                    size_type rfind(const basic_string& str, size_type pos = npos) const noexcept;
                    size_type rfind(const CharT * s, size_type pos = npos) const;
                    size_type rfind(const CharT* s, size_type pos, size_type n) const;
                    size_type rfind(CharT c, size_type pos = npos) const noexcept;

                    size_type find_first_of(const basic_string& str, size_type pos = 0) const noexcept;
                    size_type find_first_of(const CharT * s, size_type pos = 0) const;
                    size_type find_first_of(const CharT* s, size_type pos, size_type n) const;
                    size_type find_first_of(CharT c, size_type pos = 0) const noexcept;

                    size_type find_last_of(const basic_string& str, size_type pos = npos) const noexcept;
                    size_type find_last_of(const CharT * s, size_type pos = npos) const;
                    size_type find_last_of(const CharT* s, size_type pos, size_type n) const;
                    size_type find_last_of(CharT c, size_type pos = npos) const noexcept;

                    size_type find_first_not_of(const basic_string& str, size_type pos = 0) const noexcept;
                    size_type find_first_not_of(const CharT * s, size_type pos = 0) const;
                    size_type find_first_not_of(const CharT* s, size_type pos, size_type n) const;
                    size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept;

                    size_type find_last_not_of(const basic_string& str, size_type pos = npos) const noexcept;
                    size_type find_last_not_of(const CharT * s, size_type pos = npos) const;
                    size_type find_last_not_of(const CharT* s, size_type pos, size_type n) const;
                    size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept;

                    basic_string substr(size_type pos = 0, size_type len = npos) const;

                    int compare(const basic_string& str) const noexcept;
                    int compare(size_type pos, size_type len, const basic_string& str) const;int compare(size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen = npos) const;
                    int compare(const CharT * s) const;int compare(size_type pos, size_type len, const CharT* s) const;
                    int compare(size_type pos, size_type len, const CharT* s, size_type n) const;

                


            };

            // Non-member function overloads

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (basic_string<CharT, Traits, Alloc>&& lhs, basic_string<CharT, Traits, Alloc>&& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (basic_string<CharT, Traits, Alloc>&& lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (const basic_string<CharT, Traits, Alloc>& lhs, basic_string<CharT, Traits, Alloc>&& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (basic_string<CharT, Traits, Alloc>&& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (const CharT* lhs, basic_string<CharT, Traits, Alloc>&& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (const basic_string<CharT, Traits, Alloc>& lhs, CharT rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (basic_string<CharT, Traits, Alloc>&& lhs, CharT rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (CharT lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            basic_string<CharT, Traits, Alloc> operator+ (CharT lhs, basic_string<CharT, Traits, Alloc>&& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator== (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept;

            template <class CharT, class Traits, class Alloc>
            bool operator== (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator== (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator!= (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept;

            template <class CharT, class Traits, class Alloc>
            bool operator!= (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator!= (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator<  (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept;

            template <class CharT, class Traits, class Alloc>
            bool operator<  (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator<  (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator<= (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept;

            template <class CharT, class Traits, class Alloc>
            bool operator<= (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator<= (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator>  (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept;

            template <class CharT, class Traits, class Alloc>
            bool operator>  (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator>  (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator>= (const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept;

            template <class CharT, class Traits, class Alloc>
            bool operator>= (const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs);

            template <class CharT, class Traits, class Alloc>
            bool operator>= (const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs);

            template <class CharT, class Traits, class Alloc>
            void swap(basic_string<CharT, Traits, Alloc>& x, basic_string<CharT, Traits, Alloc>& y);

            //template <class CharT, class Traits, class Alloc>
            //basic_istream<CharT, Traits>& operator>> (basic_istream<CharT, Traits>& is, basic_string<CharT, Traits, Alloc>& str);

            //template <class CharT, class Traits, class Alloc>
            //basic_ostream<CharT, Traits>& operator<< (basic_ostream<CharT, Traits>& os, const basic_string<CharT, Traits, Alloc>& str);

            //template <class CharT, class Traits, class Alloc>
            //basic_istream<CharT, Traits>& getline(basic_istream<CharT, Traits>& is, basic_string<CharT, Traits, Alloc>& str, CharT delim);

            //template <class CharT, class Traits, class Alloc>
            //basic_istream<CharT, Traits>& getline(basic_istream<CharT, Traits>&& is, basic_string<CharT, Traits, Alloc>& str, CharT delim);

            //template <class CharT, class Traits, class Alloc>
            //basic_istream<CharT, Traits>& getline(basic_istream<CharT, Traits>& is, basic_string<CharT, Traits, Alloc>& str);

            //template <class CharT, class Traits, class Alloc>
            //basic_istream<CharT, Traits>& getline(basic_istream<CharT, Traits>&& is, basic_string<CharT, Traits, Alloc>& str);

           

        #endif
    }

    #include "CPSTL_basic_string.tpp"

#endif //CPSTL_BASIC_STRING_CLASS_H