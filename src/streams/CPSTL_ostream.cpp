#include <CPostream.h>

cpstd::ostream& cpstd::endl(cpstd::ostream& os){
#if __has_include(<ostream>)
    return std::endl(os);
#else
    os.put(os.widen('\n')); // This mimics the behavior of std::endl
    os.flush(); // Ensure the output is flushed
    return os;
#endif
}

cpstd::ostream& cpstd::ends(cpstd::ostream& os){
#if __has_include(<ostream>)
    return std::ends(os);
#else
    os.put(os.widen('\0')); // This mimics the behavior of std::ends
    os.flush(); // Ensure the output is flushed
    return os;
#endif
}

cpstd::ostream& cpstd::flush(cpstd::ostream& os){
#if __has_include(<ostream>)
    return std::flush(os);
#else
    os.flush();
    return os;
#endif
}