#include <iostream>

#include <SDL_render.h>

#include "camera.h"
#include "game_object.h"


GameObject::GameObject(std::string nm)
{
    name = nm;
    std::cout << "Game object: " << name << " created" << std::endl;
    position = {0, 0, 0};
    src_rect = {0, 0, 0, 0};
    start();
}

GameObject::~GameObject()
{
    for (auto &t : tags)
        delete t.second;
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
