#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>

typedef struct
{
	float x;
	float y;
	float z;
}vec3D;

class GameObject
{
private:
	const char *name;
	vec3D position = {30, 30, 30};
	SDL_Rect src_rect = {0, 0, 0, 0};
	SDL_Rect dest_rect = {0, 0, 0, 0};
	SDL_Texture *texture;
public:
    GameObject(const char*, SDL_Renderer*, const char*);
    ~GameObject();

	virtual void start() {}
	virtual void update() {}

	void set_render_props(int tex_x1 = 0, int tex_y1 = 0, int h = 0, int w = 0, int scale_x = 1, int scale_y = 1);

	const char* get_name() { return name; }
	SDL_Texture* get_texture() { return texture; }
	SDL_Rect get_src_render_rect() { return src_rect; }
	SDL_Rect get_dest_render_rect() { return dest_rect; }
	vec3D get_position() { return position; }

	void set_position(vec3D pos) { position = pos; }
};
#endif
