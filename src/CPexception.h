#ifndef CPSTL_EXCEPTION_H
#define CPSTL_EXCEPTION_H

    #include <CPSTL_BuildSettings.h>

    #if defined(CPSTL_USING_STL)
        #include <exception>
        #include <new>
        #include <stdexcept>
    #endif

    //! @file CPexception.h
    //! @brief Standard exception hierarchy.
    //!
    //! In STL mode these are the `std` classes. Otherwise CPSTL provides the
    //! same names with a fixed, allocation-free message: a string literal
    //! passed to the constructor is kept by pointer, so it must outlive the
    //! exception (string literals always do).
    //!
    //! CPSTL containers never throw in either mode on their own; these types
    //! exist for code that wants the standard names on targets without
    //! `<stdexcept>`.

    namespace cpstd {

    #if defined(CPSTL_USING_STL)

        using exception = std::exception;
        using logic_error = std::logic_error;
        using out_of_range = std::out_of_range;
        using length_error = std::length_error;
        using bad_alloc = std::bad_alloc;

    #else

        class exception {
        public:
            exception() noexcept {}
            exception(const exception&) noexcept = default;
            exception& operator=(const exception&) noexcept = default;
            virtual ~exception() {}
            virtual const char* what() const noexcept { return "cpstd::exception"; }
        };

        class bad_alloc : public exception {
        public:
            const char* what() const noexcept override { return "cpstd::bad_alloc"; }
        };

        class logic_error : public exception {
        public:
            explicit logic_error(const char* message) noexcept
                : _Message(message != nullptr ? message : "cpstd::logic_error") {}
            const char* what() const noexcept override { return _Message; }

        private:
            const char* _Message;
        };

        class out_of_range : public logic_error {
        public:
            explicit out_of_range(const char* message = "cpstd::out_of_range") noexcept
                : logic_error(message) {}
        };

        class length_error : public logic_error {
        public:
            explicit length_error(const char* message = "cpstd::length_error") noexcept
                : logic_error(message) {}
        };

    #endif

    }

#endif//CPSTL_EXCEPTION_H
