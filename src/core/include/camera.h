#ifndef CAMERA
#define CAMERA

#include <SDL2/SDL_rect.h>

#include "type_structs.h"


class Camera
{
private:
    vec3D position;
public:
    Camera();
    ~Camera();

    SDL_Rect get_destination_rect(vec3D, int, int);

    void set_camera_position(vec3D);
};

#endif
