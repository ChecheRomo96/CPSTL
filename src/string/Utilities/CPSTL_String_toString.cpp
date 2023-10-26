#include "CPSTL_String_toString.h"

cpstd::string cpstd::to_string(int val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(long long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(unsigned val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(unsigned long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(unsigned long long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(float val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(double val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}

cpstd::string cpstd::to_string(long double val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
}