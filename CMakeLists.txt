cmake_minimum_required(VERSION 3.16.3)

project(LearnOpenGL)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp)

add_executable(out ${SOURCES})

target_link_libraries(
  out
  ${SDL2_LIBRARIES}
  SDL2_image
)
