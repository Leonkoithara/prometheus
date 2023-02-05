#include "game_manager.h"
#include "menu.h"


int main(int argc, char *argv[])
{
	create_main_menu();

	while (gm.get_running_stat())
	{
	    gm.event_handler();
		gm.update();
		gm.render();
	}

	return 0;
}
