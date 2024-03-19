#include "CPSTL_basic_streambuf.h"

#if !__has_include(<streambuf>)

    ////////////////////////////////////////////////////////////////////////////////////
    // Constructors and destructor

        template <class charT, class traits>
        basic_streambuf<charT, traits>::basic_streambuf<charT, traits>()
        : eback_(nullptr), gptr_(nullptr), egptr_(nullptr), pbase_(nullptr), pptr_(nullptr), epptr_(nullptr) {

        }

        template <class charT, class traits>
        basic_streambuf<charT, traits>::basic_streambuf(const basic_streambuf<charT, traits>& x)
        eback_(x.eback_), gptr_(x.gptr_), egptr_(x.egptr_), pbase_(x.pbase_), pptr_(x.pptr_), epptr_(x.epptr_) {
        
        }


#endif