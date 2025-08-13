#include <game_object.h>
#include <button.h>
#include <character.h>
#include <game_manager.h>
#include <scene.h>

#include <GL/glew.h>


void Player::spawn_player()
{
    Scene *player_scene = new Scene("player_scene");
    player_scene->create_window("Prometheus", 0, 0, 1000, 1000, {178, 255, 255}, false);
    gm.add_scene(player_scene);
    gm.delete_scene("world_map");

    GameObject *ground = new GameObject("ground");
    ground->set_position({0, 500, 0});
    ground->add_texturefile("res/textures/ground.png", 0);
    ground->set_dest_render_props(0, 500, 500, 1000);

    player_scene->add_game_object(ground);
}
