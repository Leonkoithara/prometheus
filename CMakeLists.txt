cmake_minimum_required(VERSION 3.16.3)

project(prometheus)

set(CMAKE_BUILD_TYPE Debug)

set(CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(src build)
