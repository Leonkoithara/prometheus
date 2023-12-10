#include <iostream>

#include "scene.h"

#define TERRAIN_TYPES 6


enum terrain { plains = 0, mountains, forests, water, human_civ, civ_ruins };

void create_new_world(Scene*, std::string, long = 0);
