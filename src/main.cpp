#include "game_manager.h"
#include "button.h"


int main(int argc, char *argv[])
{
	GameManager gm;
	gm.init();
	gm.add_empty_scene("Test", 200, 100, 640, 480);
	gm.instantiate_game_object("Test", "pacman", 0, 0);
	gm.set_texturefile_game_obj("Test", "pacman", "res/textures/sprite1.png");
	Button *butt = new Button("button");
	butt->set_position({100, 100});
	gm.add_game_object("button", butt, "Test");
	gm.set_texturefile_game_obj("Test", "button", "res/textures/button.png");

	while (gm.get_running_stat()) {
	    gm.event_handler();
		gm.update();
		gm.render();
	}

	gm.clean();
	
	return 0;
}
