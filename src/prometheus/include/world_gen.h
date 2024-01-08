#ifndef WORLDGEN
#define WORLDGEN
#include <iostream>

#include "game_object.h"
#include "scene.h"

#define TERRAIN_TYPES 6

enum terrain { plains = 0, mountains, forests, water, human_civ, civ_ruins };
enum direction { up = 0, down, right, left };


direction convert2direction(std::string dir);
void start_create_world(int, GameObject *);
void create_new_world(Scene *, std::string, int = 50, long = 0);
void create_submap(int, GameObject *);
#endif
