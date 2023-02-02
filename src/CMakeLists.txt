add_subdirectory(core)
add_subdirectory(prometheus)

add_executable(out main.cpp)
target_include_directories(
  out
  PUBLIC
  core/include
  prometheus/include
)
target_link_libraries(
  out
  core
  prometheus
)
