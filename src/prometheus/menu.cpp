#include "button.h"
#include "game_object.h"
#include "game_manager.h"
#include "scene.h"
#include "world_gen.h"

void quit_game(int x, GameObject *) { gm.quit(); }

void create_main_menu()
{
    Scene *main_menu = new Scene("main_menu");
    main_menu->create_window("Main Menu", 100, 100, 640, 480, false);
    
    GameObject *title = new GameObject("title");
    title->set_position({100, 0});
    title->add_texturefile("res/textures/prometheus.png", 0);

    Button *create_world_button = new Button("create_world_button");
    create_world_button->set_position({190, 150});
    create_world_button->add_texturefile("res/textures/button.png", 0);
    create_world_button->set_text("Create new World");
    create_world_button->set_onclickevent(&start_create_world);

    Button *quit_game_button = new Button("quit_game_button", 'q');
    quit_game_button->set_position({220, 190});
    quit_game_button->add_texturefile("res/textures/button.png", 0);
    quit_game_button->set_text("Quit game");
    quit_game_button->set_onclickevent(&quit_game);

    main_menu->add_game_object(title);
    main_menu->add_game_object(create_world_button);
    main_menu->add_game_object(quit_game_button);

    gm.add_scene(main_menu);
}
