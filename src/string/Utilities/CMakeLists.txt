######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

    set( CPSTL_VECTOR_SRC_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize a list for all the header files in this directory

    set( HEADERS_LIST_LOCAL "" )
#
######################################################################################################
# Append Sources and Headers

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_String_Utilities.h" )
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_String_toString.h" )
    
    list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_String_toString.cpp")
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
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPSTL/string/Utilities
        )

        install(
            TARGETS CPSTL 
            EXPORT CPSTLExport
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/string/Utilities
        )

        install(
            EXPORT CPSTLExport
            FILE CPSTL-config.cmake
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/string/Utilities
        )
    endif()
#
######################################################################################################