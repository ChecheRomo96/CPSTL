######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( CPSTL_SRC_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list
    
	set(CPSTL_PRIVATE_SOURCES "")       # .cpp
    set(CPSTL_PUBLIC_INCLUDE_FILES "")  # .h + .tpp
    set(CPSTL_PRIVATE_INCLUDE_FILES "") # .h + .tpp internos
#
######################################################################################################
# Append Sources and Headers
	
	# Append Sources
	list( APPEND CPSTL_PRIVATE_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL.cpp")

	# Append Headers
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL.h")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPSTL_BuildSettings.h")
	
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPalgorithm")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPexception")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPinitializer_list")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPutility")

	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPalgorithm.h")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPexception.h")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPinitializer_list.h")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPutility.h")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPiterator.h")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPios.h")

#
######################################################################################################
# Add Subdirectories
	
	add_subdirectory(utility)
	add_subdirectory(streams)

	if( ${CPSTL_VECTOR_STATUS} )
		list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPvector")
		list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPvector.h")
		add_subdirectory(vector)
	endif()

	if( ${CPSTL_STRING_STATUS} )
		list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPstring")
		list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPstring.h")
		add_subdirectory(string)
	endif()
	

	if( ${CPSTL_ITERATOR_STATUS} )
		list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPiterator")
		list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPiterator.h")
		add_subdirectory(iterator)
	endif()

	
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPtype_traits")
	list( APPEND CPSTL_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_LIST_DIR}/CPtype_traits.h")
	add_subdirectory(type_traits)

#
######################################################################################################
# Create the CPSTL library

	message("${CPSTL_PRIVATE_SOURCES}")
	add_library( CPSTL STATIC ${CPSTL_PRIVATE_SOURCES} )


	target_compile_definitions(CPSTL PRIVATE _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
#
######################################################################################################
# Add Compliler Definitions

	if( CPSTL_USING_STL )
		message("Using STL compatibility")
		target_compile_definitions(CPSTL PUBLIC CPSTL_USING_STL)
	endif()

	if( CPSTL_ALLOCATION_METHOD STREQUAL "dummy" )
		message("No allocation method selected")
	elseif( CPSTL_ALLOCATION_METHOD STREQUAL "std" )
		message("Using std for allocation")
		target_compile_definitions(CPSTL PUBLIC CPSTL_USING_STD_ALLOCATION)
	elseif( CPSTL_ALLOCATION_METHOD STREQUAL "CPP" )
		message("Using C++ allocators (new, new[], delete, delete[]")
		target_compile_definitions(CPSTL PUBLIC CPSTL_USING_CPP_ALLOCATION)
	elseif( CPSTL_ALLOCATION_METHOD STREQUAL "C" )
		message("Using C allocators (malloc, calloc, free)")
		target_compile_definitions(CPSTL PUBLIC CPSTL_USING_C_ALLOCATION)
	endif()

	if( CPSTL_EXCEPTIONS )
		message("CPSTL exceptions enabled")
		target_compile_definitions(CPSTL PUBLIC CPSTL_EXCEPTIONS_ENABLED)
	endif()

	if( CPSTL_VECTOR_STATUS )
		message("CPSTL::vector enabled")
		target_compile_definitions(CPSTL PUBLIC CPSTL_VECTOR_ENABLED)
	endif()


	if( CPSTL_STRING_STATUS )

		message("CPSTL::string enabled")
		target_compile_definitions(CPSTL PUBLIC CPSTL_STRING_ENABLED)

		if( CPSTL_ENABLE_UNICODE_STRINGS )
			message("Unicode string support enabled")
			target_compile_definitions(CPSTL PUBLIC CPSTL_ENABLE_UNICODE_STRINGS)
		endif()
	endif()
#
######################################################################################################
# Include directories for install and for build 

	target_sources(CPSTL PRIVATE
		${CPSTL_PRIVATE_INCLUDE_FILES}
		${CPSTL_PUBLIC_INCLUDE_FILES}
	)
	
	target_include_directories(
		CPSTL PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/CPSTL-${CPSTL_VERSION}>
	)
#
######################################################################################################
# CPSTL install process

	if(NOT CPSTL_BUILD_TARGET STREQUAL "Dev" AND NOT CPSTL_BUILD_TARGET STREQUAL "Submodule")

		install(
			FILES ${CPSTL_PUBLIC_INCLUDE_FILES}
			DESTINATION "include/CPSTL-${CPSTL_VERSION}"
		)
		
	endif()
#
######################################################################################################