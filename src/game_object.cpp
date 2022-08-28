#include "game_object.h"
#include <iostream>

GameObject::GameObject(SDL_Renderer *renderer, const char *filename)
{
	SDL_Surface *surface = IMG_Load(filename);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	std::cout << "Game object created" << std::endl;
}

GameObject::~GameObject() {}

void GameObject::update()
{
	std::cout << position.x << std::endl;
	position.x += 0.1;
}
