######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

    set( CPSTL_VECTOR_SRC_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list

    set( HEADERS_LIST_LOCAL "" )
#
######################################################################################################
# Append Sources and Headers

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_Move.h")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_Iterator.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_types.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_allocator.h")

    add_subdirectory(type_traits)

#
######################################################################################################
# CPSTL Vector Installation

    if( ${CPSTL_INSTALL} )

        install(
            FILES ${HEADERS_LIST_LOCAL} 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPSTL/utility 
        )

        install(
            TARGETS CPSTL 
            EXPORT CPSTLExport
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/utility
        )

        install(
            EXPORT CPSTLExport
            FILE CPSTL-config.cmake
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/utility
        )
    endif()
#
######################################################################################################