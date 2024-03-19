#ifndef CPSTL_LOCALE_H
#define CPSTL_LOCALE_H

    #include <CPSTL_BuildSettings.h>
    #include <CPstring.h>


    namespace cpstd{
    #ifdef CPSTL_USING_STL
        using locale = std::locale;

        template <class charT>
        using collate = std::collate<charT>;

    #else
        /*
        class locale{
        public:
            typedef int category;

            static constexpr category none     = 0b00000000;
            static constexpr category all      = 0b00011111;
            static constexpr category ctype    = 0b00000001;
            static constexpr category monetary = 0b00000010;
            static constexpr category numeric  = 0b00000100;
            static constexpr category time     = 0b00001000;
            static constexpr category messages = 0b00010000;

            class facet {
            protected:
              explicit facet (size_t refs = 0);
              virtual ~facet();
              facet (const facet&) = delete;
              void operator= (const facet&) = delete;
            };

            class id {
            public:
                id();
                void operator= (const id&) = delete;
                id(const id&) = delete;
            };


        public:
            locale() noexcept;
            locale(const locale& x) noexcept;
            explicit locale(const char* std_name);
            explicit locale(const string& std_name);
            locale(const locale& x, const char* std_name, category cats);         
            locale(const locale& x, const string& std_name, category cats);

            template <class Facet>
            locale(const locale& x, const locale& y, category cats);

            locale(const locale& x, facet* f);

            ~locale();

            static const locale& classic();

            template <class Facet>
            locale combine(const locale& x) const;

            static locale global(const locale& loc);

            string name() const;

            bool operator!=(const locale& x) const;

            template <class charT, class Traits, class Allocator>
            bool operator()(const basic_string<charT,Traits,Allocator>& s1, const basic_string<charT,Traits,Allocator>& s2) const;

            const locale& operator=(const locale& x) noexcept;

            bool operator==(const locale& x) const;
        };

        template <class charT> 
        class collate : locale::facet{
        public:
            using char_type = charT;
            using string_type = cpstd::basic_string<charT>;

            explicit collate(size_t refs=0);
            int compare(const char_type* low1, const char_type* high1, const char_type* low2, const char_type* high2) const;
            string_type transform(const char_type* low, const char_type* high) const;
            long hash(const char_type* low, const char_type* high) const;

        protected:

            ~collate();

            virtual int do_compare(const char_type* low1, const char_type* high1, const char_type* low2, const char_type* high2) const;
            string_type do_transform(const char_type* low, const char_type* high) const;
            long do_hash(const char_type* low, const char_type* high) const;

        };

        // Explicit specialization for char
        template <>
        class collate<char> : public collate<char> {
        public:
            explicit collate(cpstd::size_t refs = 0) : collate<char>() {}
            int compare(const char* low1, const char* high1, const char* low2, const char* high2) const override;
            std::string transform(const char* low, const char* high) const override;
            long hash(const char* low, const char* high) const override;

        protected:
            ~collate() override;
        };

        template <>
        class collate<wchar_t> : public collate<wchar_t> {
        public:
            explicit collate(std::size_t refs = 0) : collate<wchar_t>() {}
            int compare(const wchar_t* low1, const wchar_t* high1, const wchar_t* low2, const wchar_t* high2) const override;
            std::wstring transform(const wchar_t* low, const wchar_t* high) const override;
            long hash(const wchar_t* low, const wchar_t* high) const override;

        protected:
            ~collate() override;
        };*/

    #endif
    }


#endif//CPSTL_LOCALE_H