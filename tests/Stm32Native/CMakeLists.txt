add_executable(CPSTLStm32Native main.cpp)
include("${PROJECT_SOURCE_DIR}/tools/RoModularBuild/cmake/boards/STM32G0B1CBT6.cmake")
romodular_configure_stm32g0b1cbt6(CPSTLStm32Native)
target_link_libraries(CPSTLStm32Native PRIVATE CPSTL::CPSTL)
target_compile_definitions(CPSTLStm32Native PRIVATE
    CPSTL_STM32_NATIVE
    CPSTL_HW_BUILD_ID=${CPSTL_STM32_BUILD_ID}UL
    $<$<BOOL:${CPSTL_STM32_INJECT_FAILURE}>:CPSTL_HW_INJECT_FAILURE>)
target_compile_options(CPSTLStm32Native PRIVATE -Os)
if(NOT CPSTL_ALLOCATION STREQUAL "STD")
    target_compile_options(CPSTLStm32Native PRIVATE -ffreestanding)
endif()
cpstl_enable_warnings(CPSTLStm32Native)
