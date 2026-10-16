#include <stdint.h>
#include "../Arduino/CPSTLHardware/HardwareTests.h"

enum { CaseCount = 0
#define CPSTL_HW_CASE(name) + 1
#include "../Arduino/CPSTLHardware/Cases.h"
#undef CPSTL_HW_CASE
};

struct NativeReport {
    uint32_t magic, buildId, state, total, passed, failed, assertions;
    uint32_t outcomes[CaseCount];
    uint32_t failureLines[CaseCount];
};
extern "C" {
volatile NativeReport cpstlNativeReport __attribute__((used)) = {};
}

static void RunCase(bool (*test)()) {
    const unsigned index = cpstlNativeReport.total;
    hardware_tests::lastFailureLine = 0;
    bool passed = test();
#if defined(CPSTL_HW_INJECT_FAILURE)
    if (index == 0) passed = false;
#endif
    cpstlNativeReport.outcomes[index] = passed ? 1 : 2;
    cpstlNativeReport.failureLines[index] = hardware_tests::lastFailureLine;
    cpstlNativeReport.total = index + 1;
    if (passed) ++cpstlNativeReport.passed;
    else ++cpstlNativeReport.failed;
}

extern "C" __attribute__((noreturn)) void romodular_fault_handler() {
    cpstlNativeReport.state = 3;
    for (;;) {}
}
int main() {
    cpstlNativeReport.magic = 0x4350534eUL;
    cpstlNativeReport.buildId = CPSTL_HW_BUILD_ID;
    cpstlNativeReport.state = 1;
    using namespace hardware_tests;
#define CPSTL_HW_CASE(name) RunCase(name);
#include "../Arduino/CPSTLHardware/Cases.h"
#undef CPSTL_HW_CASE
    cpstlNativeReport.assertions = hardware_tests::assertions;
    __atomic_thread_fence(__ATOMIC_RELEASE);
    cpstlNativeReport.state = 2;
    return cpstlNativeReport.failed ? 1 : 0;
}
