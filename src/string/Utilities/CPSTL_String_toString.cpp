#include "CPSTL_String_toString.h"

cpstd::string cpstd::to_string(int val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#else
    string result;
    bool isNegative = false;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
        val = -val;
    }

    // Special case for 0
    if (val == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (val > 0) {
        char digit = '0' + static_cast<char>(val % 10);
        result.push_back(digit);
        val /= 10;
    }

    // Add the negative sign if necessary
    if (isNegative) {
        result.push_back('-');
    }

    // Reverse the string to get the correct order
    size_t start = 0;
    size_t end = result.size() - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
#endif
}

cpstd::string cpstd::to_string(long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#else
    string result;
    bool isNegative = false;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
        val = -val;
    }

    // Special case for 0
    if (val == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (val > 0) {
        char digit = '0' + static_cast<char>(val % 10);
        result.push_back(digit);
        val /= 10;
    }

    // Add the negative sign if necessary
    if (isNegative) {
        result.push_back('-');
    }

    // Reverse the string to get the correct order
    size_t start = 0;
    size_t end = result.size() - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
#endif
}

cpstd::string cpstd::to_string(long long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#else
    string result;
    bool isNegative = false;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
        val = -val;
    }

    // Special case for 0
    if (val == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (val > 0) {
        char digit = '0' + static_cast<char>(val % 10);
        result.push_back(digit);
        val /= 10;
    }

    // Add the negative sign if necessary
    if (isNegative) {
        result.push_back('-');
    }

    // Reverse the string to get the correct order
    size_t start = 0;
    size_t end = result.size() - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
#endif
}

cpstd::string cpstd::to_string(unsigned val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
    string result;

    // Special case for 0
    if (val == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (val > 0) {
        char digit = '0' + static_cast<char>(val % 10);
        result.push_back(digit);
        val /= 10;
    }

    // Reverse the string to get the correct order
    size_t start = 0;
    size_t end = result.size() - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
}

cpstd::string cpstd::to_string(unsigned long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
    string result;

    // Special case for 0
    if (val == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (val > 0) {
        char digit = '0' + static_cast<char>(val % 10);
        result.push_back(digit);
        val /= 10;
    }

    // Reverse the string to get the correct order
    size_t start = 0;
    size_t end = result.size() - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
}

cpstd::string cpstd::to_string(unsigned long long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
    string result;

    // Special case for 0
    if (val == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (val > 0) {
        char digit = '0' + static_cast<char>(val % 10);
        result.push_back(digit);
        val /= 10;
    }

    // Reverse the string to get the correct order
    size_t start = 0;
    size_t end = result.size() - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
}

cpstd::string cpstd::to_string(float val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
    return cpstd::string("");
}

cpstd::string cpstd::to_string(double val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
    return cpstd::string("");
}

cpstd::string cpstd::to_string(long double val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
#endif
    return cpstd::string("");
}