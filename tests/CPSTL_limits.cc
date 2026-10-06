#include <gtest/gtest.h>

#include <CPlimits.h>

#include <limits>

// cpstd::numeric_limits must agree with std::numeric_limits on every
// specialized type, in both modes.
template <class T>
void ExpectSameLimits() {
    using C = cpstd::numeric_limits<T>;
    using S = std::numeric_limits<T>;
    EXPECT_TRUE(C::is_specialized);
    EXPECT_EQ(C::min(), S::min());
    EXPECT_EQ(C::max(), S::max());
    EXPECT_EQ(C::lowest(), S::lowest());
    EXPECT_EQ(C::digits, S::digits);
    EXPECT_EQ(C::digits10, S::digits10);
    EXPECT_EQ(C::is_signed, S::is_signed);
    EXPECT_EQ(C::is_integer, S::is_integer);
    EXPECT_EQ(C::is_exact, S::is_exact);
    EXPECT_EQ(C::radix, S::radix);
    EXPECT_EQ(C::is_bounded, S::is_bounded);
}

TEST(NumericLimitsTest, IntegralTypes) {
    ExpectSameLimits<bool>();
    ExpectSameLimits<char>();
    ExpectSameLimits<signed char>();
    ExpectSameLimits<unsigned char>();
    ExpectSameLimits<wchar_t>();
    ExpectSameLimits<char16_t>();
    ExpectSameLimits<char32_t>();
    ExpectSameLimits<short>();
    ExpectSameLimits<unsigned short>();
    ExpectSameLimits<int>();
    ExpectSameLimits<unsigned int>();
    ExpectSameLimits<long>();
    ExpectSameLimits<unsigned long>();
    ExpectSameLimits<long long>();
    ExpectSameLimits<unsigned long long>();
    EXPECT_EQ(cpstd::numeric_limits<const int>::max(), 2147483647);
}

TEST(NumericLimitsTest, FloatingTypes) {
    ExpectSameLimits<float>();
    ExpectSameLimits<double>();
    ExpectSameLimits<long double>();
    EXPECT_EQ(cpstd::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon());
    EXPECT_EQ(cpstd::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    EXPECT_EQ(cpstd::numeric_limits<double>::denorm_min(), std::numeric_limits<double>::denorm_min());
    const double nan = cpstd::numeric_limits<double>::quiet_NaN();
    EXPECT_NE(nan, nan);
    EXPECT_EQ(cpstd::numeric_limits<float>::max_digits10, std::numeric_limits<float>::max_digits10);
    EXPECT_EQ(cpstd::numeric_limits<double>::max_digits10, std::numeric_limits<double>::max_digits10);
}

namespace {
    struct NotArithmetic {};
}

TEST(NumericLimitsTest, UnspecializedTypes) {
    EXPECT_FALSE(cpstd::numeric_limits<NotArithmetic>::is_specialized);
}
