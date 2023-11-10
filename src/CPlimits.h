#ifndef CPSTL_LIMITS_H
#define CPSTL_LIMITS_H

    #include <CPSTL_BuildSettings.h>

    namespace cpstd{
    #if defined(CPSTL_USING_STL)
        using float_round_style = std::float_round_style;
        using float_denorm_style = std::float_denorm_style;

        template<class T> 
        using numeric_limits = std::numeric_limits<T>;

    #else
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


        template<> class numeric_limits<bool> {
        public:
            static constexpr bool is_specialized = true;

            static constexpr bool min() noexcept { return false; }
            static constexpr bool max() noexcept { return true; }
            static constexpr bool lowest() noexcept { return false; }

            static constexpr int digits = 1;
            static constexpr int digits10 = 0;
            static constexpr int max_digits10 = 0;

            static constexpr bool is_signed = false;
            static constexpr bool is_integer = true;
            static constexpr bool is_exact = true;
            static constexpr int radix = 2;
            
            static constexpr bool is_bounded = true;
            static constexpr bool is_modulo = false;        
        };

    #endif
    }

#endif//CPSTL_LIMITS_H