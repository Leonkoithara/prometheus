#ifndef WORLDGEN
#define WORLDGEN
#include <type_structs.h>
#include <iostream>

#include <game_object.h>
#include <scene.h>
#include <character.h>

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

class WorldGen
{
private:
    std::string name;
    int world_size;
    long seed;
    terrain **terrain_matrix;
    submap_data **submap_data_matrix;
    bool **submap_generated_flag;
    int ***probablity_matrix;
    Player *player;
    Scene *playing_area;

public:
    WorldGen(int, std::string);

    int get_world_size() { return world_size; }

    void set_terrain_matrix();
    void modify_probablities(int, int, int, terrain);
    void populate_overmap_symbols(Scene*);
    void create_playing_area();
    void set_submap_terrain_elevation(long, long);
    void populate_submap_terrain(long, long);

    vec3D convert_screenxy_to_xy(long x, long y)
    {
        long retx = ONE_BY_ROOT_TWO * (x + y - 889);
        long rety = ONE_BY_ROOT_TWO * (y - x + 889);
        return {retx, rety, 0};
    }
    vec3D convert_xy_to_screenxy(long x, long y)
    {
        long retx = ONE_BY_ROOT_TWO * (x - y) + 889;
        long rety = ONE_BY_ROOT_TWO * (x + y);
        return {retx, rety, 0};
    }

    void create_player();
    void spawn_player();
};


void start_create_world(int, GameObject *);
void create_first_submap(int, GameObject*);

extern WorldGen *world;
#endif
