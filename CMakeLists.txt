cmake_minimum_required(VERSION 2.8.4)

project(exceptions)
set(EXCEPTIONS_VERSION_MAJOR 1)
set(EXCEPTIONS_VERSION_MINOR 1)
set(EXCEPTIONS_VERSION_REVISION 00)
set(EXCEPTIONS_VERSION_SPECIAL alpha1)

enable_testing()
include(Dart)

if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_library(libexceptions 
	Contract.cpp)

add_executable(test_exceptions test.cpp)
target_link_libraries(test_exceptions libexceptions)

add_test(test_exceptions ${EXECUTABLE_OUTPUT_PATH}/test_exceptions)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)
