######################################################################################################
# Initialize a list for all the header files in this directory

    set( HEADERS_LIST_LOCAL "" )
#
######################################################################################################
# Append Sources and Headers

    list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_cstring.cpp")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_String.h" )
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_String.tpp")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_char_traits.h" )
#
######################################################################################################
# Add Subdirectories
    
    add_subdirectory(Utilities)
#
######################################################################################################
# Refresh Sources List and Header List at PARENT_SCOPE

    set( CPSTL_SOURCES "${CPSTL_SOURCES}" PARENT_SCOPE)
#
######################################################################################################
# CPSTL String Installation

    if( ${CPSTL_INSTALL} )

        install(
            FILES ${HEADERS_LIST_LOCAL} 
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