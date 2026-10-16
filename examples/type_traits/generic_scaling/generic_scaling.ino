#include <CPSTL.h>
#include <CPtype_traits.h>

// Convert a simulated 10-bit ADC sample to millivolts.
template <typename T>
long ScaleIntegral(T value, long numerator, long denominator) {
    static_assert(cpstd::is_integral<T>::value, "ScaleIntegral needs an integer type");
    // This example's 10-bit input and 5000 mV reference fit in a 32-bit long.
    return (static_cast<long>(value) * numerator) / denominator;
}
static_assert(!cpstd::is_integral<float>::value, "float is not integral");

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Convert a simulated 10-bit ADC sample to millivolts.");
    const long rawAdc = 768;
    const long referenceMv = 5000;
    const long adcMaximum = 1023;
    const long millivolts = ScaleIntegral(rawAdc, referenceMv, adcMaximum);
    Serial.print("Simulated ADC sample: "); Serial.println(static_cast<long>(rawAdc));
    Serial.print("ADC full-scale count: "); Serial.println(static_cast<long>(adcMaximum));
    Serial.print("Reference voltage (mV): "); Serial.println(static_cast<long>(referenceMv));
    Serial.println("Calculation: 768 * 5000 / 1023, using long integers to avoid AVR int overflow.");
    Serial.print("Converted voltage (mV): "); Serial.println(static_cast<long>(millivolts));
    Serial.println("Integer division discards the fraction; this sample is about 3753 mV.");
    Serial.println("is_integral rejects floating-point inputs at compile time, not at runtime.");
}

void loop() {}
