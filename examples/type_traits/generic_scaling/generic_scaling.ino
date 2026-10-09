#include <CPSTL.h>
#include <CPlimits.h>


/*
  Goal: Compile-time selection: restrict an arithmetic helper to integral signals.
  Interfaces: is_integral<T>::value and static_assert.
  Observe: The valid ADC conversion has no runtime type check.
*/
static_assert(cpstd::is_integral<int>::value, "int is integral");
static_assert(!cpstd::is_integral<float>::value, "float is not integral");

template <typename T>
T ScaleIntegral(T value, T numerator, T denominator) {
    static_assert(cpstd::is_integral<T>::value, "ScaleIntegral needs an integer type");
    return static_cast<T>((value * numerator) / denominator);
}

void setup() {
    Serial.begin(9600);
    const int rawAdc = 768;
    const int millivolts = ScaleIntegral(rawAdc, 5000, 1023);
    Serial.print("ADC "); Serial.print(rawAdc);
    Serial.print(" -> "); Serial.print(millivolts); Serial.println(" mV");
    Serial.print("uint8 maximum: ");
    Serial.println(cpstd::numeric_limits<unsigned char>::max());
    Serial.println("The trait rejects floating-point calls at compile time.");
}

void loop() {}
