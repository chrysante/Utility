cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

# download CPM.cmake
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

project(
  utility
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES CXX)

set(CMAKE_CXX_VISIBILITY_PRESET     hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(utility SHARED)

include(GenerateExportHeader)
generate_export_header(utility
  EXPORT_MACRO_NAME UTL_API
  EXPORT_FILE_NAME include/utl/api.hpp
)

target_include_directories(utility
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include
        include
)

add_subdirectory(include/utl)
source_group(include/utl REGULAR_EXPRESSION "include/utl/*")
source_group(include/utl/__graph REGULAR_EXPRESSION "include/utl/__graph/*")
source_group(include/utl/__third_party REGULAR_EXPRESSION "include/utl/__third_party/*")
source_group(include/utl/dispatch REGULAR_EXPRESSION "include/utl/dispatch/*")

add_subdirectory(src)
source_group(src REGULAR_EXPRESSION "src/*")

if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

add_library(test-lib SHARED)
add_subdirectory(test/test-lib)

add_executable(test)
CPMAddPackage("gh:catchorg/Catch2@3.4.0")
target_include_directories(test
  PRIVATE
    include
    test
    ${Catch2_SOURCE_DIR}/src
)

target_link_libraries(test utility)
target_link_libraries(test test-lib)
target_link_libraries(test Catch2::Catch2)
target_link_libraries(test Catch2::Catch2WithMain)
add_subdirectory(test/utl)
source_group(utl REGULAR_EXPRESSION "test/utl/*")
source_group(utl/graph REGULAR_EXPRESSION "test/utl/graph/*")
source_group(utl/vector REGULAR_EXPRESSION "test/utl/vector/*")