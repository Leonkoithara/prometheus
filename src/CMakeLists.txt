add_subdirectory(core)

add_executable(out main.cpp)
target_include_directories(
  out
  PUBLIC
  core/include
)
target_link_libraries(
  out
  core
)
