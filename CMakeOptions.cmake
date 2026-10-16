#####################################################################################################
# Build outputs

    option(CPSTL_TESTING "Build the GoogleTest suite" OFF)
    option(CPSTL_EXAMPLES "Build the desktop examples" OFF)
    option(CPSTL_AVR_SMOKE "Build the self-checking AVR firmware (AVR cross builds only)" OFF)
    option(CPSTL_STM32_NATIVE "Build native STM32G0B1CBT6 contract firmware (no Arduino)" OFF)
    option(CPSTL_STM32_INJECT_FAILURE "Deliberately fail the first native STM32 case" OFF)
    set(CPSTL_STM32_BUILD_ID "0x43505354" CACHE STRING "Unique 32-bit native STM32 report ID")
    option(CPSTL_WARNINGS_AS_ERRORS "Treat warnings in CPSTL tests and examples as errors" ON)

    set(CPSTL_CXX_STANDARD "11" CACHE STRING "C++ standard for CPSTL and its tests (11, 14, 17 or 20)")
    set_property(CACHE CPSTL_CXX_STANDARD PROPERTY STRINGS 11 14 17 20)
#
#####################################################################################################
# Library configuration (exported as compile definitions of CPSTL::CPSTL)

    option(CPSTL_USING_STL "Alias every cpstd facility to std (hosted targets only)" OFF)

    set(CPSTL_ALLOCATION "C" CACHE STRING
        "cpstd::allocator backend: C (malloc/free), CPP (operator new nothrow) or STD (std::allocator)")
    set_property(CACHE CPSTL_ALLOCATION PROPERTY STRINGS C CPP STD)

    option(CPSTL_VECTOR "Include cpstd::vector in CPSTL.h" ON)
    option(CPSTL_STRING "Include cpstd::string in CPSTL.h and build its conversions" ON)
    option(CPSTL_STACK "Include the cpstd::stack adapter in CPSTL.h" ON)
    option(CPSTL_QUEUE "Include the cpstd::queue adapter in CPSTL.h" ON)
    option(CPSTL_UNICODE_STRINGS "Declare u16string and u32string (and u8string from C++20)" OFF)
#
#####################################################################################################
# Validation

    if(NOT CPSTL_CXX_STANDARD MATCHES "^(11|14|17|20)$")
        message(FATAL_ERROR "CPSTL_CXX_STANDARD must be 11, 14, 17 or 20, not '${CPSTL_CXX_STANDARD}'")
    endif()

    string(TOUPPER "${CPSTL_ALLOCATION}" CPSTL_ALLOCATION)
    if(NOT CPSTL_ALLOCATION MATCHES "^(C|CPP|STD)$")
        message(FATAL_ERROR "CPSTL_ALLOCATION must be C, CPP or STD, not '${CPSTL_ALLOCATION}'")
    endif()
    if(CPSTL_USING_STL)
        set(CPSTL_ALLOCATION "STD")
    endif()

    if(CPSTL_STM32_NATIVE)
        if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m0plus")
            message(FATAL_ERROR "CPSTL_STM32_NATIVE needs the Cortex-M0+ Arm toolchain")
        endif()
        if(CPSTL_TESTING OR CPSTL_EXAMPLES OR CPSTL_AVR_SMOKE)
            message(FATAL_ERROR "Native STM32 firmware cannot build host tests/examples or AVR firmware")
        endif()
        if(NOT CPSTL_VECTOR OR NOT CPSTL_STRING OR NOT CPSTL_STACK OR NOT CPSTL_QUEUE)
            message(FATAL_ERROR "Native STM32 contract firmware requires all four container modules")
        endif()
        string(LENGTH "${CPSTL_STM32_BUILD_ID}" _stm32_id_length)
        if(NOT CPSTL_STM32_BUILD_ID MATCHES "^0x[0-9A-Fa-f]+$" OR _stm32_id_length GREATER 10)
            message(FATAL_ERROR "CPSTL_STM32_BUILD_ID must be a hexadecimal 32-bit integer")
        endif()
    endif()

    # AVR-GCC ships no C++ standard library: no STL mode, no std::allocator,
    # and nothing for GoogleTest to run on.
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "^avr")
        if(CPSTL_USING_STL OR CPSTL_ALLOCATION STREQUAL "STD")
            message(FATAL_ERROR "AVR builds need CPSTL_USING_STL=OFF and CPSTL_ALLOCATION C or CPP")
        endif()
        if(CPSTL_TESTING OR CPSTL_EXAMPLES)
            message(FATAL_ERROR "CPSTL_TESTING and CPSTL_EXAMPLES are host-only; AVR builds use CPSTL_AVR_SMOKE")
        endif()
    elseif(CPSTL_AVR_SMOKE)
        message(FATAL_ERROR "CPSTL_AVR_SMOKE needs an AVR toolchain (preset atmega328p_avrgcc_avr5)")
    endif()
#
#####################################################################################################
