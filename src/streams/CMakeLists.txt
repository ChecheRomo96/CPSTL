######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list

    set( HEADERS_LIST_LOCAL "" )
#
######################################################################################################
# Append Sources and Headers

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_ios_base.h")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_ios.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_ios.tpp")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_fpos.h")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_streambuf.h")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_ostream.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_ostream.tpp")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_istream.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_istream.tpp")

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_iostream.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_basic_iostream.tpp")


    list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_ios_base.cpp")
    list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_ostream.cpp")
    list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_istream.cpp")
    list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_iostream.cpp")

    #add_subdirectory(type_traits)

#
######################################################################################################
# Refresh Sources List and Header List at PARENT_SCOPE

    set( CPSTL_SOURCES "${CPSTL_SOURCES}" PARENT_SCOPE)
#
######################################################################################################
# CPSTL Vector Installation

    if( ${CPSTL_INSTALL} )

        install(
            FILES ${HEADERS_LIST_LOCAL} 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPSTL/streams 
        )

        install(
            TARGETS CPSTL 
            EXPORT CPSTLExport
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/streams
        )

        install(
            EXPORT CPSTLExport
            FILE CPSTL-config.cmake
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPSTL/streams
        )
    endif()
#
######################################################################################################