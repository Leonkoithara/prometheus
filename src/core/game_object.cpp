#include "game_object.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <iostream>

GameObject::GameObject(std::string nm)
{
	name = nm;
	std::cout << "Game object created" << std::endl;
	texture = NULL;
	position = {0, 0, 0};
	src_rect = {0, 0, 0, 0};
	dest_rect = {0, 0, 0, 0};
	start();
}

GameObject::~GameObject() {}

void GameObject::set_texturefile(SDL_Renderer *renderer, std::string filename)
{
	SDL_Surface *surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &src_rect.w, &src_rect.h);
	dest_rect.h = src_rect.h;
	dest_rect.w = src_rect.w;
}

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

void GameObject::set_position(vec3D pos)
{
	position = pos;
	dest_rect.x = pos.x;
	dest_rect.y = pos.y;
}
