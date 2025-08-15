#include <cstdio>
#include <iostream>

#include <game_object.h>
#include <button.h>
#include <character.h>
#include <game_manager.h>
#include <scene.h>

#include <GL/glew.h>


void Player::spawn_player()
{
    Scene *player_scene = new Scene("player_scene");
    player_scene->create_window("Prometheus", 0, 0, 1778, 1000, {135, 206, 235}, false);
    gm.add_scene(player_scene);

    GameObject *ground = new GameObject("ground");
    ground->set_position({0, 500, 0});
    ground->add_texturefile("res/textures/ground.png", 0);
    ground->set_dest_render_props(0, 500, 500, 1778);
    player_scene->add_game_object(0, ground);

    int grass_num = rand()%30;
    int cloud_num = rand()%15;

    for (int i=0; i<grass_num; i++)
    {
        char grass_name[15];
        sprintf(grass_name, "grass_%d", i);
        GameObject *grass = new GameObject(grass_name);
        float grass_x = rand()%1778;
        float grass_y = 500+rand()%500;
        grass->set_position({grass_x, grass_y, 0});
        grass->add_texturefile("res/textures/grass1.png", i);
        player_scene->add_game_object(i+1, grass);
    }

    for (int i=0; i<cloud_num; i++)
    {
        char cloud_name[15];
        sprintf(cloud_name, "cloud_%d", i);
        GameObject *cloud = new GameObject(cloud_name);
        float cloud_x = rand()%1778;
        float cloud_y = rand()%400;
        cloud->set_position({cloud_x, cloud_y, 0});
        cloud->add_texturefile("res/textures/cloud1.png", grass_num+i);
        player_scene->add_game_object(grass_num+i+1, cloud);
    }
}
