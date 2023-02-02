#include "button.h"
#include "game_object.h"
#include "game_manager.h"
#include "scene.h"

void quit_game(int x) { gm.quit(); }
void new_game(int x)
{
	Scene *game_start = new Scene("prometheus");
	game_start->init("Prometheus", 100, 100, 640, 480, false);
	gm.add_scene(game_start);
}

void create_main_menu()
{
	Scene *main_menu = new Scene("main_menu");
	main_menu->init("Main Menu", 100, 100, 640, 480, false);
	
	GameObject *title = new GameObject("title");
	title->set_position({-180, -220});
	title->add_texturefile("res/textures/prometheus.png", 0);

	Button *new_game_button = new Button("new_game_button");
	new_game_button->set_position({-80, -30});
	new_game_button->add_texturefile("res/textures/button.png", 0);
	new_game_button->set_text("Start new game");
	new_game_button->set_onclickevent(&new_game);

	Button *quit_game_button = new Button("quit_game_button");
	quit_game_button->set_position({-60, 30});
	quit_game_button->add_texturefile("res/textures/button.png", 0);
	quit_game_button->set_text("Quit game");
	quit_game_button->set_onclickevent(&quit_game);

	main_menu->add_game_object(title);
	main_menu->add_game_object(new_game_button);
	main_menu->add_game_object(quit_game_button);

	gm.add_scene(main_menu);
}
