cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

project(
  utility
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES CXX)

set(CMAKE_CXX_VISIBILITY_PRESET     hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

if(WIN32)
  add_compile_options("/MP")
endif()

if(utility_SHARED)
  add_library(utility SHARED)
else()
  add_library(utility STATIC)
endif()

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

set(utility_headers
  include/utl/__base.hpp
  include/utl/__debug.hpp
  include/utl/__function_objects.hpp
  include/utl/__function.hpp
  include/utl/__graph/chordal.hpp
  include/utl/__graph/find_cycle.hpp
  include/utl/__graph/greedy_color.hpp
  include/utl/__graph/scc.hpp
  include/utl/__graph/topsort.hpp
  include/utl/__wrap_iterator.hpp
  include/utl/__soa_generated.hpp
  include/utl/__third_party/ankerl/unordered_dense.h
  include/utl/bit.hpp
  include/utl/callback_iterator.hpp
  include/utl/common.hpp
  include/utl/concepts.hpp
  include/utl/dispatch/concurrent_dispatch_queue.hpp
  include/utl/dispatch/thread_pool.hpp
  include/utl/dynamic_library.hpp
  include/utl/expected.hpp
  include/utl/filesystem_ext.hpp
  include/utl/format_time.hpp
  include/utl/function_view.hpp
  include/utl/functional.hpp
  include/utl/graph.hpp
  include/utl/hash.hpp
  include/utl/hashtable.hpp
  include/utl/ilist.hpp
  include/utl/ipp.hpp
  include/utl/lazy.hpp
  include/utl/math.hpp
  include/utl/messenger.hpp
  include/utl/metric_table.hpp
  include/utl/overload.hpp
  include/utl/pimpl.hpp
  include/utl/projection.hpp
  include/utl/ptr_union.hpp
  include/utl/queue.hpp
  include/utl/scope_guard.hpp
  include/utl/stack.hpp
  include/utl/static_string.hpp
  include/utl/stopwatch.hpp
  include/utl/strcat.hpp
  include/utl/streammanip.hpp
  include/utl/structure_of_arrays.hpp
  include/utl/thread.hpp
  include/utl/tinyptrset.hpp
  include/utl/tiny_ptr_vector.hpp
  include/utl/type_traits.hpp
  include/utl/typeinfo.hpp
  include/utl/utility.hpp
  include/utl/uuid.hpp
  include/utl/vector.hpp
) 

set(utility_sources
  src/dynamic_library.cpp
  src/thread.cpp
  src/thread_pool.cpp
  src/typeinfo.cpp
  src/uuid.cpp
)

target_sources(utility PRIVATE ${utility_headers} ${utility_sources})
source_group(TREE ${PROJECT_SOURCE_DIR}/include/utl FILES ${utility_headers})
source_group(TREE ${PROJECT_SOURCE_DIR}/src FILES ${utility_sources})

if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

# download CPM.cmake
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
CPMAddPackage("gh:catchorg/Catch2@3.4.0")

add_library(test-lib SHARED test/test-lib/test.cpp)

add_executable(test)

target_include_directories(test
  PRIVATE
    include
    test
    ${Catch2_SOURCE_DIR}/src
)

target_link_libraries(test utility)
target_link_libraries(test Catch2::Catch2)
target_link_libraries(test Catch2::Catch2WithMain)
add_dependencies(test test-lib)

set(utility_test_sources
  test/utl/LifetimeCounter.cpp
  test/utl/LifetimeCounter.hpp
  test/utl/TypeCompare.h
  test/utl/callback_iterator.t.cpp
  test/utl/common.t.cpp
  test/utl/concurrent_dispatch_queue.t.cpp
  test/utl/dynamic_library.t.cpp
  test/utl/format_time.t.cpp
  test/utl/function.t.cpp
  test/utl/function_view.t.cpp
  test/utl/graph/Vertex.hpp
  test/utl/graph/chordal.t.cpp
  test/utl/graph/find_cycle.t.cpp
  test/utl/graph/greedy_color.t.cpp
  test/utl/graph/scc.t.cpp
  test/utl/graph/topsort.t.cpp
  test/utl/hashtable.t.cpp
  test/utl/ilist.t.cpp
  test/utl/ipp.t.cpp
  test/utl/lazy.t.cpp
  test/utl/math.t.cpp
  test/utl/messenger.t.cpp
  test/utl/metric_table.t.cpp
  test/utl/pimpl.t.cpp
  test/utl/projection.t.cpp
  test/utl/ptr_union.t.cpp
  test/utl/queue.t.cpp
  test/utl/scope_guard.t.cpp
  test/utl/stack.t.cpp
  test/utl/streammanip.t.cpp
  test/utl/structure_of_arrays.t.cpp
  test/utl/thread_pool.t.cpp
  test/utl/tiny_ptr_vector.t.cpp
  test/utl/tinyptrset.t.cpp
  test/utl/type_traits.t.cpp
  test/utl/utility.t.cpp
  test/utl/uuid.t.cpp
  test/utl/vector/VectorTest.hpp
  test/utl/vector/constructors.t.cpp
  test/utl/vector/insert-erase.t.cpp
  test/utl/vector/vector.t.cpp
)

target_sources(test PRIVATE ${utility_test_sources})
source_group(TREE ${PROJECT_SOURCE_DIR}/test/utl FILES ${utlity_test_sources})
