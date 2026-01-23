cmake_minimum_required(VERSION 3.19)

project(gen_ips)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${CMAKE_PROJECT_NAME} src/func.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC inc)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        1da23a3e8119ec5cce4f9388e91b065e20bf06f5 # v2.4.12
)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        eddb0241389718a23a42db6af5f0164b6e0139af # v1.9.4
)

FetchContent_MakeAvailable(doctest benchmark)

add_executable(ut_gen_ips test/ut_gen_ips.cpp)
target_link_libraries(ut_gen_ips gen_ips doctest)

add_executable(gen_ips_benchmark test/benchmarks.cpp)
target_link_libraries(gen_ips_benchmark gen_ips benchmark)