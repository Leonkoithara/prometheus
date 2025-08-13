#include "SDL_surface.h"
#include <iostream>

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <button.h>
#include <game_object.h>


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
    for (auto it : surfaces)
    {
        w2 = it.second.second->w;
        h2 = it.second.second->h;
        if(w2 > w1)
            w1 = w2;
        if(h2 > h1)
            h1 = h2;
    }
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.h = h1;
    src_rect.w = w1;

    dest_rect.x = position.x;
    dest_rect.y = position.y;
    dest_rect.h = src_rect.h;
    dest_rect.w = src_rect.w;
}

void GameObject::set_src_render_props(int tex_x1, int tex_y1, int h, int w)
{
    src_rect.x = tex_x1;
    src_rect.y = tex_y1;
    if(h != 0)
        src_rect.h = h;
    if(w != 0)
        src_rect.w = w;
}

void GameObject::set_dest_render_props(int dest_x1, int dest_y1, int h, int w)
{
    dest_rect.x = dest_x1;
    dest_rect.y = dest_y1;
    if(h != 0)
        dest_rect.h = h;
    else
        dest_rect.h = src_rect.h;
    if(w != 0)
        dest_rect.w = w;
    else
        dest_rect.w = src_rect.w;
}

void GameObject::set_position(vec3D pos)
{
    position = pos;
}

void GameObject::add_texturefile(std::string texturefile, int render_order)
{
    surfaces[render_order] = std::pair<std::string, SDL_Surface*>(texturefile, NULL);
    set_surface();
    set_render_rect_defaults();
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

void GameObject::set_surface()
{
    for (auto surface : get_surfaces())
    {
        if (surface.second.second == NULL)
        {
            SDL_Surface *surf;
            if (surface.second.first == "button_text")
            {
                Button *butt = dynamic_cast<Button*>(this);
                TTF_Font *sans = TTF_OpenFont("res/fonts/FreeSans.ttf", 24);
                const char *ttf_err = TTF_GetError();
                if (std::strlen(ttf_err) != 0)
                    std::cout << ttf_err << std::endl;
                vec3D tmp = butt->get_text_color();
                SDL_Color white = {static_cast<unsigned char>(tmp.x), static_cast<unsigned char>(tmp.y), static_cast<unsigned char>(tmp.z)};
                surf = TTF_RenderText_Solid(sans, butt->get_text().c_str(), white);
            }
            else
            {
                surf = IMG_Load(surface.second.first.c_str());
            }
            add_surface(surf, surface.first);
        }

    }
//    obj->set_render_rect_defaults();
}
