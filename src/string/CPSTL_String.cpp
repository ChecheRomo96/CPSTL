#include "CPSTL_String.h"
#include <CPlimits.h>

#if !defined(CPSTL_USING_STL)
    #include <stdlib.h>
#endif

namespace {

#if !defined(CPSTL_USING_STL)

    // Writes the decimal digits of `value` in order, preceded by '-' when
    // `negative` is set.
    cpstd::string FormatUnsigned(unsigned long long value, bool negative) {
        char digits[24];
        int count = 0;
        do {
            digits[count++] = static_cast<char>('0' + static_cast<int>(value % 10u));
            value /= 10u;
        } while (value != 0u);

        cpstd::string result;
        result.reserve(static_cast<cpstd::size_t>(count) + (negative ? 1u : 0u));
        if (negative) {
            result.push_back('-');
        }
        while (count > 0) {
            result.push_back(digits[--count]);
        }
        return result;
    }

    // Magnitude of a signed value without overflowing on its minimum.
    unsigned long long Magnitude(long long value) {
        return value < 0 ? static_cast<unsigned long long>(-(value + 1)) + 1u
                         : static_cast<unsigned long long>(value);
    }

    // Fixed six-decimal format, rounded to nearest, like std::to_string.
    // Values beyond the range of unsigned long long are not representable in
    // this format and are written as "inf" / "-inf"; NaN as "nan".
    cpstd::string FormatFixed(long double value) {
        if (value != value) {
            return cpstd::string("nan");
        }
        const bool negative = value < 0;
        if (negative) {
            value = -value;
        }
        const long double scaled = value * 1000000.0L + 0.5L;
        const long double limit = 18446744073709551615.0L;
        if (scaled >= limit) {
            return cpstd::string(negative ? "-inf" : "inf");
        }
        const unsigned long long micros = static_cast<unsigned long long>(scaled);
        const unsigned long long whole = micros / 1000000u;
        unsigned long long fraction = micros % 1000000u;

        cpstd::string result = FormatUnsigned(whole, negative);
        result.push_back('.');
        char decimals[6];
        for (int i = 5; i >= 0; --i) {
            decimals[i] = static_cast<char>('0' + static_cast<int>(fraction % 10u));
            fraction /= 10u;
        }
        result.append(decimals, 6);
        return result;
    }

    int DigitValue(char c) {
        if (c >= '0' && c <= '9') { return c - '0'; }
        if (c >= 'a' && c <= 'z') { return c - 'a' + 10; }
        if (c >= 'A' && c <= 'Z') { return c - 'A' + 10; }
        return 99;
    }

    bool IsSpace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
    }

    // Parses an integer like strtoull: optional whitespace, sign and base
    // prefix (base 0 detects 0x / 0), then digits. Reports the magnitude, the
    // sign, whether it overflowed, and the characters consumed (0 when no
    // digits were found).
    struct ParsedInteger {
        unsigned long long magnitude;
        bool negative;
        bool overflow;
        cpstd::size_t used;
    };

    ParsedInteger ParseInteger(const cpstd::string& text, int base) {
        ParsedInteger result = {0u, false, false, 0u};
        const char* s = text.c_str();
        cpstd::size_t i = 0;
        while (IsSpace(s[i])) {
            ++i;
        }
        if (s[i] == '+' || s[i] == '-') {
            result.negative = (s[i] == '-');
            ++i;
        }
        if ((base == 0 || base == 16) && s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X') &&
            DigitValue(s[i + 2]) < 16) {
            i += 2;
            base = 16;
        } else if (base == 0) {
            base = (s[i] == '0') ? 8 : 10;
        }
        if (base < 2 || base > 36) {
            return result;
        }
        const unsigned long long ubase = static_cast<unsigned long long>(base);
        const unsigned long long limit = static_cast<unsigned long long>(-1);
        const cpstd::size_t firstDigit = i;
        int digit = DigitValue(s[i]);
        while (digit < base) {
            const unsigned long long d = static_cast<unsigned long long>(digit);
            if (result.magnitude > (limit - d) / ubase) {
                result.overflow = true;
            } else {
                result.magnitude = result.magnitude * ubase + d;
            }
            ++i;
            digit = DigitValue(s[i]);
        }
        result.used = (i == firstDigit) ? 0u : i;
        return result;
    }

    template <class Signed>
    Signed ToSigned(const ParsedInteger& parsed, Signed minimum, Signed maximum) {
        const unsigned long long maxMagnitude = static_cast<unsigned long long>(maximum);
        if (parsed.negative) {
            if (parsed.overflow || parsed.magnitude > maxMagnitude + 1u) {
                return minimum;
            }
            if (parsed.magnitude == maxMagnitude + 1u) {
                return minimum;
            }
            return static_cast<Signed>(-static_cast<Signed>(parsed.magnitude));
        }
        if (parsed.overflow || parsed.magnitude > maxMagnitude) {
            return maximum;
        }
        return static_cast<Signed>(parsed.magnitude);
    }

    template <class Unsigned>
    Unsigned ToUnsigned(const ParsedInteger& parsed, Unsigned maximum) {
        if (parsed.overflow || parsed.magnitude > static_cast<unsigned long long>(maximum)) {
            return maximum;
        }
        // Like strtoul, a leading '-' negates in the unsigned type.
        const Unsigned value = static_cast<Unsigned>(parsed.magnitude);
        return parsed.negative ? static_cast<Unsigned>(0u - value) : value;
    }

    void Store(cpstd::size_t* idx, cpstd::size_t used) {
        if (idx != nullptr) {
            *idx = used;
        }
    }

    double ParseFloating(const cpstd::string& str, cpstd::size_t* idx) {
        const char* begin = str.c_str();
        char* end = nullptr;
        const double value = strtod(begin, &end);
        Store(idx, static_cast<cpstd::size_t>(end - begin));
        return value;
    }

#endif

} // namespace

namespace cpstd {

#if defined(CPSTL_USING_STL)

    int stoi(const string& str, size_t* idx, int base) { return std::stoi(str, idx, base); }
    long stol(const string& str, size_t* idx, int base) { return std::stol(str, idx, base); }
    unsigned long stoul(const string& str, size_t* idx, int base) { return std::stoul(str, idx, base); }
    long long stoll(const string& str, size_t* idx, int base) { return std::stoll(str, idx, base); }
    unsigned long long stoull(const string& str, size_t* idx, int base) { return std::stoull(str, idx, base); }
    float stof(const string& str, size_t* idx) { return std::stof(str, idx); }
    double stod(const string& str, size_t* idx) { return std::stod(str, idx); }
    long double stold(const string& str, size_t* idx) { return std::stold(str, idx); }

    string to_string(int val) { return std::to_string(val); }
    string to_string(long val) { return std::to_string(val); }
    string to_string(long long val) { return std::to_string(val); }
    string to_string(unsigned val) { return std::to_string(val); }
    string to_string(unsigned long val) { return std::to_string(val); }
    string to_string(unsigned long long val) { return std::to_string(val); }
    string to_string(float val) { return std::to_string(val); }
    string to_string(double val) { return std::to_string(val); }
    string to_string(long double val) { return std::to_string(val); }

#else

    int stoi(const string& str, size_t* idx, int base) {
        const ParsedInteger parsed = ParseInteger(str, base);
        Store(idx, parsed.used);
        return parsed.used == 0 ? 0 : ToSigned<int>(parsed, cpstd::numeric_limits<int>::min(),
                                                     cpstd::numeric_limits<int>::max());
    }

    long stol(const string& str, size_t* idx, int base) {
        const ParsedInteger parsed = ParseInteger(str, base);
        Store(idx, parsed.used);
        return parsed.used == 0 ? 0L : ToSigned<long>(parsed, cpstd::numeric_limits<long>::min(),
                                                      cpstd::numeric_limits<long>::max());
    }

    long long stoll(const string& str, size_t* idx, int base) {
        const ParsedInteger parsed = ParseInteger(str, base);
        Store(idx, parsed.used);
        return parsed.used == 0 ? 0LL
            : ToSigned<long long>(parsed, cpstd::numeric_limits<long long>::min(),
                                  cpstd::numeric_limits<long long>::max());
    }

    unsigned long stoul(const string& str, size_t* idx, int base) {
        const ParsedInteger parsed = ParseInteger(str, base);
        Store(idx, parsed.used);
        return parsed.used == 0 ? 0UL
            : ToUnsigned<unsigned long>(parsed, cpstd::numeric_limits<unsigned long>::max());
    }

    unsigned long long stoull(const string& str, size_t* idx, int base) {
        const ParsedInteger parsed = ParseInteger(str, base);
        Store(idx, parsed.used);
        return parsed.used == 0 ? 0ULL
            : ToUnsigned<unsigned long long>(parsed, cpstd::numeric_limits<unsigned long long>::max());
    }

    float stof(const string& str, size_t* idx) { return static_cast<float>(ParseFloating(str, idx)); }
    double stod(const string& str, size_t* idx) { return ParseFloating(str, idx); }
    long double stold(const string& str, size_t* idx) { return ParseFloating(str, idx); }

    string to_string(int val) { return FormatUnsigned(Magnitude(val), val < 0); }
    string to_string(long val) { return FormatUnsigned(Magnitude(val), val < 0); }
    string to_string(long long val) { return FormatUnsigned(Magnitude(val), val < 0); }
    string to_string(unsigned val) { return FormatUnsigned(val, false); }
    string to_string(unsigned long val) { return FormatUnsigned(val, false); }
    string to_string(unsigned long long val) { return FormatUnsigned(val, false); }
    string to_string(float val) { return FormatFixed(val); }
    string to_string(double val) { return FormatFixed(val); }
    string to_string(long double val) { return FormatFixed(val); }

#endif

}
