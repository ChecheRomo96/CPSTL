#include <CPSTL.h>
#include <CPtype_traits.h>
#include <stdio.h>

// Convert a simulated 10-bit ADC sample to millivolts.
template <typename T>
long ScaleIntegral(T value, long numerator, long denominator) {
    static_assert(cpstd::is_integral<T>::value, "ScaleIntegral needs an integer type");
    // This example's 10-bit input and 5000 mV reference fit in a 32-bit long.
    return (static_cast<long>(value) * numerator) / denominator;
}
static_assert(!cpstd::is_integral<float>::value, "float is not integral");

int main() {
    printf("Convert a simulated 10-bit ADC sample to millivolts.\n");
    const long rawAdc = 768;
    const long referenceMv = 5000;
    const long adcMaximum = 1023;
    const long millivolts = ScaleIntegral(rawAdc, referenceMv, adcMaximum);
    printf("Simulated ADC sample: %ld\n", static_cast<long>(rawAdc));
    printf("ADC full-scale count: %ld\n", static_cast<long>(adcMaximum));
    printf("Reference voltage (mV): %ld\n", static_cast<long>(referenceMv));
    printf("Calculation: 768 * 5000 / 1023, using long integers to avoid AVR int overflow.\n");
    printf("Converted voltage (mV): %ld\n", static_cast<long>(millivolts));
    printf("Integer division discards the fraction; this sample is about 3753 mV.\n");
    printf("is_integral rejects floating-point inputs at compile time, not at runtime.\n");
    return 0;
}
