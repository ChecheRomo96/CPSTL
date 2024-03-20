#include <CPistream.h>

cpstd::istream& cpstd::ws(cpstd::istream& is){
#if __has_include(<istream>)
    return std::ws(is);
#else
    while (std::isspace(is.peek(), is.getloc())){
        is.ignore();
    }
    return is;
#endif
}  