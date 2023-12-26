#include <iostream>

#include <SDL_render.h>

#include "game_object.h"


GameObject::GameObject(std::string nm)
{
    name = nm;
    std::cout << "Game object: " << name << " created" << std::endl;
    position = {0, 0, 0};
    src_rect = {0, 0, 0, 0};
    dest_rect = {0, 0, 0, 0};
    start();
}

GameObject::~GameObject() {}

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
    dest_rect.h = src_rect.h;
    dest_rect.w = src_rect.w;
}

void GameObject::set_render_props(int tex_x1, int tex_y1, int h, int w, int scale_x, int scale_y)
{
    src_rect.x = tex_x1;
    src_rect.y = tex_y1;
    if(h != 0)
        src_rect.h = h;
    if(w != 0)
        src_rect.w = w;
    
    dest_rect.x = position.x;
    dest_rect.y = position.y;
    dest_rect.h = src_rect.h * scale_y;
    dest_rect.w = src_rect.w * scale_y;
}

void GameObject::set_position(vec3D pos)
{
    position = pos;
    dest_rect.x = pos.x;
    dest_rect.y = pos.y;
}

void GameObject::add_texturefile(std::string texturefile, int render_order)
{
    textures[render_order] = std::pair<std::string, SDL_Texture*>(texturefile, NULL);
}
