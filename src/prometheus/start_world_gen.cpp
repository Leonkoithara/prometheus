#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <button.h>
#include <camera.h>
#include <scene.h>
#include <game_manager.h>
#include <game_object.h>
#include <type_structs.h>
#include <world_gen.h>


WorldGen *world;

void camera_translate(int x, GameObject *obj)
{
    enum direction { up = 0, down, right, left };
    int dir = obj->get_tag("direction")->longval;

    switch (dir)
	{
        case up:
            cam.camera_translate({0, -10});
            break;
        case down:
            cam.camera_translate({0, 10});
            break;
        case right:
            cam.camera_translate({10, 0});
            break;
        case left:
            cam.camera_translate({-10, 0});
            break;
    }
}

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

    Button *scroll_up = new Button("worldmap_w", 'w');
    scroll_up->add_tag("direction", (long)0);
    Button *scroll_down = new Button("worldmap_s", 's');
    scroll_down->add_tag("direction", 1);
    Button *scroll_right = new Button("worldmap_d", 'd');
    scroll_right->add_tag("direction", 2);
    Button *scroll_left = new Button("worldmap_a", 'a');
    scroll_left->add_tag("direction", 3);
    scroll_up->set_onclickevent(&camera_translate);
    scroll_down->set_onclickevent(&camera_translate);
    scroll_right->set_onclickevent(&camera_translate);
    scroll_left->set_onclickevent(&camera_translate);

    new_world_gen->create_window("Prometheus", 0, 0, winx, winy, false);
    new_world_gen->add_game_object(scroll_up);
    new_world_gen->add_game_object(scroll_down);
    new_world_gen->add_game_object(scroll_right);
    new_world_gen->add_game_object(scroll_left);

    create_new_world(new_world_gen, world_name, world_size);

    gm.add_scene(new_world_gen);
    gm.delete_scene("main_menu");
}
