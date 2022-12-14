cmake_minimum_required(VERSION 3.10)

project(poaky)

## Compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2 -Wextra -march=native")
set(CMAKE_BUILD_TYPE "Release")

## Folders
set(CMAKE_SOURCE_DIR ${CMAKE_BINARY_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

Include(FetchContent)
## Main
FetchContent_Declare(
  Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(EIGEN_BUILD_DOC OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)
FetchContent_MakeAvailable(Eigen)

file(GLOB_RECURSE SOURCES ./src/*.cpp)
add_library(Source INTERFACE)
target_include_directories(Source INTERFACE ./src)

add_executable(main ./main.cpp ${SOURCES})
target_link_libraries(main PRIVATE Source Eigen3::Eigen)

## Test
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.2.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TEST_SRC ./test/*.cpp)
add_library(Test_src INTERFACE)
target_include_directories(Test_src INTERFACE ./test)

add_executable(test ./test/test_main.cpp ${SOURCES} ${TEST_SRC})
target_link_libraries(test PRIVATE Catch2::Catch2WithMain
                                   Source Test_src Eigen3::Eigen)

## Benchmark
add_library(Benchmark INTERFACE)
target_include_directories(Benchmark INTERFACE ./benchmark)
add_executable(benchmark ./benchmark/benchmark.cpp ${SOURCES})
target_link_libraries(benchmark PRIVATE Catch2::Catch2WithMain
                                        Source Benchmark Eigen3::Eigen)

## Test coverage
include(CodeCoverage)
add_executable(coverage ${SOURCES} ${TEST_SRC})
target_link_libraries(coverage PRIVATE Catch2::Catch2WithMain
                                       Source Test_src Eigen3::Eigen)
target_compile_options(coverage PRIVATE 
                       -O0 -Wall -fprofile-arcs -ftest-coverage)
setup_target_for_coverage_gcovr_html(
  NAME coverage_report
  EXECUTABLE coverage
  BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
  EXCLUDE "test/*" "build/_deps/*")

