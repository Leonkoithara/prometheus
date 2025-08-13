find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(core OBJECT game_manager.cpp game_object.cpp scene.cpp button.cpp)

target_include_directories(core PUBLIC include)
target_link_libraries(
  core
  ${SDL2_LIBRARIES}
  SDL2_image
  SDL2_ttf
)
