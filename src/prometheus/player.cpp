#include <character.h>
#include <game_manager.h>
#include <scene.h>

#include <GL/glew.h>


void Player::spawn_player()
{
    Scene *player_scene = new Scene("player_scene");
    player_scene->create_window("Prometheus", 0, 0, 1000, 1000, false);
    gm.add_scene(player_scene);
    gm.delete_scene("world_map");

    {
        float position[] =
        {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.0f,  0.5f
        };
        player_scene->set_vao(position, 6 * sizeof(float));
        player_scene->read_shader_code("res/shaders/triangle.vert", VERTEX_SHADER);
        player_scene->read_shader_code("res/shaders/triangle.frag", FRAGMENT_SHADER);
        player_scene->create_shader_program();
    }

    GameObject *title = new GameObject("title");
    title->set_position({100, 0});
    title->add_texturefile("res/textures/prometheus.png", 0);
    player_scene->add_game_object(title);
}
