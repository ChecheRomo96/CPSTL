# Warning set for CPSTL's own tests and examples. The library is header-heavy,
# so these flags also exercise its headers.
function(cpstl_enable_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor)
    endif()
    if(CPSTL_WARNINGS_AS_ERRORS)
        set_target_properties(${target} PROPERTIES COMPILE_WARNING_AS_ERROR ON)
    endif()
endfunction()

function(cpstl_add_test test_target)
    add_executable(${test_target} ${ARGN})
    # CPSTL comes through CPSTLTestSupport; linking it again makes Apple ld warn
    # about duplicate libraries.
    target_link_libraries(${test_target} PRIVATE CPSTLTestSupport GTest::gtest_main)
    cpstl_enable_warnings(${test_target})
    gtest_discover_tests(${test_target}
        TEST_PREFIX "${test_target}."
        DISCOVERY_MODE PRE_TEST
        PROPERTIES LABELS "CPSTL"
    )
endfunction()

function(cpstl_add_example example_target)
    add_executable(${example_target} ${ARGN})
    target_link_libraries(${example_target} PRIVATE CPSTL::CPSTL)
    cpstl_enable_warnings(${example_target})
    # Tutorials remain executable smoke coverage when testing is enabled, but
    # their output teaches a workflow rather than asserting unit-test cases.
    if(CPSTL_TESTING)
        add_test(NAME "example.${example_target}" COMMAND ${example_target})
        set_tests_properties("example.${example_target}" PROPERTIES LABELS "CPSTL;example")
    endif()
endfunction()
