# SHARED library
add_library(exceptions-shared SHARED "")

include(GenerateExportHeader)
generate_export_header(exceptions-shared
	BASE_NAME "exceptions"
	EXPORT_MACRO_NAME "exceptions_EXPORT"
	EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/exceptions-export.h"
	DEPRECATED_MACRO_NAME "exceptions_DEPRECATED"
	NO_EXPORT_MACRO_NAME "exceptions_NO_EXPORT"
	STATIC_DEFINE "exceptions_STATIC_DEFINE"
	NO_DEPRECATED_MACRO_NAME "exceptions_NO_DEPRECATED"
	DEFINE_NO_DEPRECATED
)

if (WIN32 AND NOT CYGWIN)
	set(TARGET_PLATFORM win32)
else()
	set(TARGET_PLATFORM posix)
endif()

target_sources(exceptions-shared
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/contract.${TARGET_PLATFORM}.cpp
)

target_compile_definitions(exceptions-shared
	INTERFACE
		$<INSTALL_INTERFACE:USING_exceptions>
)

target_include_directories(exceptions-shared
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
		$<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}>
)

set_target_properties(exceptions-shared
	PROPERTIES
		POSITION_INDEPENDENT_CODE 1
		CXX_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN 1
		SOVERSION ${PROJECT_VERSION_MAJOR}
		OUTPUT_NAME "exceptions"
		DEBUG_POSTFIX "_d"
		PUBLIC_HEADER "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/exceptions-export.h;${CMAKE_CURRENT_LIST_DIR}/exception.hpp;${CMAKE_CURRENT_LIST_DIR}/contract.hpp;${CMAKE_CURRENT_LIST_DIR}/bug.hpp"
		MACOSX_RPATH ON
)

# STATIC library
add_library(exceptions-static STATIC "")

target_sources(exceptions-static
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/contract.${TARGET_PLATFORM}.cpp
)

target_compile_definitions(exceptions-static
	PUBLIC
	INTERFACE
		$<INSTALL_INTERFACE:USING_exceptions>
)

target_include_directories(exceptions-static
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
		$<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}>
)

set_target_properties(exceptions-static
	PROPERTIES
		POSITION_INDEPENDENT_CODE 1
		ARCHIVE_OUTPUT_NAME "exceptions"
		DEBUG_POSTFIX "_sd"
		RELEASE_POSTFIX "_s"
		PUBLIC_HEADER "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/exceptions-export.h;${CMAKE_CURRENT_LIST_DIR}/exception.hpp;${CMAKE_CURRENT_LIST_DIR}/contract.hpp;${CMAKE_CURRENT_LIST_DIR}/bug.hpp"
)

# <<< Install and export targets >>>

install(
	TARGETS
		exceptions-shared
		exceptions-static
	EXPORT
		exceptionsTargets
	ARCHIVE
		DESTINATION ${INSTALL_LIBDIR}
		COMPONENT lib
	RUNTIME
		DESTINATION ${INSTALL_BINDIR}
		COMPONENT bin
	LIBRARY
		DESTINATION ${INSTALL_LIBDIR}
		COMPONENT lib
	PUBLIC_HEADER
		DESTINATION ${INSTALL_INCLUDEDIR}/exceptions
		COMPONENT dev
)

install(
	EXPORT
		exceptionsTargets
	NAMESPACE
		"exceptions::"
	DESTINATION
		${INSTALL_CMAKEDIR}
	COMPONENT
		dev
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/exceptionsConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/exceptionsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/exceptionsConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
  )

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/exceptionsConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/exceptionsConfigVersion.cmake
	DESTINATION
		${INSTALL_CMAKEDIR}
)

