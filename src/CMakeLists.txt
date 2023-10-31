######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( CPSTL_SRC_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list

	set( CPSTL_SOURCES "" )
	set( HEADERS_LIST "" )

#
######################################################################################################
# Append Sources and Headers
	
	# Append Sources
	list( APPEND CPSTL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/CPSTL.cpp")

	# Append Headers
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPSTL.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPSTL_BuildSettings.h")
	
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPalgorithm")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPexception")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPinitializer_list")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPutility")

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPalgorithm.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPexception.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPinitializer_list.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPutility.h")

#
######################################################################################################
# Add Subdirectories
	
	add_subdirectory(utility)

	if( ${CPSTL_VECTOR_STATUS} )
		list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPvector")
		list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPvector.h")
		add_subdirectory(vector)
	endif()

	if( ${CPSTL_STRING_STATUS} )
		list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPstring")
		list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPstring.h")
		add_subdirectory(string)
	endif()
#
######################################################################################################
# Create the CPSTL library

	message("${CPSTL_SOURCES}")
	add_library( CPSTL STATIC ${CPSTL_SOURCES} )
#
######################################################################################################
# Add Compliler Definitions

	if( ${CPSTL_EXCEPTIONS} )
		message("CPSTL exceptions enabled")
		target_compile_definitions(CPSTL PUBLIC CPSTL_EXCEPTIONS_ENABLED)
	endif()

	if( ${CPSTL_VECTOR_STATUS} )

		message("CPSTL::vector enabled")
		target_compile_definitions(CPSTL PUBLIC CPSTL_VECTOR_ENABLED)

		if( ${CPSTL_VECTOR_ALLOCATION_METHOD} STREQUAL "dummy" )
			message("No allocation method selected")
		elseif( ${CPSTL_VECTOR_ALLOCATION_METHOD} STREQUAL "std::vector" )
			message("Using std::vector for allocation")
			target_compile_definitions(CPSTL PUBLIC CPSTL_VECTOR_USING_STD_ALLOCATION)
		elseif( ${CPSTL_VECTOR_ALLOCATION_METHOD} STREQUAL "CPP" )
			message("Using C++ allocators (new, new[], delete, delete[]")
			target_compile_definitions(CPSTL PUBLIC CPSTL_VECTOR_USING_CPP_ALLOCATION)
		elseif( ${CPSTL_VECTOR_ALLOCATION_METHOD} STREQUAL "C" )
			message("Using C allocators (malloc, calloc, free)")
			target_compile_definitions(CPSTL PUBLIC CPSTL_VECTOR_USING_C_ALLOCATION)
		endif()
	endif()


	if( ${CPSTL_STRING_STATUS} )

		message("CPSTL::string enabled")
		target_compile_definitions(CPSTL PUBLIC CPSTL_STRING_ENABLED)

		if( ${CPSTL_STRING_ALLOCATION_METHOD} STREQUAL "dummy" )
			message("No allocation method selected")
		elseif( ${CPSTL_STRING_ALLOCATION_METHOD} STREQUAL "std::string" )
			message("Using std::string for allocation")
			target_compile_definitions(CPSTL PUBLIC CPSTL_STRING_USING_STD_ALLOCATION)
		elseif( ${CPSTL_STRING_ALLOCATION_METHOD} STREQUAL "CPP" )
			message("Using C++ allocators (new, new[], delete, delete[]")
			target_compile_definitions(CPSTL PUBLIC CPSTL_STRING_USING_CPP_ALLOCATION)
		elseif( ${CPSTL_STRING_ALLOCATION_METHOD} STREQUAL "C" )
			message("Using C allocators (malloc, calloc, free)")
			target_compile_definitions(CPSTL PUBLIC CPSTL_STRING_USING_C_ALLOCATION)
		endif()
	endif()
#
######################################################################################################
# Include directories for install and for build 

	target_include_directories( 
		CPSTL 
		PUBLIC 
		"$<BUILD_INTERFACE:${CPSTL_SRC_DIRECTORY}>"
		#"$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>"
	)
#
######################################################################################################
# CPSTL install process

	if(NOT CPSTL_BUILD_TARGET STREQUAL "Dev" AND NOT CPSTL_BUILD_TARGET STREQUAL "Submodule")

		install(
			FILES ${HEADERS_LIST}
			DESTINATION "include/CPSTL-${CPSTL_VERSION}"
		)
		
	endif()
#
######################################################################################################