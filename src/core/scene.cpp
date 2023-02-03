#include <iostream>

#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "scene.h"
#include "button.h"
#include "game_object.h"

Scene::Scene(std::string scene_name)
{
	name = scene_name;
	update_scene = true;
	active_scene = true;
}

void Scene::create_window(std::string title, int xpos, int ypos, int width, int height, bool full_screen)
{
	int flags = 0;
	if (full_screen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

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

void Scene::click_objects(int xpos, int ypos, int button_id, bool unclick)
{
	int winw, winh;
	SDL_GetWindowSize(window, &winw, &winh);
	for (auto &it : game_objects ) {
		Button *obj = dynamic_cast<Button*>(it.second);
		if (obj == NULL)
			continue;
		if (obj->check_clicked(xpos-(winw/2), ypos-(winh/2)))
		    obj->click_object(button_id, unclick);
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
	if (update_scene) {
	    for (auto &it : game_objects)
		    it.second->update();
	}
}

void Scene::set_game_obj_texture(GameObject *obj)
{
	for (auto texture : obj->get_textures()) {

		if (texture.second.second == NULL) {
			SDL_Texture *tex;
			if (texture.second.first == "button_text") {
				Button *butt = dynamic_cast<Button*>(obj);
				TTF_Font *sans = TTF_OpenFont("res/fonts/FreeSans.ttf", 24);
				std::cout << TTF_GetError() << std::endl;
				SDL_Color white = {225, 225, 225};
				SDL_Surface *msg_surface = TTF_RenderText_Solid(sans, butt->get_text().c_str(), white);
				tex = SDL_CreateTextureFromSurface(renderer, msg_surface);
			}
			else
			{
				SDL_Surface *surface = IMG_Load(texture.second.first.c_str());
				tex = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
			}
			obj->add_texture(tex, texture.first);
		}

	}
	obj->set_render_rect_defaults();
}

void Scene::render()
{
	if (active_scene)
	{
		SDL_RenderClear(renderer);
		
	    for (auto it : game_objects)
		{
			for (auto itr : it.second->get_textures()) {
			    if (itr.second.second == NULL) {
				    set_game_obj_texture(it.second);
					break;
				}
			}
		    SDL_Rect src = it.second->get_src_render_rect();
			SDL_Rect dest = camera.get_destination_rect(it.second->get_position(), src.h, src.w);

			auto textures = it.second->get_textures();
			for (auto itr : textures) {
			    SDL_RenderCopy(renderer, itr.second.second, &src, &dest);
			}
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

