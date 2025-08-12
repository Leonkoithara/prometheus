#ifndef GAME_MANAGER
#define GAME_MANAGER

#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include <game_object.h>
#include <scene.h>
#include <type_structs.h>

class GameManager
{
private:
    bool running;
    vec3D screen_size;
    std::unordered_map<std::string, Scene*> scenes;
    std::vector<Scene*> delete_scene_queue;
    bool opengl_init_complete;
    time_t start_time;
public:
    GameManager();
    ~GameManager();

    void update();
    void event_handler();
    void render();
    void quit();

    bool get_running_stat() { return running; }
    vec3D get_screen_size() { return screen_size; }
    Scene* get_scene_by_name(std::string);

    void add_scene(Scene*);

    void delete_scene(std::string);

    void init_opengl()
    {
        if(opengl_init_complete)
            return;
        else
        {
            if (glewInit() != GLEW_OK)
                exit(1);
            std::cout << glGetString(GL_VERSION) << std::endl;
            opengl_init_complete = true;
        }
    }
};

extern GameManager gm;
#endif
