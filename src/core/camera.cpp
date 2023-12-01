#include "camera.h"


Camera::Camera()
{
    position = {320, 240, 0};
}

Camera::~Camera() {}

SDL_Rect Camera::get_destination_rect(vec3D obj_pos, int h, int w)
{
    SDL_Rect result;

    result.x = position.x + obj_pos.x;
    result.y = position.y + obj_pos.y;
    result.h = h;
    result.w = w;

    return result;
}

void Camera::set_camera_position(vec3D pos)
{
    position = pos;
}
