#ifndef SCENE
#define SCENE

#include <string>
#include <unordered_map>

#include "game_object.h"
class Scene
{
private:
	const char *name;
	bool update_scene;
	bool active_scene;
	std::unordered_map<std::string, GameObject*> game_objects;
	SDL_Renderer *renderer;
	SDL_Window *window;
public:
	Scene(const char*);
	~Scene();

	void init(const char*, int, int, int, int, bool);
	void instantiate_game_object(std::string, float, float);
	void update();
	void render();
	void clean();

	void set_active_scene(bool active) { active_scene = active; }
	void set_update_scene(bool update) { update_scene = update; }
	void set_game_obj_texture(std::string, std::string);

	GameObject* get_scene_game_obj(std::string);
	const char* get_scene_name(){ return name; }
};

#endif
