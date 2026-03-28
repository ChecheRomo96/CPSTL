######################################################################################################
# Initialize Lists

	set(PRIVATE_SOURCES "")       # .cpp
    set(PUBLIC_INCLUDE_FILES "")  # .h + .tpp
    set(PRIVATE_INCLUDE_FILES "") # .h + .tpp internos
#
######################################################################################################
# Append Sources and Headers
    
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_String.h" )
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_CharTraits.h" )
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_CharTraits.tpp" )
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_string.h" )
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_string.tpp" )
#
######################################################################################################
# Refrehsh list at parent scope

    list( APPEND CPSTL_PRIVATE_SOURCES "${PRIVATE_SOURCES}")
    list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${PUBLIC_INCLUDE_FILES}")
    list( APPEND CPSTL_PRIVATE_INCLUDE_FILES "${PRIVATE_INCLUDE_FILES}")

    set(CPSTL_PRIVATE_SOURCES ${CPSTL_PRIVATE_SOURCES} PARENT_SCOPE)
    set(CPSTL_PUBLIC_INCLUDE_FILES ${CPSTL_PUBLIC_INCLUDE_FILES} PARENT_SCOPE)
    set(CPSTL_PRIVATE_INCLUDE_FILES ${CPSTL_PRIVATE_INCLUDE_FILES} PARENT_SCOPE)
#
######################################################################################################
# CPSTL String Installation

    if( ${CPSTL_INSTALL} )

        install(
            FILES ${PUBLIC_INCLUDE_FILES} 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPSTL/string 
        )

        install(
            TARGETS CPSTL 
            EXPORT CPSTLExport
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/string
        )

        install(
            EXPORT CPSTLExport
            FILE CPSTL-config.cmake
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/string
        )
    endif()
#
######################################################################################################