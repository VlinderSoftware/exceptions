cmake_minimum_required(VERSION 2.8.4)

project(exceptions)
set(EXCEPTIONS_VERSION_MAJOR 1)
set(EXCEPTIONS_VERSION_MINOR 1)
set(EXCEPTIONS_VERSION_REVISION 00)
set(EXCEPTIONS_VERSION_SPECIAL alpha1)

option(EXCEPTIONS_BUILD_FOR_RELACY OFF)

enable_testing()
include(Dart)

if(WIN32)
	set(EXCEPTIONS_TARGET_PLATFORM_NAME win32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -DEXCEPTIONS_EXPORTS)
else()
	set(EXCEPTIONS_TARGET_PLATFORM_NAME other)
endif()

if (EXCEPTIONS_BUILD_FOR_RELACY)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/relacy/relacy_2_4)
endif()

set(EXCEPTIONS_SOURCES
	contract.${EXCEPTIONS_TARGET_PLATFORM_NAME}.cpp
	)

add_library(exceptions SHARED
	${EXCEPTIONS_SOURCES}
	)
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
add_library(exceptions_relacy SHARED
	${EXCEPTIONS_SOURCES}
	)
if (WIN32)
	set_target_properties(exceptions_relacy
		PROPERTIES COMPILE_FLAGS "/FI${CMAKE_SOURCE_DIR}\\tests\\relacy.hpp /wd4290"
		)
else()
	set_target_properties(exceptions_relacy
		PROPERTIES COMPILE_FLAGS "-include tests/relacy.hpp"
		)
	if (WIN32)
		set_target_properties(exceptions_relacy
			PROPERTIES COMPILE_FLAGS "/FI${CMAKE_SOURCE_DIR}\\tests\\relacy.hpp /wd4290"
			)
	else()
		set_target_properties(exceptions_relacy
			PROPERTIES COMPILE_FLAGS "-include tests/relacy.hpp"
			)
	endif()
endif()
endif()
if (${PROJECT_BINARY_DIR} STREQUAL ${CMAKE_BINARY_DIR})
else()
	if (CYGWIN)
		add_custom_command(
			TARGET exceptions
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/cygexceptions.dll" "${CMAKE_BINARY_DIR}/cygexceptions.dll"
			VERBATIM
			)
		if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
		add_custom_command(
			TARGET exceptions_relacy
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/cygexceptions_relacy.dll" "${CMAKE_BINARY_DIR}/cygexceptions_relacy.dll"
			VERBATIM
			)
		endif()
	elseif (WIN32)
		add_custom_command(
			TARGET exceptions
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/$(Configuration)/exceptions.dll" "${CMAKE_BINARY_DIR}/$(Configuration)/exceptions.dll"
			VERBATIM
			)
		if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
		add_custom_command(
			TARGET exceptions_relacy
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_BINARY_DIR}/$(Configuration)/exceptions_relacy.dll" "${CMAKE_BINARY_DIR}/$(Configuration)/exceptions_relacy.dll"
			VERBATIM
			)
		endif()
	endif()
endif()

if (${PROJECT_BINARY_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	foreach (test
		exceptions
		bug
		)
		add_executable(test_${test} tests/${test}.cpp)
		target_link_libraries(test_${test} exceptions ${CMAKE_THREAD_LIBS_INIT})
		add_test(test_${test} ${EXECUTABLE_OUTPUT_PATH}/test_${test})
	endforeach (test)
endif()

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
