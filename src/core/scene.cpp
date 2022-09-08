#include <iostream>

#include <SDL_rect.h>
#include <SDL_render.h>

#include "scene.h"
#include "game_object.h"

Scene::Scene(const char *scene_name)
{
	name = scene_name;
	update_scene = true;
	active_scene = true;
}

void Scene::init(const char *title, int xpos, int ypos, int width, int height, bool full_screen)
{
	int flags = 0;
	if (full_screen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Initialization failed" << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window)
	{
		std::cout << "Window creation failed" << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cout << "Renderer could not be created" << std::endl;
		exit(1);
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	active_scene = true;
}

void Scene::instantiate_game_object(std::string game_obj_name, float pos_x, float pos_y)
{
	auto it = game_objects.find(game_obj_name);
	if (it == game_objects.end())
	{
		GameObject *obj = new GameObject(game_obj_name);
		obj->set_position({pos_x, pos_y, 0});
		game_objects[game_obj_name] = obj;
	}
}

void Scene::update()
{
	if (update_scene) {
	    for (auto &it : game_objects) {
		    it.second->update();
		}
	}
}

void Scene::render()
{
	if (active_scene)
	{
		SDL_RenderClear(renderer);
		
	    for (auto it : game_objects)
		{
			if (it.second->get_texture() == NULL)
				continue;

		    SDL_Rect src = it.second->get_src_render_rect();
			SDL_Rect dest = camera.get_destination_rect(it.second->get_position(), src.h, src.w);
			SDL_RenderCopy(renderer, it.second->get_texture(), &src, &dest);
		}
		
		SDL_RenderPresent(renderer);
	}
}

void Scene::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

Scene::~Scene() {}

void Scene::set_game_obj_texture(std::string game_object_name, std::string filename)
{
	auto it = game_objects.find(game_object_name);
	if (it != game_objects.end())
	{
		it->second->set_texturefile(renderer, filename);
	}
	else
		std::cout << "Game Object not found" << std::endl;
}
