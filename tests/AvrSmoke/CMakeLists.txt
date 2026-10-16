#####################################################################################################
# Self-checking AVR firmware (ATmega328P / ATmega2560)
#
# Linking it against the bare AVR-GCC toolchain is the AVR gate: every module
# must compile with C allocation and without a C++ standard library.

    add_executable(CPSTLAvrSmoke main.cpp)
    target_compile_definitions(CPSTLAvrSmoke PRIVATE F_CPU=16000000UL)
    target_compile_options(CPSTLAvrSmoke PRIVATE -Os)
    target_link_libraries(CPSTLAvrSmoke PRIVATE CPSTL::CPSTL)
    cpstl_enable_warnings(CPSTLAvrSmoke)

    include("${PROJECT_SOURCE_DIR}/tools/RoModularBuild/cmake/boards/AVR.cmake")
    romodular_configure_avr(CPSTLAvrSmoke MALLOC_NEW)
