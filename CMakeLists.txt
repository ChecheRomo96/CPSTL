#####################################################################################################
# CPSTL: Cross-Platform STL

    cmake_minimum_required(VERSION 3.25)

    project(CPSTL VERSION 1.1.1 LANGUAGES CXX)

    # library.properties (Arduino) and CPSTL_BuildSettings.h (IDE builds)
    # carry the same version; refuse to configure when they drift.
    file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/library.properties" CPSTL_ARDUINO_VERSION_LINE
        REGEX "^version=" LIMIT_COUNT 1)
    string(REGEX REPLACE "^version=" "" CPSTL_ARDUINO_VERSION "${CPSTL_ARDUINO_VERSION_LINE}")
    if(NOT CPSTL_ARDUINO_VERSION STREQUAL PROJECT_VERSION)
        message(FATAL_ERROR "Version mismatch: CMake declares ${PROJECT_VERSION}, "
            "library.properties declares ${CPSTL_ARDUINO_VERSION}")
    endif()

    file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/src/CPSTL_BuildSettings.h" CPSTL_SOURCE_VERSION_LINE
        REGEX "#define[ \t]+CPSTL_VERSION[ \t]+\"[^\"]+\"" LIMIT_COUNT 1)
    if(NOT CPSTL_SOURCE_VERSION_LINE MATCHES "\"([^\"]+)\"" OR
       NOT CMAKE_MATCH_1 STREQUAL PROJECT_VERSION)
        message(FATAL_ERROR "Version mismatch: CMake declares ${PROJECT_VERSION}, "
            "CPSTL_BuildSettings.h declares '${CMAKE_MATCH_1}'")
    endif()

    include(CMakePackageConfigHelpers)
    include(GNUInstallDirs)
    include(CMakeOptions.cmake)
    include(cmake/CPSTLHelpers.cmake)

    set(CMAKE_CXX_STANDARD ${CPSTL_CXX_STANDARD})
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

    message(STATUS "CPSTL ${PROJECT_VERSION}: C++${CPSTL_CXX_STANDARD}, "
        "STL mode ${CPSTL_USING_STL}, allocation ${CPSTL_ALLOCATION}, "
        "vector ${CPSTL_VECTOR}, string ${CPSTL_STRING}, "
        "stack ${CPSTL_STACK}, queue ${CPSTL_QUEUE}")
#
#####################################################################################################
# Library

    add_subdirectory(src)
#
#####################################################################################################
# Examples and tests

    # Tests first: examples register themselves as CTest smoke tests when
    # testing is enabled.
    if(CPSTL_TESTING)
        include(cmake/BuildTests.cmake)
        add_subdirectory(tests)
    endif()

    if(CPSTL_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if(CPSTL_AVR_SMOKE)
        add_subdirectory(tests/AvrSmoke)
    endif()
#
#####################################################################################################
# Package

    install(TARGETS CPSTL
        EXPORT CPSTLTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CPSTL"
    )

    install(EXPORT CPSTLTargets
        NAMESPACE CPSTL::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CPSTL"
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_LIST_DIR}/cmake/CPSTLConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/CPSTLConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CPSTL"
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/CPSTLConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CPSTLConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CPSTLConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CPSTL"
    )

    # A standalone CPSTL package carries its documents at the prefix root.
    # Built inside another project (FetchContent), they go to share/doc/CPSTL
    # so they do not replace that project's own LICENSE, README and CHANGELOG.
    if(PROJECT_IS_TOP_LEVEL)
        set(CPSTL_DOC_DESTINATION ".")
    else()
        set(CPSTL_DOC_DESTINATION "${CMAKE_INSTALL_DATADIR}/doc/CPSTL")
    endif()
    install(FILES
        "${CMAKE_CURRENT_LIST_DIR}/LICENSE"
        "${CMAKE_CURRENT_LIST_DIR}/README.md"
        "${CMAKE_CURRENT_LIST_DIR}/CHANGELOG.md"
        DESTINATION "${CPSTL_DOC_DESTINATION}"
    )
#
#####################################################################################################
