#include <character.h>
#include <game_manager.h>


void Player::spawn_player()
{
    Scene *player_scene = new Scene("player_scene");
    player_scene->create_window("Prometheus", 0, 0, 1000, 1000, false);
    gm.add_scene(player_scene);
    gm.delete_scene("world_map");
}
