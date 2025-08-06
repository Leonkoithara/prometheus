#ifndef SCENE
#define SCENE

#include <unordered_map>
#include <string>
#include <GL/glew.h>

#include "game_object.h"


class Scene
{
private:
    std::string name;
    bool update_scene;
    bool active_scene;
    std::unordered_map<std::string, GameObject*> game_objects;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_GLContext opengl_contxt;
    GLuint vao;
    unsigned int shader_program;
    int gl_render_ready;
public:
    Scene(std::string);
    ~Scene();

    void create_window(std::string, int, int, int, int, bool);
    GameObject* instantiate_game_object(std::string, float, float);
    void update();
    void render();

    void set_active_scene(bool active) { active_scene = active; }
    void set_update_scene(bool update) { update_scene = update; }
    void set_game_obj_texture(GameObject*);
    void set_vao(const void*, int);

    GameObject* get_scene_game_obj(std::string);
    std::string get_scene_name(){ return name; }
    int get_window_id() { return SDL_GetWindowID(window); }

    void add_game_object(GameObject*);
    void click_objects(int, int, int, bool);
    void process_keystroke(unsigned int, unsigned int, bool);
    void create_shader_program(std::string, std::string);
};

#endif
