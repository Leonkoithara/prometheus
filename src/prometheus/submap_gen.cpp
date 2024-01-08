#include "world_gen.h"

void create_submap(int x, GameObject *icon)
{
    std::cout << "Clicked: " << icon->get_tag("terrain") << ", at: " << icon->get_tag("xpos") << "," << icon->get_tag("ypos") << std::endl;
}
