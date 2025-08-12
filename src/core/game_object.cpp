#include <iostream>

#include <SDL_render.h>

#include "camera.h"
#include "game_object.h"


void game_obj_empty_callback(GameObject *){};
void game_obj_click_empty_callback(int x, GameObject *){};
GameObject::GameObject(std::string nm)
{
    name = nm;
    std::cout << "Game object: " << name << " created" << std::endl;
    position = {0, 0, 0};
    src_rect = {0, 0, 0, 0};
    data_store_size = 0;
    start();
    mouse_on = false;
    mouseonobject = &game_obj_empty_callback;
    mouseoffobject = &game_obj_empty_callback;
    clicked = -1;
    whileclickevent = &game_obj_click_empty_callback;
    onceclickevent = &game_obj_click_empty_callback;
}

GameObject::GameObject(std::string name, unsigned int key, unsigned int mod) : GameObject(name)
{
    keycode_binding = key;
    keycode_binding_mod = mod;
}

GameObject::~GameObject()
{
    for (auto &t : tags)
        delete t.second;
}

bool GameObject::check_mouse_on(int xpos, int ypos)
{
    SDL_Rect rect = this->get_dest_render_rect();
    if (
        xpos >= rect.x &&
        ypos >= rect.y &&
        xpos <= rect.x+rect.w &&
        ypos <= rect.y+rect.h
    )
    {
        mouse_on = true;
        return true;
    }
    if (mouse_on)
    {
        mouse_on = false;
        mouseoffobject(this);
    }
    mouse_on = false;
    return false;
}

void GameObject::update()
{
    if (clicked >= 0)
        whileclickevent(clicked, this);
}


void GameObject::click_object(int button_id, bool click)
{
    if (click)
    {
        clicked = button_id;
        onceclickevent(button_id, this);
    }
    else
        clicked = -1;
}

void GameObject::set_render_rect_defaults()
{
    int w1 = 0, w2 = 0, h1 = 0, h2 = 0;
    for (auto it : textures)
    {
        SDL_QueryTexture(it.second.second, NULL, NULL, &w2, &h2);
        if(w2 > w1)
            w1 = w2;
        if(h2 > h1)
            h1 = h2;
    }
    src_rect.h = h1;
    src_rect.w = w1;
}

void GameObject::set_render_props(int tex_x1, int tex_y1, int h, int w, int scale_x, int scale_y)
{
    src_rect.x = tex_x1;
    src_rect.y = tex_y1;
    if(h != 0)
        src_rect.h = h;
    if(w != 0)
        src_rect.w = w;
}

void GameObject::set_position(vec3D pos)
{
    position = pos;
}

void GameObject::add_texturefile(std::string texturefile, int render_order)
{
    textures[render_order] = std::pair<std::string, SDL_Texture*>(texturefile, NULL);
}

void GameObject::add_tag(std::string key, const char *value)
{
    tags[key] = new tag(value);
}

void GameObject::add_tag(std::string key, long value)
{
    tags[key] = new tag(value);
}

tag* GameObject::get_tag(std::string key)
{
    auto search = tags.find(key);
    if (search != tags.end())
        return search->second;
    else
        return nullptr;
}
