if( ${CPSTL_TESTING}  AND ${CPSTL_VECTOR_TESTING})
    message("Appending CPSTL vector Unit Tests")
    add_subdirectory(vector)
endif() 

if( ${CPSTL_TESTING}  AND ${CPSTL_STRING_TESTING})
    message("Appending CPSTL string Unit Tests")
    add_subdirectory(string)
endif() 