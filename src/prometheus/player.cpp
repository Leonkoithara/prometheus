#include <character.h>
#include <game_manager.h>
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
        player_scene->set_vao(position);


        std::string vertexShader =
            "#version 330 core\n"
            "layout (location = 0) in vec4 position;\n"
            "void main()\n"
            "{\n"
            "gl_Position = position;\n"
            "}";
        std::string fragmentShader =
            "#version 330 core\n"
            "layout (location = 0) out vec4 color;\n"
            "void main()\n"
            "{\n"
            "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}";
        player_scene->create_shader_program(vertexShader, fragmentShader);
    }
}
