#ifndef SCENE
#define SCENE

#include <map>
#include <string>
#include <GL/glew.h>

#include <button.h>
#include <game_object.h>
#include <type_structs.h>


enum SHADER_TYPE { VERTEX_SHADER = 0, FRAGMENT_SHADER };

class Scene
{
private:
    std::string name;
    bool update_scene;
    bool active_scene;
    // int is the render order
    std::map<int, std::pair<std::string, GameObject*>> game_objects;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_GLContext opengl_contxt;
    GLuint vao;
    unsigned int shader_program;
    int gl_render_ready;
    std::string vertex_shader;
    std::string fragment_shader;
    Button *fps_obj;
public:
    Scene(std::string);
    ~Scene();

    void create_window(std::string, int, int, int, int, vec3D, bool);
    void update();
    void render();

    void set_active_scene(bool active) { active_scene = active; }
    void set_update_scene(bool update) { update_scene = update; }
    void set_game_obj_texture(GameObject*);
    void set_vao(const void*, int);

    GameObject* get_scene_game_obj(std::string);
    std::string get_scene_name(){ return name; }
    int get_window_id() { return SDL_GetWindowID(window); }
    Button* get_fps_obj() { return fps_obj; }

    // int is the render order
    void add_game_object(int, GameObject*);
    void click_objects(int, int, int, bool);
    void mouse_update_event(int, int);
    void process_keystroke(unsigned int, unsigned int, bool);
    void create_shader_program();
    void read_shader_code(std::string, enum SHADER_TYPE);
};

#endif
