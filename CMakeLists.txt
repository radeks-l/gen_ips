cmake_minimum_required(VERSION 3.19)

project(gen_ips)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${CMAKE_PROJECT_NAME} src/func.cpp src/main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE inc)