#include "game_manager.h"
#include "game_object.h"
#include "scene.h"

#include <SDL_ttf.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

GameManager gm;

GameManager::GameManager()
{
	running = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Initialization failed" << std::endl;
		exit(1);
	}

	if(TTF_Init() < 0) {
		std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
		exit(1);
	}
}

void GameManager::event_handler()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
	{
		Scene *scn;
		for (auto it : scenes)
		{
		    if(it.second->get_window_id() == event.window.windowID)
			{
				scn = it.second;
				break;
			}
		}
		scn->click_objects(event.button.x, event.button.y, event.button.button, false);
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		Scene *scn;
		for (auto it : scenes)
		{
		    if(it.second->get_window_id() == event.window.windowID)
			{
				scn = it.second;
				break;
			}
		}
		scn->click_objects(event.button.x, event.button.y, event.button.button, true);
		break;
	}
	case SDL_WINDOWEVENT:
	{
		Scene *scn;
		for (auto it : scenes)
		{
		    if(it.second->get_window_id() == event.window.windowID)
			{
				scn = it.second;
				break;
			}
		}
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			scenes.erase(scn->get_scene_name());
			delete scn;
		}
		break;
	}
	case SDL_QUIT:
	{
		quit();
		break;
	}
	}
}

void GameManager::update()
{
	for (auto &it : scenes) {
	    it.second->update();
	}
}

void GameManager::render()
{
	for (auto it : scenes)
		it.second->render();
}

void GameManager::quit()
{
	running = false;
}

GameObject* GameManager::instantiate_game_object(std::string scene_name, std::string obj_name, float xpos, float ypos)
{
	GameObject *obj;
	auto it = scenes.find(scene_name);
	if (it != scenes.end())
	{
		obj = it->second->instantiate_game_object(obj_name, xpos, ypos);
		std::cout << "Object instantiated successfully" << std::endl;
	}
	else
		std::cout << "Scene not found" << std::endl;

	return obj;
}

Scene* GameManager::get_scene_by_name(std::string name)
{
	auto it = scenes.find(name);
	if (it == scenes.end())
	    return NULL;

	return it->second;
}

void GameManager::add_game_object(GameObject *obj, std::string scene_name)
{
	Scene *scn = get_scene_by_name(scene_name);
	scn->add_game_object(obj);
}

void GameManager::add_scene(Scene *scn)
{
	scenes[scn->get_scene_name()] = scn;
}

void GameManager::add_empty_scene(std::string scene_name, int xpos, int ypos, int width, int height)
{
	Scene *scn = new Scene(scene_name);

	scn->create_window(scene_name, xpos, ypos, width, height, false);
	scenes[scene_name] = scn;
}

GameManager::~GameManager()
{
	for (auto &it : scenes)
		delete it.second;	
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
