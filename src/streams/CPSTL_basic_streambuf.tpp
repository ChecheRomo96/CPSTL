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
    //
    ////////////////////////////////////////////////////////////////////////////////////
    // Buffer management and positioning:

        template <class charT, class traits>
        basic_streambuf<charT, traits>* basic_streambuf<charT, traits>::pubsetbuf(char_type* s, streamsize n){
            return setbuf(s,n);
        }

        template <class charT, class traits>
        pos_type basic_streambuf<charT, traits>::pubseekoff(off_type off, ios_base::seekdir way, ios_base::openmode which){
            return seekoff(off, way, which);
        }

        template <class charT, class traits>
        pos_type basic_streambuf<charT, traits>::pubseekpos(pos_type pos, ios_base::openmode which){
            return seekpos(pos, which);
        }

        template <class charT, class traits>
        int basic_streambuf<charT, traits>::pubsync(){
            return sync();
        }
    //
    ////////////////////////////////////////////////////////////////////////////////////
    // Buffer management and positioning:


    //
    ////////////////////////////////////////////////////////////////////////////////////
    // Buffer management and positioning:

#endif