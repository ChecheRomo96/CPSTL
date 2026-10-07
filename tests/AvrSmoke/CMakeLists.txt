#####################################################################################################
# Self-checking AVR firmware (ATmega328P)
#
# Linking it against the bare AVR-GCC toolchain is the AVR gate: every module
# must compile with C allocation and without a C++ standard library.

    add_executable(CPSTLAvrSmoke main.cpp)
    set_target_properties(CPSTLAvrSmoke PROPERTIES SUFFIX ".elf")
    target_compile_definitions(CPSTLAvrSmoke PRIVATE F_CPU=16000000UL)
    target_compile_options(CPSTLAvrSmoke PRIVATE -Os)
    target_link_libraries(CPSTLAvrSmoke PRIVATE CPSTL::CPSTL)
    cpstl_enable_warnings(CPSTLAvrSmoke)

    find_program(CPSTL_AVR_OBJCOPY "${ROMODULAR_AVR_TOOLCHAIN_PREFIX}-objcopy"
        HINTS "${ROMODULAR_AVR_TOOLCHAIN_ROOT}/bin" REQUIRED)
    find_program(CPSTL_AVR_SIZE "${ROMODULAR_AVR_TOOLCHAIN_PREFIX}-size"
        HINTS "${ROMODULAR_AVR_TOOLCHAIN_ROOT}/bin" REQUIRED)

    add_custom_command(TARGET CPSTLAvrSmoke POST_BUILD
        COMMAND "${CPSTL_AVR_OBJCOPY}" -O ihex -R .eeprom
            "$<TARGET_FILE:CPSTLAvrSmoke>"
            "$<TARGET_FILE_DIR:CPSTLAvrSmoke>/CPSTLAvrSmoke.hex"
        COMMAND "${CPSTL_AVR_SIZE}" "$<TARGET_FILE:CPSTLAvrSmoke>"
        VERBATIM
    )
#
#####################################################################################################
