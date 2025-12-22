#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL_rect.h>
#include <SDL_render.h>

#include <button.h>
#include <game_manager.h>
#include <game_object.h>
#include <scene.h>

Scene::Scene(std::string scene_name)
{
    name = scene_name;
    update_scene = true;
    active_scene = true;
}

void Scene::create_window(std::string title, int xpos, int ypos, int width, int height, vec3D bg_color, bool full_screen)
{
    int flags = 0;
    std::cout << "Creating window: " << title << std::endl;
    if (full_screen)
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    else
        flags = SDL_WINDOW_OPENGL;

    window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
    if (!window)
    {
        std::cout << "Window creation failed" << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cout << "Renderer could not be created" << std::endl;
        exit(1);
    }
    SDL_SetRenderDrawColor(renderer, bg_color.x, bg_color.y, bg_color.z, 255);
    active_scene = true;

    Button *fps_counter = new Button("fps_counter", true);
    fps_counter->set_text(std::to_string(gm.get_previous_frame_duration()));
    fps_counter->set_position({0, 10, 0});
    game_objects[0] = std::pair<std::string, GameObject*>("fps_counter", fps_counter);
    fps_obj = fps_counter;
}

void Scene::click_objects(int xpos, int ypos, int button_id, bool click)
{
    for (auto &it : game_objects )
    {
        GameObject *obj = it.second.second;
        if (obj->check_mouse_on(xpos, ypos))
            obj->click_object(button_id, click);
    }
}

void Scene::mouse_update_event(int xpos, int ypos)
{
    for (auto &it : game_objects )
    {
        GameObject *obj = it.second.second;
        if (obj->check_mouse_on(xpos, ypos))
            obj->mouse_on_object();
    }
}

void Scene::process_keystroke(unsigned int key, unsigned int mod, bool down)
{
    for (auto &it : game_objects )
    {
        Button *obj = dynamic_cast<Button*>(it.second.second);
        if (obj == NULL)
            continue;
        if (obj->get_keycode_binding() == key)
		{
            if ((obj->get_keycode_binding_mod() == 0 && ((mod & ~(KMOD_NUM)) | KMOD_NONE) == 0) || (obj->get_keycode_binding_mod() & mod) != 0)
            {
                obj->click_object(1, true);
                obj->click_object(1, false);
            }
        }
    }
}

void Scene::add_game_object(int render_order, GameObject *obj)
{
    std::string game_obj_name = obj->get_name();
    // fps_counter obj must always be rendered last
    render_order++;
    auto it = game_objects.find(render_order);
    if (it == game_objects.end())
    {
        game_objects[render_order] = game_objects[render_order-1];
        game_objects[render_order-1] = std::pair<std::string, GameObject*>(game_obj_name, obj);
    }
    else
        std::cout << "An object exists on this render order, verify render order or duplicated add obj call" << std::endl;
}

void Scene::update()
{
    if (update_scene)
    {
        for (auto &it : game_objects)
            it.second.second->update();
    }
}

void Scene::render()
{
    if (active_scene)
    {
        SDL_RenderClear(renderer);
        
        for (auto it : game_objects)
        {
            SDL_Rect src = it.second.second->get_src_render_rect();
            SDL_Rect dest = it.second.second->get_dest_render_rect();

            auto surfaces = it.second.second->get_surfaces();
            for (auto itr : surfaces)
            {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, itr.second.second);
                SDL_RenderCopy(renderer, texture, &src, &dest);
                SDL_DestroyTexture(texture);
            }
        }

        SDL_RenderFlush(renderer);
        SDL_RenderPresent(renderer);
    }
}

Scene::~Scene()
{
    for (auto &it : game_objects)
        delete it.second.second;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    std::cout << "Destroy scene: " << name << std::endl;
}
