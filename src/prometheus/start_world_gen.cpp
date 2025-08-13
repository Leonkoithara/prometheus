#include <button.h>
#include <scene.h>
#include <game_manager.h>
#include <game_object.h>
#include <type_structs.h>
#include <world_gen.h>


WorldGen *world;

void create_new_world(Scene *prometheus, std::string world_name, int world_size)
{
    std::string world_filename = "res/save/" + world_name + "/world->dat";
    world = new WorldGen(world_size, world_name);

    world->set_terrain_matrix();
    world->populate_objects(prometheus);
}

void start_create_world(int x, GameObject *)
{
    Scene *new_world_gen = new Scene("world_map");
    int world_size = 50;
    std::string world_name = "begins";

    int winx = world_size*25, winy = world_size*25;
    vec3D screen_size = gm.get_screen_size();
    if (winx > screen_size.x)
        winx = screen_size.x;
    if (winy > screen_size.y)
        winy = screen_size.y;

    new_world_gen->create_window("Prometheus", 0, 0, winx, winy, {0, 0, 0}, false);

    create_new_world(new_world_gen, world_name, world_size);

    gm.add_scene(new_world_gen);
    gm.delete_scene("main_menu");
}
