#ifndef WORLDGEN
#define WORLDGEN
#include <iostream>

#include "game_object.h"
#include "scene.h"

#define TERRAIN_TYPES 6

enum terrain { plains = 0, mountains, forests, water, human_civ, civ_ruins };

struct submap_data
{
    terrain **terrain_matrix;
    int **elevation_matrix;

    submap_data() {}

    submap_data(int sub_world_size)
    {
        terrain_matrix = new terrain*[sub_world_size];
        for (int i=0; i<sub_world_size; i++)
            terrain_matrix[i] = new terrain[sub_world_size];
        elevation_matrix = new int*[sub_world_size];
        for (int i=0; i<sub_world_size; i++)
            elevation_matrix[i] = new int[sub_world_size];
    }
};

struct worldgen_data
{
    std::string name;
    int world_size;
    long seed;
    terrain **terrain_matrix;
    submap_data **submap_data_matrix;
    bool **submap_generated_flag;

    worldgen_data(int size, std::string nm)
    {
        name = nm;
        world_size = size;
        seed = 0;
        terrain_matrix = new terrain*[world_size];
        for( int i=0; i<world_size; i++)
            terrain_matrix[i] = new terrain[world_size];
        submap_generated_flag = new bool*[world_size];
        for( int i=0; i<world_size; i++)
        {
            submap_generated_flag[i] = new bool[world_size];
            for( int j=0; j<world_size; j++)
                submap_generated_flag[i][j] = false;
        }
        submap_data_matrix = new submap_data*[world_size];
        for( int i=0; i<world_size; i++)
        {
            submap_data_matrix[i] = new submap_data[world_size];
            for( int j=0; j<world_size; j++)
                submap_data_matrix[i][j] = submap_data(world_size);
        }
    }
};


void start_create_world(int, GameObject *);
void create_submap(int, GameObject *);

extern worldgen_data *world;
#endif
