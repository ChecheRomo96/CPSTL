#ifndef CPSTL_HARDWARE_REPORT_H
#define CPSTL_HARDWARE_REPORT_H

// STM32 runs automatically and exposes its result through SWD, so no UART
// adapter is required. state=2 is written only after every case has finished.
#if defined(ARDUINO_ARCH_STM32)
enum {
    HardwareCaseCount = 0
#define CPSTL_HW_CASE(name) + 1
#include "Cases.h"
#undef CPSTL_HW_CASE
};
struct HardwareReport {
    uint32_t magic;
    uint32_t buildId;
    uint32_t state;
    uint32_t total;
    uint32_t passed;
    uint32_t failed;
    uint32_t assertions;
    uint32_t outcomes[HardwareCaseCount]; // 1=PASS, 2=FAIL, 0=not executed
};
extern "C" {
volatile HardwareReport cpstlHardwareReport __attribute__((used)) = {};
}
#endif
#endif
