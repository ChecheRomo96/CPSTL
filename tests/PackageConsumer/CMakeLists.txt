# Builds against an installed CPSTL package:
#   cmake -S tests/PackageConsumer -B build/package-consumer -DCMAKE_PREFIX_PATH=dist/<preset>
cmake_minimum_required(VERSION 3.25)
project(CPSTLPackageConsumer LANGUAGES CXX)

find_package(CPSTL 1.1 CONFIG REQUIRED)

add_executable(CPSTLPackageConsumer main.cpp)
target_link_libraries(CPSTLPackageConsumer PRIVATE CPSTL::CPSTL)

enable_testing()
add_test(NAME CPSTLPackageConsumer COMMAND CPSTLPackageConsumer)
