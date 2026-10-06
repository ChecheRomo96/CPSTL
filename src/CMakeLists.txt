#####################################################################################################
# CPSTL library
#
# Every header under src/ is public. The extensionless wrappers (CPvector,
# CPstring, ...) mirror the standard header names.

    file(GLOB_RECURSE CPSTL_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/*.tpp"
    )
    file(GLOB CPSTL_WRAPPER_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/CP*")
    list(FILTER CPSTL_WRAPPER_HEADERS EXCLUDE REGEX "\\.(h|cpp)$")

    set(CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL.cpp")
    if(CPSTL_STRING)
        list(APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/string/CPSTL_String.cpp")
    endif()

    add_library(CPSTL STATIC ${CPSTL_SOURCES})
    add_library(CPSTL::CPSTL ALIAS CPSTL)

    target_sources(CPSTL PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}"
        FILES ${CPSTL_HEADERS} ${CPSTL_WRAPPER_HEADERS}
    )

    # Consumers inherit the language level and configuration CPSTL was built with.
    target_compile_features(CPSTL PUBLIC cxx_std_${CPSTL_CXX_STANDARD})

    target_compile_definitions(CPSTL PUBLIC
        CPSTL_VERSION="${PROJECT_VERSION}"
        CPSTL_USING_${CPSTL_ALLOCATION}_ALLOCATION
        $<$<BOOL:${CPSTL_USING_STL}>:CPSTL_USING_STL>
        $<$<BOOL:${CPSTL_VECTOR}>:CPSTL_VECTOR_ENABLED>
        $<$<BOOL:${CPSTL_STRING}>:CPSTL_STRING_ENABLED>
        $<$<BOOL:${CPSTL_STACK}>:CPSTL_STACK_ENABLED>
        $<$<BOOL:${CPSTL_QUEUE}>:CPSTL_QUEUE_ENABLED>
        $<$<BOOL:${CPSTL_UNICODE_STRINGS}>:CPSTL_ENABLE_UNICODE_STRINGS>
    )
#
#####################################################################################################
