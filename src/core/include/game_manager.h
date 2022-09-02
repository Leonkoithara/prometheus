#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>

#include "game_object.h"

class GameManager
{
private:
	bool running;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::unordered_map<const char*, GameObject*> game_objects;
public:
	GameManager() {}
	~GameManager() {}

	void init(const char *, int, int, int, int, bool);
	void update();
	void event_handler();
	void render();
	void clean();

	void instantiate_game_object(const char*, const char*);

	bool get_running_stat() { return running; }
	GameObject* get_obj_by_name(const char *);
};

#endif
