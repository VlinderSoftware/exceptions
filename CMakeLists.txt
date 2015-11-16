cmake_minimum_required(VERSION 2.8.4)
project(exceptions)
include(${CMAKE_SOURCE_DIR}/cmake/settings.cmake)

option(EXCEPTIONS_BUILD_FOR_RELACY OFF)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
include(Dart)
endif()

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
	contract.hpp
	exception.hpp
	)

add_library(exceptions SHARED
	${EXCEPTIONS_SOURCES}
	)
if (EXCEPTIONS_BUILD_FOR_RELACY)
	if (WIN32)
		add_library(exceptions_relacy SHARED
			${EXCEPTIONS_SOURCES}
			)
		set_target_properties(exceptions_relacy
			PROPERTIES COMPILE_FLAGS "/FI${CMAKE_SOURCE_DIR}\\tests\\relacy.hpp /wd4290"
			)
	else()
		add_library(exceptions_relacy SHARED
			${EXCEPTIONS_SOURCES}
			)
		set_target_properties(exceptions_relacy
			PROPERTIES COMPILE_FLAGS "-include ${CMAKE_SOURCE_DIR}/tests/relacy.hpp"
			)
	endif()
endif()

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
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

