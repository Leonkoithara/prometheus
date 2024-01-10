#include "world_gen.h"

void create_submap(int x, GameObject *icon)
{
    std::cout << "Clicked: " << icon->get_tag("terrain")->strval << ", at: " << icon->get_tag("xpos")->longval << "," << icon->get_tag("ypos")->longval << std::endl;
}
