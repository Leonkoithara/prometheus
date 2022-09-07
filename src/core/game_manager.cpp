#include "game_manager.h"
#include "game_object.h"
#include "scene.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void GameManager::init()
{
	running = true;
	Scene *scn = new Scene("default");
	
	scn->init("Default Window", 100, 100, 640, 480, false);
	scenes["default"] = scn;
}

void GameManager::event_handler()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
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
		it.second->render(camera);
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
