cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(use-exceptions
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(exceptions 1 REQUIRED CONFIG)
if(exceptions_FOUND)
  get_property(_loc TARGET exceptions::exceptions-shared PROPERTY LOCATION)
  message(STATUS "Found exceptions: ${_loc} (found version ${exceptions_VERSION})")
  foreach(prop IN ITEMS
      IMPORTED_LOCATION_DEBUG IMPORTED_LOCATION_RELEASE
      IMPORTED_IMPLIB_DEBUG IMPORTED_IMPLIB_RELEASE)
    get_target_property(_item_loc exceptions::exceptions-shared ${prop})
    if(_item_loc)
      get_filename_component(_item_loc ${_item_loc} DIRECTORY)
      list(APPEND _locations ${_item_loc})
    endif()
  endforeach()
endif()

include(CMakePrintHelpers)
cmake_print_properties(
  TARGETS
    exceptions::exceptions-shared
  PROPERTIES
    LOCATION
    IMPORTED_LOCATION_DEBUG
    IMPORTED_LOCATION_RELEASE
    IMPORTED_IMPLIB_DEBUG
    IMPORTED_IMPLIB_RELEASE
    INTERFACE_COMPILE_DEFINITIONS
    INTERFACE_COMPILE_OPTIONS
    INTERFACE_INCLUDE_DIRECTORIES
    INTERFACE_LINK_LIBRARIES
  )

cmake_print_properties(
  TARGETS
    exceptions::exceptions-static
  PROPERTIES
    LOCATION
    IMPORTED_LOCATION_DEBUG
    IMPORTED_LOCATION_RELEASE
    IMPORTED_IMPLIB_DEBUG
    IMPORTED_IMPLIB_RELEASE
    INTERFACE_COMPILE_DEFINITIONS
    INTERFACE_COMPILE_OPTIONS
    INTERFACE_INCLUDE_DIRECTORIES
    INTERFACE_LINK_LIBRARIES
  )

add_executable(use_exceptions use_exceptions.cpp)

target_link_libraries(use_exceptions exceptions::exceptions-shared)

enable_testing()

add_test(
  NAME check_use_exceptions
  COMMAND $<TARGET_FILE:use_exceptions>
  )

if(WIN32)
  list(APPEND _locations $ENV{PATH})
  string(REPLACE ";" "\;" _locations "${_locations}")
  set_tests_properties(check_use_exceptions
    PROPERTIES
      ENVIRONMENT "PATH=${_locations}"
    )
endif()
