#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "camera.h"
#include "type_structs.h"

#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>


class GameObject
{
private:
    std::string name;
    vec3D position;
    SDL_Rect src_rect;
    std::map<int, std::pair<std::string, SDL_Texture*>> textures;
    std::map<std::string, tag*> tags;
    void *data_store;
    long data_store_size;
protected:
    unsigned int keycode_binding;
    unsigned int keycode_binding_mod;
    int clicked;
    void (*whileclickevent)(int, GameObject*);
    void (*onceclickevent)(int, GameObject*);
    bool mouse_on;
    void (*mouseonobject)(GameObject*);
    void (*mouseoffobject)(GameObject*);
public:
    GameObject(std::string);
    GameObject(std::string, unsigned int, unsigned int = 0);
    ~GameObject();

    virtual void start() {}
    virtual void update();

    void add_texturefile(std::string, int);
    void add_texture(SDL_Texture *texture, int texture_id) { textures[texture_id].second = texture; }
    void add_tag(std::string key, const char*);
    void add_tag(std::string key, long);
    void set_render_rect_defaults();
    void set_render_props(int tex_x1 = 0, int tex_y1 = 0, int h = 0, int w = 0, int scale_x = 1, int scale_y = 1);
    void set_keybinding(char key) { keycode_binding = key; }
    void set_whileclickevent(void (*func)(int, GameObject*)) { whileclickevent = func; }
    void set_onclickevent(void (*func)(int, GameObject*)) { onceclickevent = func; }

    bool check_mouse_on(int, int);
    void mouse_on_object() { mouseonobject(this); };
    void click_object(int, bool);
    void set_mouseonobject(void (*func)(GameObject*)) { mouseonobject = func; }
    void set_mouseoffobject(void (*func)(GameObject*)) { mouseoffobject = func; }

    std::string get_name() { return name; }
    std::map<int, std::pair<std::string, SDL_Texture*>> get_textures() { return textures; }
    SDL_Rect get_src_render_rect() { return src_rect; }
    SDL_Rect get_dest_render_rect() { return cam.get_destination_rect(position, src_rect.h, src_rect.w); }
    vec3D get_position() { return position; }
    tag* get_tag(std::string key);
    unsigned int get_keycode_binding() { return keycode_binding; }
    unsigned int get_keycode_binding_mod() { return keycode_binding_mod; }

    void set_position(vec3D);
};
#endif
