#include "game_object.h"
#include "SDL_render.h"
#include <iostream>

GameObject::GameObject(const char *nm, SDL_Renderer *renderer, const char *filename)
{
	name = nm;
	SDL_Surface *surface = IMG_Load(filename);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	std::cout << "Game object created" << std::endl;

	SDL_QueryTexture(texture, NULL, NULL, &src_rect.w, &src_rect.h);
	dest_rect.h = src_rect.h;
	dest_rect.w = src_rect.w;
}

GameObject::~GameObject() {}

void GameObject::set_render_props(int tex_x1, int tex_y1, int h, int w, int scale_x, int scale_y)
{
	src_rect.x = tex_x1;
	src_rect.y = tex_y1;
	if(h != 0)
		src_rect.h = h;
	if(w != 0)
		src_rect.w = w;
	
	dest_rect.x = position.x;
	dest_rect.y = position.y;
	dest_rect.h = src_rect.h * scale_y;
	dest_rect.w = src_rect.w * scale_y;
}
