#include "CPSTL_String_toString.h"
#include <CPstring.h>
namespace cpstd{

    ////////////////////////////////////////////////////////////////////
    // to_string

        cpstd::string to_string(int val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
            cpstd::string result;
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

        cpstd::string to_string(long val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(long long val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(unsigned val) {
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(unsigned long val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(unsigned long long val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(float val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(double val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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

        cpstd::string to_string(long double val){
        #if __has_include(<string>)
            return cpstd::string(cpstd::move(std::to_string(val)));
        #else
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
    //
    ////////////////////////////////////////////////////////////////////
    // to_wstring

        cpstd::wstring to_wstring(int val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            cpstd::wstring result;
            bool isNegative = false;
            unsigned value = (val > 0) ? val : -1 * val;

            // Handle the case where the value is negative
            if (val < 0) {
                isNegative = true;
            }

            // Special case for 0
            if (value == 0) {
                result.push_back(L'0');
            }

            // Build the string in reverse order
            while (value > 0) {
                wchar_t digit = L'0' + static_cast<wchar_t>(value % 10);
                result.push_back(digit);
                value /= 10;
            }

            // Add the negative sign if necessary
            if (isNegative) {
                result.push_back(L'-');
            }

            // Reverse the string to get the correct order
            size_t start = 0;
            size_t end = result.size() - 1;
            while (start < end) {
                wchar_t temp = result[start];
                result[start] = result[end];
                result[end] = temp;
                start++;
                end--;
            }

            return result;
        #endif
        }

        cpstd::wstring to_wstring(long val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            cpstd::wstring result;
            bool isNegative = false;
            unsigned long value = (val > 0) ? val : -1 * val;

            // Handle the case where the value is negative
            if (val < 0) {
                isNegative = true;
            }

            // Special case for 0
            if (value == 0) {
                result.push_back(L'0');
            }

            // Build the string in reverse order
            while (value > 0) {
                wchar_t digit = L'0' + static_cast<wchar_t>(value % 10);
                result.push_back(digit);
                value /= 10;
            }

            // Add the negative sign if necessary
            if (isNegative) {
                result.push_back(L'-');
            }

            // Reverse the string to get the correct order
            size_t start = 0;
            size_t end = result.size() - 1;
            while (start < end) {
                wchar_t temp = result[start];
                result[start] = result[end];
                result[end] = temp;
                start++;
                end--;
            }

            return result;
        #endif
        }
        
        cpstd::wstring to_wstring(long long val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            cpstd::wstring result;
            bool isNegative = false;
            unsigned long long value = (val > 0) ? val : -1 * val;

            // Handle the case where the value is negative
            if (val < 0) {
                isNegative = true;
            }

            // Special case for 0
            if (value == 0) {
                result.push_back(L'0');
            }

            // Build the string in reverse order
            while (value > 0) {
                wchar_t digit = L'0' + static_cast<wchar_t>(value % 10);
                result.push_back(digit);
                value /= 10;
            }

            // Add the negative sign if necessary
            if (isNegative) {
                result.push_back(L'-');
            }

            // Reverse the string to get the correct order
            size_t start = 0;
            size_t end = result.size() - 1;
            while (start < end) {
                wchar_t temp = result[start];
                result[start] = result[end];
                result[end] = temp;
                start++;
                end--;
            }

            return result;
        #endif
        }

        cpstd::wstring to_wstring(unsigned val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            cpstd::wstring result;

            // Special case for 0
            if (val == 0) {
                result.push_back(L'0');
            }

            // Build the string in reverse order
            while (val > 0) {
                wchar_t digit = L'0' + static_cast<wchar_t>(val % 10);
                result.push_back(digit);
                val /= 10;
            }

            // Reverse the string to get the correct order
            size_t start = 0;
            size_t end = result.size() - 1;
            while (start < end) {
                wchar_t temp = result[start];
                result[start] = result[end];
                result[end] = temp;
                start++;
                end--;
            }

            return result;
        #endif
        }

        cpstd::wstring to_wstring(unsigned long val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            cpstd::wstring result;

            // Special case for 0
            if (val == 0) {
                result.push_back(L'0');
            }

            // Build the string in reverse order
            while (val > 0) {
                wchar_t digit = L'0' + static_cast<wchar_t>(val % 10);
                result.push_back(digit);
                val /= 10;
            }

            // Reverse the string to get the correct order
            size_t start = 0;
            size_t end = result.size() - 1;
            while (start < end) {
                wchar_t temp = result[start];
                result[start] = result[end];
                result[end] = temp;
                start++;
                end--;
            }

            return result;
        #endif
        }

        cpstd::wstring to_wstring(unsigned long long val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            cpstd::wstring result;

            // Special case for 0
            if (val == 0) {
                result.push_back(L'0');
            }

            // Build the string in reverse order
            while (val > 0) {
                wchar_t digit = L'0' + static_cast<wchar_t>(val % 10);
                result.push_back(digit);
                val /= 10;
            }

            // Reverse the string to get the correct order
            size_t start = 0;
            size_t end = result.size() - 1;
            while (start < end) {
                wchar_t temp = result[start];
                result[start] = result[end];
                result[end] = temp;
                start++;
                end--;
            }

            return result;
        #endif
        }

        cpstd::wstring to_wstring(float val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            if (val == 0.0f)
                return L"0";

            cpstd::wstring result;
            bool isNegative = false;

            // Handle the case where the value is negative
            if (val < 0) {
                isNegative = true;
                val = -val;
            }

            // Convert the integral part to string
            unsigned long long integralPart = static_cast<unsigned long long>(val);
            result += to_wstring(integralPart);

            // Add decimal point
            result.push_back(L'.');

            // Convert the fractional part to string (considering a fixed precision, e.g., 15)
            float fractionalPart = val - static_cast<float>(integralPart);
            for (int i = 0; i < 6; ++i) {
                fractionalPart *= 10;
                result += static_cast<wchar_t>(L'0' + static_cast<int>(fractionalPart));
                fractionalPart -= static_cast<int>(fractionalPart);
            }

            // Add the negative sign if necessary
            if (isNegative) {
                result.insert(0, L"-");
            }

            return result;
        #endif
        }
        
        cpstd::wstring to_wstring(double val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            if (val == 0.0)
                return L"0";

            cpstd::wstring result;
            bool isNegative = false;

            // Handle the case where the value is negative
            if (val < 0) {
                isNegative = true;
                val = -val;
            }

            // Convert the integral part to string
            unsigned long long integralPart = static_cast<unsigned long long>(val);
            result += to_wstring(integralPart);

            // Add decimal point
            result.push_back(L'.');

            // Convert the fractional part to string (considering a fixed precision, e.g., 15)
            double fractionalPart = val - static_cast<double>(integralPart);
            for (int i = 0; i < 6; ++i) {
                fractionalPart *= 10;
                result += static_cast<wchar_t>(L'0' + static_cast<int>(fractionalPart));
                fractionalPart -= static_cast<int>(fractionalPart);
            }

            // Add the negative sign if necessary
            if (isNegative) {
                result.insert(0, L"-");
            }

            return result;
        #endif
        }

        cpstd::wstring to_wstring(long double val) {
        #if __has_include(<string>)
            return cpstd::wstring(cpstd::move(std::to_wstring(val)));
        #else
            if (val == 0.0)
                return L"0";

            cpstd::wstring result;
            bool isNegative = false;

            // Handle the case where the value is negative
            if (val < 0) {
                isNegative = true;
                val = -val;
            }

            // Convert the integral part to string
            unsigned long long integralPart = static_cast<unsigned long long>(val);
            result += to_wstring(integralPart);

            // Add decimal point
            result.push_back(L'.');

            // Convert the fractional part to string (considering a fixed precision, e.g., 15)
            long double fractionalPart = val - static_cast<long double>(integralPart);
            for (int i = 0; i < 6; ++i) {
                fractionalPart *= 10;
                result += static_cast<wchar_t>(L'0' + static_cast<int>(fractionalPart));
                fractionalPart -= static_cast<int>(fractionalPart);
            }

            // Add the negative sign if necessary
            if (isNegative) {
                result.insert(0, L"-");
            }

            return result;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////
    // stoi
        
        int stoi(const cpstd::string& str, cpstd::size_t* pos, int base ){
        #if __has_include(<string>)
            return std::stoi(str,pos,base);
        #else
            int result = 0;
            bool negative = false;
            cpstd::size_t i = 0;

            // Handle optional sign
            if (str[i] == '-') {
                negative = true;
                ++i;
            } else if (str[i] == '+') {
                ++i;
            }

            // Convert digits to integer
            for (; i < str.size(); ++i) {
                if (str[i] >= '0' && str[i] <= '9') {
                    result = result * base + (str[i] - '0');
                } else {
                    // If invalid character is encountered, stop conversion
                    break;
                }
            }

            if (pos) {
                *pos = i;
            }

            return negative ? -result : result;
        #endif
        }

        int stoi(const cpstd::wstring& str, cpstd::size_t* pos, int base ){
            #if __has_include(<string>)
                // Using std::stoi if available
                return std::stoi(str, pos, base);
            #else
                int result = 0;
                bool negative = false;
                cpstd::size_t i = 0;

                // Handle optional sign
                if (str[i] == L'-') {
                    negative = true;
                    ++i;
                } else if (str[i] == L'+') {
                    ++i;
                }

                // Convert digits to integer
                for (; i < str.size(); ++i) {
                    if (str[i] >= L'0' && str[i] <= L'9') {
                        result = result * base + (str[i] - L'0');
                    } else {
                        // If invalid character is encountered, stop conversion
                        break;
                    }
                }

                if (pos) {
                    *pos = i;
                }

                return negative ? -result : result;
            #endif
        }
    //
    ////////////////////////////////////////////////////////////////////
    // stol
        
        long stol(const cpstd::string& str, cpstd::size_t* pos, int base ){
        #if __has_include(<string>)
            return std::stol((std::string)str, pos, base);
        #else
            long result = 0;
            bool negative = false;
            cpstd::size_t i = 0;

            // Handle optional sign
            if (str[i] == '-') {
                negative = true;
                ++i;
            } else if (str[i] == '+') {
                ++i;
            }

            // Convert digits to long integer
            for (; i < str.size(); ++i) {
                if (str[i] >= '0' && str[i] <= '9') {
                    result = result * base + (str[i] - '0');
                } else {
                    // If invalid character is encountered, stop conversion
                    break;
                }
            }

            if (pos) {
                *pos = i;
            }

            return negative ? -result : result;
        #endif
        }

        long stol(const cpstd::wstring& str, cpstd::size_t* pos, int base ){
        #if __has_include(<string>)
            // Using std::stol if available
            return std::stol((std::wstring)str, pos, base);
        #else
            long result = 0;
            bool negative = false;
            cpstd::size_t i = 0;

            // Handle optional sign
            if (str[i] == L'-') {
                negative = true;
                ++i;
            } else if (str[i] == L'+') {
                ++i;
            }

            // Convert digits to long integer
            for (; i < str.size(); ++i) {
                if (str[i] >= L'0' && str[i] <= L'9') {
                    result = result * base + (str[i] - L'0');
                } else {
                    // If invalid character is encountered, stop conversion
                    break;
                }
            }

            if (pos) {
                *pos = i;
            }

            return negative ? -result : result;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////
    // stoll
    
        long long stoll(const cpstd::string& str, cpstd::size_t* pos, int base ){
        #if __has_include(<string>)
            // Using std::stoll if available
            return std::stoll(str, pos, base);
        #else
            long long result = 0;
            bool negative = false;
            cpstd::size_t i = 0;

            // Handle optional sign
            if (str[i] == '-') {
                negative = true;
                ++i;
            } else if (str[i] == '+') {
                ++i;
            }

            // Convert digits to long long integer
            for (; i < str.size(); ++i) {
                if (str[i] >= '0' && str[i] <= '9') {
                    result = result * base + (str[i] - '0');
                } else {
                    // If invalid character is encountered, stop conversion
                    break;
                }
            }

            if (pos) {
                *pos = i;
            }

            return negative ? -result : result;
        #endif
        }

        long long stoll(const cpstd::wstring& str, cpstd::size_t* pos, int base ){
        #if __has_include(<string>)
            // Using std::stoll if available
            return std::stoll(str, pos, base);
        #else
            long long result = 0;
            bool negative = false;
            cpstd::size_t i = 0;

            // Handle optional sign
            if (str[i] == L'-') {
                negative = true;
                ++i;
            } else if (str[i] == L'+') {
                ++i;
            }

            // Convert digits to long long integer
            for (; i < str.size(); ++i) {
                if (str[i] >= L'0' && str[i] <= L'9') {
                    result = result * base + (str[i] - L'0');
                } else {
                    // If invalid character is encountered, stop conversion
                    break;
                }
            }

            if (pos) {
                *pos = i;
            }

            return negative ? -result : result;
        #endif
        }
    //
    ////////////////////////////////////////////////////////////////////
}
