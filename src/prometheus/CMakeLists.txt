find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_library(prometheus OBJECT menu.cpp world_gen.cpp start_world_gen.cpp submap_gen.cpp player.cpp)

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
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)
