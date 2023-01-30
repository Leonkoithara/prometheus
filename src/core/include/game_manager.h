#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>

#include "game_object.h"
#include "scene.h"
#include "camera.h"

class GameManager
{
private:
	bool running;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::unordered_map<std::string, Scene*> scenes;
public:
	GameManager() {}
	~GameManager() {}

	void init();
	void update();
	void event_handler();
	void render();
	void clean();

	GameObject* instantiate_game_object(std::string, std::string, float, float);

	bool get_running_stat() { return running; }
	Scene* get_scene_by_name(std::string);

	void add_empty_scene(std::string, int, int, int, int);
	void add_scene(std::string, Scene*) {}
	void add_game_object(std::string, GameObject*, std::string);
};

#endif
