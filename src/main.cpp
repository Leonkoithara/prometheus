#include "game_manager.h"

int main(int argc, char *argv[])
{
	GameManager gm;
	gm.init();
	gm.instantiate_game_object("default", "pacman", 30, 30);
	gm.set_texturefile_game_obj("default", "pacman", "res/textures/sprite1.png");

	while (gm.get_running_stat()) {
	    gm.event_handler();
		gm.update();
		gm.render();
	}

	gm.clean();
	
	return 0;
}
