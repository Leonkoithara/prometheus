#include "button.h"
#include "text.h"
#include "game_object.h"
#include "game_manager.h"
#include "scene.h"
#include "prometheus.h"

void quit_game(int x) { gm.quit(); }
void new_game(int x)
{
	Scene *game_start = new Prometheus();
	gm.add_scene(game_start);
}

void create_main_menu()
{
	Scene *main_menu = new Scene("main_menu");
	main_menu->create_window("Main Menu", 100, 100, 640, 480, false);
	
	GameObject *title = new GameObject("title");
	title->set_position({-180, -220});
	title->add_texturefile("res/textures/prometheus.png", 0);

	Button *new_game_button = new Button("new_game_button");
	new_game_button->set_position({-80, -30});
	new_game_button->add_texturefile("res/textures/button.png", 0);
	new_game_button->set_text("Start new game");
	new_game_button->set_onclickevent(&new_game);

	Button *options_button = new Button("options_button");
	options_button->set_position({-60, 30});
	options_button->add_texturefile("res/textures/button.png", 0);
	options_button->set_text("Options");

	Button *quit_game_button = new Button("quit_game_button");
	quit_game_button->set_position({-60, 90});
	quit_game_button->add_texturefile("res/textures/button.png", 0);
	quit_game_button->set_text("Quit game");
	quit_game_button->set_onclickevent(&quit_game);

	main_menu->add_game_object(title);
	main_menu->add_game_object(new_game_button);
	main_menu->add_game_object(options_button);
	main_menu->add_game_object(quit_game_button);

	gm.add_scene(main_menu);
}
