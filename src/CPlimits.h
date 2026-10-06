#ifndef CPSTL_LIMITS_H
#define CPSTL_LIMITS_H

    #include <CPSTL_BuildSettings.h>

    #if defined(CPSTL_USING_STL)
        #include <limits>
    #else
        // Freestanding headers: every compiler provides them, AVR-GCC included.
        #include <limits.h>
        #include <float.h>
    #endif

    namespace cpstd{
    #if defined(CPSTL_USING_STL)
        using float_round_style = std::float_round_style;
        using float_denorm_style = std::float_denorm_style;

        template<class T>
        using numeric_limits = std::numeric_limits<T>;

    #else
        #ifdef max
            #undef max
        #endif

        #ifdef min
            #undef min
        #endif

        enum float_round_style {
            round_indeterminate       = -1,
            round_toward_zero         =  0,
            round_to_nearest          =  1,
            round_toward_infinity     =  2,
            round_toward_neg_infinity =  3,
        };

        enum float_denorm_style {
            denorm_indeterminate = -1,
            denorm_absent        =  0,
            denorm_present       =  1
        };

        //! @brief Properties of arithmetic types, as `std::numeric_limits`.
        //!
        //! Specialized for bool, every character and integer type, float,
        //! double and long double. The primary template reports
        //! `is_specialized == false` and value-initialized results.
        template<class T> class numeric_limits {
        public:
            static constexpr bool is_specialized = false;
            static constexpr T min() noexcept { return T(); }
            static constexpr T max() noexcept { return T(); }
            static constexpr T lowest() noexcept { return T(); }
            static constexpr int digits = 0;
            static constexpr int digits10 = 0;
            static constexpr int max_digits10 = 0;
            static constexpr bool is_signed = false;
            static constexpr bool is_integer = false;
            static constexpr bool is_exact = false;
            static constexpr int radix = 0;
            static constexpr T epsilon() noexcept { return T(); }
            static constexpr T round_error() noexcept { return T(); }
            static constexpr int min_exponent = 0;
            static constexpr int min_exponent10 = 0;
            static constexpr int max_exponent = 0;
            static constexpr int max_exponent10 = 0;
            static constexpr bool has_infinity = false;
            static constexpr bool has_quiet_NaN = false;
            static constexpr bool has_signaling_NaN = false;
            static constexpr float_denorm_style has_denorm = denorm_absent;
            static constexpr bool has_denorm_loss = false;
            static constexpr T infinity() noexcept { return T(); }
            static constexpr T quiet_NaN() noexcept { return T(); }
            static constexpr T signaling_NaN() noexcept { return T(); }
            static constexpr T denorm_min() noexcept { return T(); }
            static constexpr bool is_iec559 = false;
            static constexpr bool is_bounded = false;
            static constexpr bool is_modulo = false;
            static constexpr bool traps = false;
            static constexpr bool tinyness_before = false;
            static constexpr float_round_style round_style = round_toward_zero;
        };

        // cv-qualified types share the unqualified type's limits.
        template<class T> class numeric_limits<const T> : public numeric_limits<T> {};
        template<class T> class numeric_limits<volatile T> : public numeric_limits<T> {};
        template<class T> class numeric_limits<const volatile T> : public numeric_limits<T> {};

        #if defined(FLT_TRUE_MIN)
            #define CPSTL_DETAIL_FLT_DENORM_MIN FLT_TRUE_MIN
            #define CPSTL_DETAIL_DBL_DENORM_MIN DBL_TRUE_MIN
            #define CPSTL_DETAIL_LDBL_DENORM_MIN LDBL_TRUE_MIN
        #else
            #define CPSTL_DETAIL_FLT_DENORM_MIN __FLT_DENORM_MIN__
            #define CPSTL_DETAIL_DBL_DENORM_MIN __DBL_DENORM_MIN__
            #define CPSTL_DETAIL_LDBL_DENORM_MIN __LDBL_DENORM_MIN__
        #endif

        namespace detail {

            // Shared members of every integral specialization. `Digits` counts
            // value bits (the sign bit excluded); digits10 = floor(Digits * log10 2).
            template<class T, T Min, T Max, int Digits, bool Signed>
            struct integral_limits {
                static constexpr bool is_specialized = true;
                static constexpr T min() noexcept { return Min; }
                static constexpr T max() noexcept { return Max; }
                static constexpr T lowest() noexcept { return Min; }
                static constexpr int digits = Digits;
                static constexpr int digits10 = Digits * 301 / 1000;
                static constexpr int max_digits10 = 0;
                static constexpr bool is_signed = Signed;
                static constexpr bool is_integer = true;
                static constexpr bool is_exact = true;
                static constexpr int radix = 2;
                static constexpr T epsilon() noexcept { return T(); }
                static constexpr T round_error() noexcept { return T(); }
                static constexpr int min_exponent = 0;
                static constexpr int min_exponent10 = 0;
                static constexpr int max_exponent = 0;
                static constexpr int max_exponent10 = 0;
                static constexpr bool has_infinity = false;
                static constexpr bool has_quiet_NaN = false;
                static constexpr bool has_signaling_NaN = false;
                static constexpr float_denorm_style has_denorm = denorm_absent;
                static constexpr bool has_denorm_loss = false;
                static constexpr T infinity() noexcept { return T(); }
                static constexpr T quiet_NaN() noexcept { return T(); }
                static constexpr T signaling_NaN() noexcept { return T(); }
                static constexpr T denorm_min() noexcept { return T(); }
                static constexpr bool is_iec559 = false;
                static constexpr bool is_bounded = true;
                static constexpr bool is_modulo = !Signed;
                static constexpr bool traps = false;
                static constexpr bool tinyness_before = false;
                static constexpr float_round_style round_style = round_toward_zero;
            };

            // Largest value of an unsigned type and of a signed type with the
            // same width, computed without overflow.
            template<class T>
            constexpr T unsigned_max() noexcept { return static_cast<T>(~static_cast<T>(0)); }

            template<class T>
            constexpr T signed_max() noexcept {
                return static_cast<T>(((static_cast<T>(1) << (sizeof(T) * CHAR_BIT - 2)) - 1) * 2 + 1);
            }

            template<class T, int Digits, int Mantissa, int MinExp, int MinExp10, int MaxExp, int MaxExp10>
            struct floating_limits {
                static constexpr bool is_specialized = true;
                static constexpr int digits = Mantissa;
                static constexpr int digits10 = Digits;
                static constexpr int max_digits10 = 2 + Mantissa * 301 / 1000;
                static constexpr bool is_signed = true;
                static constexpr bool is_integer = false;
                static constexpr bool is_exact = false;
                static constexpr int radix = FLT_RADIX;
                static constexpr T round_error() noexcept { return T(0.5); }
                static constexpr int min_exponent = MinExp;
                static constexpr int min_exponent10 = MinExp10;
                static constexpr int max_exponent = MaxExp;
                static constexpr int max_exponent10 = MaxExp10;
                static constexpr bool has_infinity = true;
                static constexpr bool has_quiet_NaN = true;
                static constexpr bool has_signaling_NaN = true;
                static constexpr float_denorm_style has_denorm = denorm_present;
                static constexpr bool has_denorm_loss = false;
                static constexpr bool is_iec559 = true;
                static constexpr bool is_bounded = true;
                static constexpr bool is_modulo = false;
                static constexpr bool traps = false;
                static constexpr bool tinyness_before = false;
                static constexpr float_round_style round_style = round_to_nearest;
            };
        }

        template<> class numeric_limits<bool>
            : public detail::integral_limits<bool, false, true, 1, false> {
        public:
            static constexpr int digits10 = 0;
            static constexpr bool is_modulo = false;
        };

        #define CPSTL_DETAIL_SIGNED_LIMITS(T) \
            template<> class numeric_limits<T> : public detail::integral_limits< \
                T, static_cast<T>(-detail::signed_max<T>() - 1), detail::signed_max<T>(), \
                static_cast<int>(sizeof(T) * CHAR_BIT - 1), true> {};

        #define CPSTL_DETAIL_UNSIGNED_LIMITS(T) \
            template<> class numeric_limits<T> : public detail::integral_limits< \
                T, static_cast<T>(0), detail::unsigned_max<T>(), \
                static_cast<int>(sizeof(T) * CHAR_BIT), false> {};

        #if CHAR_MIN < 0
            template<> class numeric_limits<char> : public detail::integral_limits<
                char, CHAR_MIN, CHAR_MAX, static_cast<int>(CHAR_BIT - 1), true> {};
        #else
            template<> class numeric_limits<char> : public detail::integral_limits<
                char, CHAR_MIN, CHAR_MAX, static_cast<int>(CHAR_BIT), false> {};
        #endif

        CPSTL_DETAIL_SIGNED_LIMITS(signed char)
        CPSTL_DETAIL_SIGNED_LIMITS(short)
        CPSTL_DETAIL_SIGNED_LIMITS(int)
        CPSTL_DETAIL_SIGNED_LIMITS(long)
        CPSTL_DETAIL_SIGNED_LIMITS(long long)
        CPSTL_DETAIL_UNSIGNED_LIMITS(unsigned char)
        CPSTL_DETAIL_UNSIGNED_LIMITS(unsigned short)
        CPSTL_DETAIL_UNSIGNED_LIMITS(unsigned int)
        CPSTL_DETAIL_UNSIGNED_LIMITS(unsigned long)
        CPSTL_DETAIL_UNSIGNED_LIMITS(unsigned long long)
        CPSTL_DETAIL_UNSIGNED_LIMITS(char16_t)
        CPSTL_DETAIL_UNSIGNED_LIMITS(char32_t)
        #if defined(__cpp_char8_t)
            CPSTL_DETAIL_UNSIGNED_LIMITS(char8_t)
        #endif

        #if defined(__WCHAR_UNSIGNED__) || (defined(_MSC_VER) && !defined(_NATIVE_WCHAR_T_DEFINED)) || \
            (defined(WCHAR_MIN) && WCHAR_MIN == 0)
            CPSTL_DETAIL_UNSIGNED_LIMITS(wchar_t)
        #else
            CPSTL_DETAIL_SIGNED_LIMITS(wchar_t)
        #endif

        #undef CPSTL_DETAIL_SIGNED_LIMITS
        #undef CPSTL_DETAIL_UNSIGNED_LIMITS

        template<> class numeric_limits<float> : public detail::floating_limits<
            float, FLT_DIG, FLT_MANT_DIG, FLT_MIN_EXP, FLT_MIN_10_EXP, FLT_MAX_EXP, FLT_MAX_10_EXP> {
        public:
            static constexpr float min() noexcept { return FLT_MIN; }
            static constexpr float max() noexcept { return FLT_MAX; }
            static constexpr float lowest() noexcept { return -FLT_MAX; }
            static constexpr float epsilon() noexcept { return FLT_EPSILON; }
            static constexpr float infinity() noexcept { return __builtin_huge_valf(); }
            static constexpr float quiet_NaN() noexcept { return __builtin_nanf(""); }
            static constexpr float signaling_NaN() noexcept { return __builtin_nansf(""); }
            static constexpr float denorm_min() noexcept { return CPSTL_DETAIL_FLT_DENORM_MIN; }
        };

        template<> class numeric_limits<double> : public detail::floating_limits<
            double, DBL_DIG, DBL_MANT_DIG, DBL_MIN_EXP, DBL_MIN_10_EXP, DBL_MAX_EXP, DBL_MAX_10_EXP> {
        public:
            static constexpr double min() noexcept { return DBL_MIN; }
            static constexpr double max() noexcept { return DBL_MAX; }
            static constexpr double lowest() noexcept { return -DBL_MAX; }
            static constexpr double epsilon() noexcept { return DBL_EPSILON; }
            static constexpr double infinity() noexcept { return __builtin_huge_val(); }
            static constexpr double quiet_NaN() noexcept { return __builtin_nan(""); }
            static constexpr double signaling_NaN() noexcept { return __builtin_nans(""); }
            static constexpr double denorm_min() noexcept { return CPSTL_DETAIL_DBL_DENORM_MIN; }
        };

        template<> class numeric_limits<long double> : public detail::floating_limits<
            long double, LDBL_DIG, LDBL_MANT_DIG, LDBL_MIN_EXP, LDBL_MIN_10_EXP, LDBL_MAX_EXP, LDBL_MAX_10_EXP> {
        public:
            static constexpr long double min() noexcept { return LDBL_MIN; }
            static constexpr long double max() noexcept { return LDBL_MAX; }
            static constexpr long double lowest() noexcept { return -LDBL_MAX; }
            static constexpr long double epsilon() noexcept { return LDBL_EPSILON; }
            static constexpr long double infinity() noexcept { return __builtin_huge_vall(); }
            static constexpr long double quiet_NaN() noexcept { return __builtin_nanl(""); }
            static constexpr long double signaling_NaN() noexcept { return __builtin_nansl(""); }
            static constexpr long double denorm_min() noexcept { return CPSTL_DETAIL_LDBL_DENORM_MIN; }
        };

    #endif
    }

#endif//CPSTL_LIMITS_H
