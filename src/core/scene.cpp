#include <iostream>

#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "button.h"
#include "game_object.h"
#include "scene.h"

Scene::Scene(std::string scene_name)
{
	name = scene_name;
	update_scene = true;
	active_scene = true;
}

void Scene::create_window(std::string title, int xpos, int ypos, int width, int height, bool full_screen)
{
	int flags = 0;
	if (full_screen)
		flags = SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	active_scene = true;
}

GameObject* Scene::instantiate_game_object(std::string game_obj_name, float pos_x, float pos_y)
{
	auto it = game_objects.find(game_obj_name);
	if (it == game_objects.end())
	{
		GameObject *obj = new GameObject(game_obj_name);
		obj->set_position({pos_x, pos_y, 0});
		game_objects[game_obj_name] = obj;
		return obj;
	}
	return NULL;
}

void Scene::click_objects(int xpos, int ypos, int button_id, bool click)
{
	int winw, winh;
	SDL_GetWindowSize(window, &winw, &winh);
	for (auto &it : game_objects )
	{
		Button *obj = dynamic_cast<Button*>(it.second);
		if (obj == NULL)
			continue;
		if (obj->check_clicked(xpos-(winw/2), ypos-(winh/2)))
		    obj->click_object(button_id, click);
	}
}

void Scene::add_game_object(GameObject *obj)
{
	std::string game_obj_name = obj->get_name();
	auto it = game_objects.find(game_obj_name);
	if (it == game_objects.end())
		game_objects[game_obj_name] = obj;
}

void Scene::update()
{
	if (update_scene)
	{
	    for (auto &it : game_objects)
		    it.second->update();
	}
}

void Scene::render()
{
	if (active_scene)
	{
		SDL_RenderClear(renderer);
		
	    for (auto &it : game_objects)
		{
			it.second->create_textures(renderer);

		    SDL_Rect src = it.second->get_src_render_rect();
			SDL_Rect dest = camera.get_destination_rect(it.second->get_position(), src.h, src.w);

			auto textures = it.second->get_textures();
			for (auto itr : *textures)
			    SDL_RenderCopy(renderer, itr.second.second, &src, &dest);
		}
		
		SDL_RenderPresent(renderer);
	}
}

Scene::~Scene()
{
	for (auto &it : game_objects)
	    delete it.second;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);  
}
