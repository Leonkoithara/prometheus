#include "game_manager.h"

const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 480;

int main(int argc, char *argv[])
{
	GameManager gm;
	gm.init("Rougelike", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	gm.instantiate_game_object("res/textures/sprite1.png");

	while (gm.get_running_stat()) {
	    gm.event_handler();
		gm.update();
		gm.render();
	}

	gm.clean();
	
	return 0;
}
