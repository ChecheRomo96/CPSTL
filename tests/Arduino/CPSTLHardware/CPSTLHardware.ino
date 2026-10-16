#include "HardwareTests.h"
#include "HardwareReport.h"

#ifndef CPSTL_HW_BUILD_ID
#define CPSTL_HW_BUILD_ID 0UL
#endif

static unsigned totalCases;
static unsigned failedCases;

static void RunCase(const __FlashStringHelper* name, bool (*run)()) {
    ++totalCases;
    bool passed = run();
#if defined(CPSTL_HW_INJECT_FAILURE)
    if (totalCases == 1) passed = false;
#endif
    if (!passed) ++failedCases;
#if defined(ARDUINO_ARCH_STM32)
    cpstlHardwareReport.outcomes[totalCases - 1] = passed ? 1 : 2;
#endif
    Serial.print(F("CPSTL_HW_CASE ")); Serial.print(name);
    Serial.println(passed ? F(" PASS") : F(" FAIL"));
}

static void ExecuteCases() {
    totalCases = 0; failedCases = 0; hardware_tests::assertions = 0;
#if defined(ARDUINO_ARCH_STM32)
    cpstlHardwareReport.magic = 0x43505354UL;
    cpstlHardwareReport.buildId = CPSTL_HW_BUILD_ID;
    cpstlHardwareReport.state = 1;
#endif
    Serial.print(F("CPSTL_HW_BEGIN ")); Serial.println(CPSTL_HW_BUILD_ID, HEX);
    using namespace hardware_tests;
#define CPSTL_HW_CASE(name) RunCase(F(#name), name);
#include "Cases.h"
#undef CPSTL_HW_CASE
    Serial.print(F("CPSTL_HW_END ")); Serial.print(CPSTL_HW_BUILD_ID, HEX);
    Serial.print(F(" total=")); Serial.print(totalCases);
    Serial.print(F(" passed=")); Serial.print(totalCases - failedCases);
    Serial.print(F(" failed=")); Serial.print(failedCases);
    Serial.print(F(" assertions=")); Serial.println(hardware_tests::assertions);
#if defined(ARDUINO_ARCH_STM32)
    cpstlHardwareReport.total = totalCases;
    cpstlHardwareReport.passed = totalCases - failedCases;
    cpstlHardwareReport.failed = failedCases;
    cpstlHardwareReport.assertions = hardware_tests::assertions;
    cpstlHardwareReport.state = 2;
#endif
}

void setup() {
    Serial.begin(115200);
#if defined(ARDUINO_ARCH_STM32)
    ExecuteCases();
#endif
}

void loop() {
#if defined(ARDUINO_ARCH_STM32)
    return; // Keep the completed SWD report stable until reset.
#else
    static char command[24];
    static byte used;
    while (Serial.available()) {
        char c = static_cast<char>(Serial.read());
        if (c == '\r') continue;
        if (c != '\n') {
            if (used < sizeof(command) - 1) command[used++] = c;
            else used = 0;
            continue;
        }
        command[used] = '\0'; used = 0;
        if (strncmp(command, "RUN ", 4) != 0 ||
            strtoul(command + 4, nullptr, 16) != CPSTL_HW_BUILD_ID) continue;
        ExecuteCases();
    }
#endif
}
