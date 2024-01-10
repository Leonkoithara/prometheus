find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(prometheus OBJECT menu.cpp world_gen.cpp submap_gen.cpp)

target_include_directories(
  prometheus
  PUBLIC
  include
  ../core/include
)
target_link_libraries(
  prometheus
  ${SDL2_LIBRARIES}
  SDL2_image
)
