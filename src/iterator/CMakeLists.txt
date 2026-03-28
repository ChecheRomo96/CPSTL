######################################################################################################
# Initialize Lists

	set(PRIVATE_SOURCES "")       # .cpp
    set(PUBLIC_INCLUDE_FILES "")  # .h + .tpp
    set(PRIVATE_INCLUDE_FILES "") # .h + .tpp internos
#
######################################################################################################
# Append Sources and Headers
    
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_Iterator.h")
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_iterator_functions.h")
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_iterator_traits.h")
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_predefined_iterators.h")
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_reverse_iterator.h")
    list( APPEND PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_back_insert_iterator.h")
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
# Append Sources and Headers


    #add_subdirectory(type_traits)

#
######################################################################################################
# CPSTL Vector Installation

    if( ${CPSTL_INSTALL} )

        install(
            FILES ${PUBLIC_INCLUDE_FILES} 
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