#include "game_manager.h"
#include "button.h"
#include "game_object.h"
#include "menu.h"


int main(int argc, char *argv[])
{
	gm.init();
	create_main_menu();

	while (gm.get_running_stat()) {
	    gm.event_handler();
		gm.update();
		gm.render();
	}

	gm.clean();
	
	return 0;
}
