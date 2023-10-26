######################################################################################################
# Setting up the project

	##################################################################################################
	# C Make Minimum Version
		
		cmake_minimum_required(VERSION 3.14)
	#
	##################################################################################################
	# Project Name Version and Languaje, print and add preprocessor flag
		
		project(CPSTL VERSION 1.0.0 LANGUAGES CXX)
		message(STATUS "Building ${PROJECT_NAME} Version = ${PROJECT_VERSION}...")

		string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
	#
	##################################################################################################
	# Set up C++ Version

		set(CMAKE_CXX_STANDARD 17) 
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	#
	##################################################################################################
#
######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( ${PROJECT_NAME_UPPER}_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} )
#
######################################################################################################
# Compile Configuration
	
	set(CPSTL_BUILD_TARGET "Submodule" CACHE STRING "CPString build target")
	set_property(CACHE CPSTL_BUILD_TARGET PROPERTY STRINGS "Dev" "Submodule" "Export" "Install")

	set(CPSTL_EXCEPTIONS FALSE CACHE BOOL "") # Enables the compilation of the Exceptions module

	set(CPSTL_EXAMPLES FALSE CACHE BOOL "") # Enables Building Examples
	set(CPSTL_TESTING FALSE CACHE BOOL "") # Enabled Unit Testing

	##################################################################################################
	# Vector configuration

		option(CPSTL_VECTOR_STATUS "Enables the compilation of cpstd::vector<T>" FALSE)

		option(CPSTL_VECTOR_EXCEPTIONS "Enables the compilation of the Exceptions module" FALSE)
		option(CPSTL_VECTOR_EXAMPLES "Enables Building Examples" FALSE)
		option(CPSTL_VECTOR_TESTING "Enabled Unit Testing" FALSE)

		set(CPSTL_VECTOR_ALLOCATION_METHOD "dummy" CACHE STRING "CPVector allocation method")
		set_property(CACHE CPSTL_VECTOR_ALLOCATION_METHOD PROPERTY STRINGS  "dummy" "std::vector" "CPP" "C")
		
		option(CPSTL_VECTOR_SORTING "Enables the compilation of the sorting module" FALSE)
	#
	##################################################################################################
	# String configuration

		option(CPSTL_STRING_STATUS "Enables the compilation of cpstd::string" FALSE)

		option(CPSTL_STRING_EXCEPTIONS "Enable CPSTL_String exceptions" FALSE)
		option(CPSTL_STRING_EXAMPLES "Enable building examples" FALSE)
		option(CPSTL_STRING_TESTING "Enable unit testing" FALSE)
		
		set(CPSTL_STRING_ALLOCATION_METHOD "dummy" CACHE STRING "CPSTL_String allocation method")
		set_property(CACHE CPSTL_STRING_ALLOCATION_METHOD PROPERTY STRINGS "dummy" "std::string" "CPP" "C")

		option(CPSTL_STRING_ITERATORS "Enable using Iterators" FALSE)
	#
	##################################################################################################
#
######################################################################################################
# Append Source

	add_subdirectory(src)
	target_compile_definitions(CPSTL INTERFACE ${PROJECT_NAME_UPPER}_VERSION="${PROJECT_VERSION}" )
#
######################################################################################################
# Append Examples

	if( ${CPSTL_EXAMPLES} )
		message("Building ${CMAKE_PROJECT_NAME} Examples...")
		add_subdirectory(examples)
	endif()
#
######################################################################################################
# Append Tests

	if( ${CPSTL_TESTING} )
		message("Building ${CMAKE_PROJECT_NAME} Tests...")

		cmake_policy(SET CMP0135 NEW)

		include(FetchContent)

		FetchContent_Declare(
		  googletest
		  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
		)
		# For Windows: Prevent overriding the parent project's compiler/linker settings
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
		FetchContent_MakeAvailable(googletest)

		enable_testing()
		include(GoogleTest)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME_UPPER}_ROOT_DIRECTORY}/bin")
		add_subdirectory(tests)
	endif()
#
######################################################################################################
