#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
	float x;
	float y;
	float z;
}vec3D;

class GameObject
{
private:
	vec3D position = {30, 30, 30};
	vec3D size = {50, 50, 50};
	SDL_Texture *texture;
public:
    GameObject(SDL_Renderer*, const char*);
    ~GameObject();

	void update();

	SDL_Texture* get_texture() { return texture; }
	vec3D get_size() { return size; }
	vec3D get_position() { return position; }
};
#endif
