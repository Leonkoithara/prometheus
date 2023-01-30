#include "game_manager.h"
#include "button.h"
#include "game_object.h"


int main(int argc, char *argv[])
{
	GameManager gm;
	gm.init();
	gm.add_empty_scene("Test", 200, 100, 640, 480);
	GameObject *pacman = gm.instantiate_game_object("Test", "pacman", 0, 0);
	pacman->add_texturefile("res/textures/sprite1.png", 0);
	Button *butt = new Button("button");
	butt->set_position({100, 100});
	butt->add_texturefile("res/textures/button.png", 0);
	butt->set_text("Hello World!");
	gm.add_game_object("button", butt, "Test");

	while (gm.get_running_stat()) {
	    gm.event_handler();
		gm.update();
		gm.render();
	}

	gm.clean();
	
	return 0;
}
