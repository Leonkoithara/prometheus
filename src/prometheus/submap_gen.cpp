#include <type_structs.h>
#include <game_object.h>
#include <tile.h>
#include <world_gen.h>


void highlight_tile(GameObject *tile)
{
    Tile *t = dynamic_cast<Tile*>(tile);
    if (t != NULL)
        t->set_highlighted(true);
}

void unhighlight_tile(GameObject *tile)
{
    Tile *t = dynamic_cast<Tile*>(tile);
    if (t != NULL)
        t->set_highlighted(false);
}


void WorldGen::set_submap_terrain_elevation(long x, long y)
{
    // set elevation to 0 and terrain to plains
    submap_generated_flag[x][y] = true;
    for( int i=0; i<world_size; i++)
    {
        for( int j=0; j<world_size; j++)
        {
            submap_data_matrix[x][y].elevation_matrix[i][j] = 0;
            submap_data_matrix[x][y].terrain_matrix[i][j] = plains;
        }
    }
}

void WorldGen::populate_submap_terrain(long x, long y)
{
    for (int i=0; i<25; i++)
    {
        for (int j=0; j<25; j++)
        {
            char submap_obj_name[15];
            snprintf(submap_obj_name, 15, "submap_%ld_%ld_%d_%d", x, y, i, j);
            Tile *submap_obj = new Tile(std::string(submap_obj_name));
            submap_obj->add_tag("xpos", i);
            submap_obj->add_tag("ypos", j);
            submap_obj->add_texturefile("res/textures/tree_map.png", 0);
            submap_obj->set_position(convert_xy_to_screenxy(i*30, j*30));
            submap_obj->set_mouseonobject(highlight_tile);
            submap_obj->set_mouseoffobject(unhighlight_tile);
            playing_area->add_game_object(i*25+j, submap_obj);
        }
    }
}
