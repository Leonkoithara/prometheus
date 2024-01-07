#include "camera.h"


Camera cam;

Camera::Camera()
{
    position = {0, 0, 0};
}

Camera::~Camera() {}

SDL_Rect Camera::get_destination_rect(vec3D obj_pos, int h, int w)
{
    SDL_Rect result;

    result.x = obj_pos.x - position.x;
    result.y = obj_pos.y - position.y;
    result.h = h;
    result.w = w;

    return result;
}

void Camera::set_camera_position(vec3D pos) { position = pos; }

void Camera::camera_translate(vec3D translate)
{
    position.x += translate.x;
    position.y += translate.y;
    position.z += translate.z;
}
