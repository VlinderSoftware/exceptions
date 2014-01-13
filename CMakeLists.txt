cmake_minimum_required(VERSION 2.8.4)

project(exceptions)
set(EXCEPTIONS_VERSION_MAJOR 1)
set(EXCEPTIONS_VERSION_MINOR 1)
set(EXCEPTIONS_VERSION_REVISION 00)
set(EXCEPTIONS_VERSION_SPECIAL alpha1)

enable_testing()
include(Dart)

if(WIN32)
	set(EXCEPTIONS_TARGET_PLATFORM_NAME win32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -DEXCEPTIONS_EXPORTS)
else()
	set(EXCEPTIONS_TARGET_PLATFORM_NAME other)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_library(exceptions SHARED
	contract.${EXCEPTIONS_TARGET_PLATFORM_NAME}.cpp)
if (${PROJECT_BINARY_DIR} STREQUAL ${CMAKE_BINARY_DIR})
else()
	if (CYGWIN)
		add_custom_command(
			TARGET exceptions
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/cygexceptions.dll" "${CMAKE_BINARY_DIR}/cygexceptions.dll"
			VERBATIM
			)
	elseif (WIN32)
		add_custom_command(
			TARGET exceptions
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/$(Configuration)/exceptions.dll" "${CMAKE_BINARY_DIR}/$(Configuration)/exceptions.dll"
			VERBATIM
			)
	endif()
endif()


foreach (test
	exceptions
	bug
	)
	add_executable(test_${test} tests/${test}.cpp)
	target_link_libraries(test_${test} exceptions ${CMAKE_THREAD_LIBS_INIT})
	add_test(test_${test} ${EXECUTABLE_OUTPUT_PATH}/test_${test})
endforeach (test)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(exceptions-doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)
