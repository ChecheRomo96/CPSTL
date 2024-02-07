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

    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_TypeTraits.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_TypeTraits_HelperClasses.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_TypeTraits_PrimaryTypeCategories.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_TypeTraits_CompositeTypeCategories.h")
    list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPSTL_TypeTraits_TypeProperties.h")
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