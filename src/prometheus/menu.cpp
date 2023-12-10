#include "button.h"
#include "game_object.h"
#include "game_manager.h"
#include "scene.h"
#include "world_gen.h"

void quit_game(int x) { gm.quit(); }
void create_world(int x)
{
    Scene *new_world_gen = new Scene("prometheus");
    new_world_gen->create_window("Prometheus", 0, 0, 1250, 950, false);

    create_new_world(new_world_gen, "prometheus_begins");

    gm.add_scene(new_world_gen);
    gm.delete_scene("main_menu");
}

void create_main_menu()
{
    Scene *main_menu = new Scene("main_menu");
    main_menu->create_window("Main Menu", 100, 100, 640, 480, false);
    
    GameObject *title = new GameObject("title");
    title->set_position({-180, -220});
    title->add_texturefile("res/textures/prometheus.png", 0);

    Button *create_world_button = new Button("create_world_button");
    create_world_button->set_position({-90, -30});
    create_world_button->add_texturefile("res/textures/button.png", 0);
    create_world_button->set_text("Create new World");
    create_world_button->set_onclickevent(&create_world);

    Button *quit_game_button = new Button("quit_game_button");
    quit_game_button->set_position({-60, 30});
    quit_game_button->add_texturefile("res/textures/button.png", 0);
    quit_game_button->set_text("Quit game");
    quit_game_button->set_onclickevent(&quit_game);

    main_menu->add_game_object(title);
    main_menu->add_game_object(create_world_button);
    main_menu->add_game_object(quit_game_button);

    gm.add_scene(main_menu);
}
