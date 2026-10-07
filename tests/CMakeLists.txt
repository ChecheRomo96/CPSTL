add_library(CPSTLTestSupport STATIC TestSupport.cc)
target_link_libraries(CPSTLTestSupport PUBLIC CPSTL::CPSTL)

cpstl_add_test(CPSTLTypeTraitsTests CPSTL_type_traits.cc)
cpstl_add_test(CPSTLIteratorTests
    CPSTL_iterator/CPSTL_iterator_type_traits.cc
    CPSTL_iterator_functions.cc)
cpstl_add_test(CPSTLUtilityTests CPSTL_utility.cc)
cpstl_add_test(CPSTLLimitsTests CPSTL_limits.cc)
cpstl_add_test(CPSTLAlgorithmTests CPSTL_algorithm.cc)
cpstl_add_test(CPSTLMemoryTests CPSTL_memory.cc)

if(CPSTL_VECTOR)
    cpstl_add_test(CPSTLVectorTests CPSTL_vector.cc CPSTL_vector_robustness.cc)
endif()

if(CPSTL_STRING)
    cpstl_add_test(CPSTLStringTests CPSTL_string.cc)
endif()

if(CPSTL_STACK OR CPSTL_QUEUE)
    cpstl_add_test(CPSTLAdapterTests CPSTL_stack.cc CPSTL_queue.cc)
endif()

# Plain executable at CPSTL_CXX_STANDARD: the GoogleTest suites above need C++17.
add_executable(CPSTLHeaderCheck HeaderCheck.cpp)
target_link_libraries(CPSTLHeaderCheck PRIVATE CPSTL::CPSTL)
cpstl_enable_warnings(CPSTLHeaderCheck)
add_test(NAME CPSTLHeaderCheck COMMAND CPSTLHeaderCheck)
set_tests_properties(CPSTLHeaderCheck PROPERTIES LABELS "CPSTL")
