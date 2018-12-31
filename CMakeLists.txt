cmake_minimum_required(VERSION 3.7)
project(exceptions VERSION 1.0.00 LANGUAGES CXX)
include(${CMAKE_SOURCE_DIR}/cmake/settings.cmake)
include(GNUInstallDirs)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
set(CPACK_PACKAGE_NAME exceptions)
set(CPACK_PACKAGE_VENDOR "Vlinder Software")
set(CPACK_PACKAGE_CONTACT "Ronald Landheer-Cieslak <rlc@vlinder.ca>")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 00)
set(CPACK_PACKAGE_DESCRIPTION "Generic exceptions support library")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Generic exceptions support library")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CPack.Description.txt)
set(CPACK_PACKAGE_HOMEPAGE_URL "http://vlinder.ca")
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md)
set(CPACK_GENERATOR DEB)
include(CPack)

enable_testing()
include(CTest)
endif()

set(EXCEPTIONS_SOURCES
	bug.hpp
	contract.${VLINDER_TARGET_PLATFORM_NAME}.cpp
	contract.hpp
	details/prologue.hpp
	exception.hpp
	)

add_library(exceptions SHARED
	${EXCEPTIONS_SOURCES}
	)
set_target_properties(exceptions PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(exceptions PROPERTIES SOVERSION 1)
install(TARGETS exceptions
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
install(FILES bug.hpp contract.hpp exception.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/exceptions)
install(FILES details/prologue.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/exceptions/details)
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

