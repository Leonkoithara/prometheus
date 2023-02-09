#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "type_structs.h"

#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>


class GameObject
{
private:
	std::string name;
	vec3D position;
	SDL_Rect src_rect;
	SDL_Rect dest_rect;
	std::map<int, std::pair<std::string, SDL_Texture*>> textures;
public:
    GameObject(std::string);
    ~GameObject();

	virtual void start() {}
	virtual void update() {}

	virtual void create_textures(SDL_Renderer *);

	void add_texturefile(std::string, int);
	void add_texture(SDL_Texture *texture, int texture_id) { textures[texture_id].second = texture; }
	void set_render_rect_defaults();
	void set_render_props(int tex_x1 = 0, int tex_y1 = 0, int h = 0, int w = 0, int scale_x = 1, int scale_y = 1);

	std::string get_name() { return name; }
	std::map<int, std::pair<std::string, SDL_Texture*>>* get_textures() { return &textures; }
	SDL_Rect get_src_render_rect() { return src_rect; }
	SDL_Rect get_dest_render_rect() { return dest_rect; }
	vec3D get_position() { return position; }

	void set_position(vec3D);
};
#endif
