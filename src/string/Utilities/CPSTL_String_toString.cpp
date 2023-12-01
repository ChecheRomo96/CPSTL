#include "CPSTL_String_toString.h"

cpstd::string cpstd::to_string(int val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
    string result;
    bool isNegative = false;
    unsigned value = (val>0)?val:-1*val;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
    }

    // Special case for 0
    if (value == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (value > 0) {
        char digit = '0' + static_cast<char>(value % 10);
        result.push_back(digit);
        value /= 10;
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
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
    string result;
    bool isNegative = false;
    unsigned long value = (val>0)?val:-1*val;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
    }

    // Special case for 0
    if (value == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (value > 0) {
        char digit = '0' + static_cast<char>(value % 10);
        result.push_back(digit);
        value /= 10;
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
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
    string result;
    bool isNegative = false;
    unsigned long long value = (val>0)?val:-1*val;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
    }

    // Special case for 0
    if (value == 0) {
        result.push_back('0');
    }

    // Build the string in reverse order
    while (value > 0) {
        char digit = '0' + static_cast<char>(value % 10);
        result.push_back(digit);
        value /= 10;
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

cpstd::string cpstd::to_string(unsigned long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
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
#endif
}

cpstd::string cpstd::to_string(unsigned long long val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
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
#endif
}

cpstd::string cpstd::to_string(float val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
    if (val == 0.0)
        return "0";

    cpstd::string result;
    bool isNegative = false;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
        val = -val;
    }

    // Convert the integral part to string
    unsigned long long integralPart = static_cast<unsigned long long>(val);
    result += to_string(integralPart);

    // Add decimal point
    result.push_back('.');

    // Convert the fractional part to string (considering a fixed precision, e.g., 15)
    double fractionalPart = val - static_cast<double>(integralPart);
    for (int i = 0; i < 6; ++i) {
        fractionalPart *= 10;
        result += static_cast<char>('0' + static_cast<int>(fractionalPart));
        fractionalPart -= static_cast<int>(fractionalPart);
    }

    // Add the negative sign if necessary
    if (isNegative) {
        result.insert(0, '-');
    }

    return result;
#endif
}

cpstd::string cpstd::to_string(double val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
    if (val == 0.0)
        return "0";

    cpstd::string result;
    bool isNegative = false;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
        val = -val;
    }

    // Convert the integral part to string
    unsigned long long integralPart = static_cast<unsigned long long>(val);
    result += to_string(integralPart);

    // Add decimal point
    result.push_back('.');

    // Convert the fractional part to string (considering a fixed precision, e.g., 15)
    double fractionalPart = val - static_cast<double>(integralPart);
    for (int i = 0; i < 8; ++i) {
        fractionalPart *= 10;
        result += static_cast<char>('0' + static_cast<int>(fractionalPart));
        fractionalPart -= static_cast<int>(fractionalPart);
    }

    // Add the negative sign if necessary
    if (isNegative) {
        result.insert(0, '-');
    }

    return result;
#endif
}

cpstd::string cpstd::to_string(long double val){
#if defined(CPSTL_STRING_USING_STD_ALLOCATION) || defined(CPSTL_USING_STL)
    return std::to_string(val);
#elif defined(CPSTL_STRING_USING_C_ALLOCATION)
    if (val == 0.0)
        return "0";

    cpstd::string result;
    bool isNegative = false;

    // Handle the case where the value is negative
    if (val < 0) {
        isNegative = true;
        val = -val;
    }

    // Convert the integral part to string
    unsigned long long integralPart = static_cast<unsigned long long>(val);
    result += to_string(integralPart);

    // Add decimal point
    result.push_back('.');

    // Convert the fractional part to string (considering a fixed precision, e.g., 15)
    double fractionalPart = val - static_cast<double>(integralPart);
    for (int i = 0; i < 6; ++i) {
        fractionalPart *= 10;
        result += static_cast<char>('0' + static_cast<int>(fractionalPart));
        fractionalPart -= static_cast<int>(fractionalPart);
    }

    // Add the negative sign if necessary
    if (isNegative) {
        result.insert(0, '-');
    }

    return result;
#endif
}