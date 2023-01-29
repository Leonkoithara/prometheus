#include "game_manager.h"
#include "game_object.h"
#include "scene.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void GameManager::init()
{
	running = true;
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
			scn->clean();
		}
		break;
	}
	case SDL_QUIT:
	{
		running = false;
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

void GameManager::clean()
{
	for (auto &it : scenes)
		it.second->clean();	
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void GameManager::instantiate_game_object(std::string scene_name, std::string obj_name, float xpos, float ypos)
{
	auto it = scenes.find(scene_name);
	if (it != scenes.end())
	{
		it->second->instantiate_game_object(obj_name, xpos, ypos);
		std::cout << "Object instantiated successfully" << std::endl;
	}
	else
		std::cout << "Scene not found" << std::endl;
}

void GameManager::set_texturefile_game_obj(std::string scene_name, std::string obj_name, std::string filename)
{
	auto it = scenes.find(scene_name);
	if (it != scenes.end())
	{
		it->second->set_game_obj_texture(obj_name, filename);
		std::cout << "Texture set successfully" << std::endl;
	}
}

Scene* GameManager::get_scene_by_name(std::string name)
{
	auto it = scenes.find(name);
	if (it == scenes.end())
	    return NULL;

	return it->second;
}

void GameManager::add_game_object(std::string obj_name, GameObject *obj, std::string scene_name)
{
	Scene *scn = get_scene_by_name(scene_name);
	scn->add_game_object(obj_name, obj);
}

void GameManager::add_empty_scene(std::string scene_name, int xpos, int ypos, int width, int height)
{
	Scene *scn = new Scene(scene_name);

	scn->init(scene_name, xpos, ypos, width, height, false);
	scenes[scene_name] = scn;
}
