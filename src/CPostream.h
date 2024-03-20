#ifndef CPSTL_OSTREAM_H
#define CPSTL_OSTREAM_H

    #include <CPSTL_BuildSettings.h>
    #include <CPios.h>


    #include "streams/CPSTL_basic_ostream.h"


    namespace cpstd{
    #if __has_include(<ostream>)
        using ostream = std::ostream;
        using wostream = std::wostream;
    #else
        using ostream = cpstd::basic_ostream<char>;
        using wostream = cpstd::basic_ostream<wchar_t>;
    #endif


        ostream& endl (ostream& os);

        template <class charT, class traits>
        cpstd::basic_ostream<charT, traits>& endl(cpstd::basic_ostream<charT, traits>& os) {
            // Insert a newline character into the stream
            os.put(os.widen('\n'));

            // Flush the stream to ensure the output is displayed
            os.flush();

            // Return the reference to the same output stream
            return os;
        }

        ostream& ends (ostream& os);

        template <class charT, class traits>
        cpstd::basic_ostream<charT, traits>& ends(cpstd::basic_ostream<charT, traits>& os) {
            os.put(os.widen('\0'));
            os.flush();
            return os;
        }

        ostream& flush (ostream& os);
        
        template <class charT, class traits>
        cpstd::basic_ostream<charT, traits>& flush(cpstd::basic_ostream<charT, traits>& os) {
            os.flush();
            return os;
        }
    }

    

#endif//CPSTL_OSTREAM_H