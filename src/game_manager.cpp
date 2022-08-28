#include "game_manager.h"
#include "SDL_render.h"
#include "game_object.h"

void GameManager::init(const char *title, int xpos, int ypos, int width,
                         int height, bool full_screen)
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
	if (!window) {
		std::cout << "Window creation failed" << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "Renderer could not be created" << std::endl;
		exit(1);
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	running = true;
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
	for (auto &i : game_objects) {
	    i.update();
	}
}

void GameManager::render()
{
	SDL_RenderClear(renderer);

	for (auto &i : game_objects) {
		SDL_Rect dest;
		dest.x = i.get_position().x;
		dest.y = i.get_position().y;
		dest.h = i.get_size().x;
		dest.w = i.get_size().y;
		SDL_RenderCopy(renderer, i.get_texture(), NULL, &dest);
	}

	SDL_RenderPresent(renderer);
}

void GameManager::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void GameManager::instantiate_game_object(const char *texturefile)
{
	game_objects.push_back(GameObject(renderer, texturefile));
	std::cout << "Object instantiated successfully" << std::endl;
}
