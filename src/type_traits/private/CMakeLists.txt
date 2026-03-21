######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

    set( CPSTL_VECTOR_SRC_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list

    set(CPSTL_PRIVATE_SOURCES "")       # .cpp
    set(CPSTL_PUBLIC_INCLUDE_FILES "")  # .h + .tpp
    set(CPSTL_PRIVATE_INCLUDE_FILES "") # .h + .tpp internos
#
######################################################################################################
# Append Sources and Headers

    list( APPEND CPSTL_PRIVATE_HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/type_traits.h")
#
######################################################################################################
# CPSTL Vector Installation

    if( ${CPSTL_INSTALL} )

        install(
            FILES ${HEADERS_LIST_LOCAL} 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPSTL/utility/type_traits 
        )

        install(
            TARGETS CPSTL 
            EXPORT CPSTLExport
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/utility/type_traits 
        )

        install(
            EXPORT CPSTLExport
            FILE CPSTL-config.cmake
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/utility/type_traits 
        )
    endif()
#
######################################################################################################