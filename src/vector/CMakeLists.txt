######################################################################################################
# Append Sources and Headers

    list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_Vector.h")
#
######################################################################################################
# Append Sources and Headers

    set(CPSTL_PRIVATE_SOURCES ${CPSTL_PRIVATE_SOURCES} PARENT_SCOPE)
    set(CPSTL_PUBLIC_INCLUDE_FILES ${CPSTL_PUBLIC_INCLUDE_FILES} PARENT_SCOPE)
    set(CPSTL_PRIVATE_INCLUDE_FILES ${CPSTL_PRIVATE_INCLUDE_FILES} PARENT_SCOPE)
#
######################################################################################################
# CPSTL Vector Installation

    if( CPSTL_INSTALL )

        install(
            FILES ${CPSTL_PUBLIC_INCLUDE_FILES} 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPSTL/vector 
        )

        install(
            TARGETS CPSTL 
            EXPORT CPSTLExport
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/vector
        )

        install(
            EXPORT CPSTLExport
            FILE CPSTL-config.cmake
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/vector
        )
    endif()
#
######################################################################################################