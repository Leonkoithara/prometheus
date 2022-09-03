#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
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
	std::string name;
	vec3D position;
	SDL_Rect src_rect;
	SDL_Rect dest_rect;
	SDL_Texture *texture;
public:
    GameObject(std::string);
    ~GameObject();

	virtual void start() {}
	virtual void update() {}

	void set_texturefile(SDL_Renderer *, std::string);
	void set_render_props(int tex_x1 = 0, int tex_y1 = 0, int h = 0, int w = 0, int scale_x = 1, int scale_y = 1);

	std::string get_name() { return name; }
	SDL_Texture* get_texture() { return texture; }
	SDL_Rect get_src_render_rect() { return src_rect; }
	SDL_Rect get_dest_render_rect() { return dest_rect; }
	vec3D get_position() { return position; }

	void set_position(vec3D);
};
#endif
