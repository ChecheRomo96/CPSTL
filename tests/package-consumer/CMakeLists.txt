cmake_minimum_required(VERSION 3.25)
project(CPSTLInstalledConsumer LANGUAGES CXX)

find_package(CPSTL 1.1.8 EXACT CONFIG REQUIRED)
add_executable(cpstl_consumer main.cpp)
target_link_libraries(cpstl_consumer PRIVATE CPSTL::CPSTL)
set_target_properties(cpstl_consumer PROPERTIES
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
enable_testing()
add_test(NAME installed-package COMMAND cpstl_consumer)
