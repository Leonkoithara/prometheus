#ifndef WORLDGEN
#define WORLDGEN
#include <iostream>

#include "game_object.h"
#include "scene.h"

#define TERRAIN_TYPES 6

enum terrain { plains = 0, mountains, forests, water, human_civ, civ_ruins };

struct worldgen_data
{
    char *name;
    int world_size;
    long seed;
    terrain **terrain_matrix;

    worldgen_data()
    {
        name = nullptr;
        world_size = 0;
        seed = 0;
        terrain_matrix = nullptr;
    }
};


void start_create_world(int, GameObject *);
void create_new_world(Scene *, std::string);
void create_submap(int, GameObject *);

extern worldgen_data world;
#endif
