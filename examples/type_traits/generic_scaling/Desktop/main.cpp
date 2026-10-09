#include <CPlimits.h>
#include <CPtype_traits.h>

#include <stdio.h>

template<class T>
typename cpstd::enable_if<cpstd::is_integral<T>::value, int>::type
Scale(T value) {
    return static_cast<int>(value) * 2;
}

int main() {
    printf("Scaled integral: %d, byte max: %u\n", Scale(21),
           static_cast<unsigned>(cpstd::numeric_limits<unsigned char>::max()));
    return 0;
}
