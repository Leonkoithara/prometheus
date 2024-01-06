#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "game_manager.h"
#include "game_object.h"
#include "scene.h"


GameManager gm;

GameManager::GameManager()
{
    running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL Initialization failed" << std::endl;
        exit(1);
    }

    if(TTF_Init() < 0)
    {
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
        exit(1);
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    float width = DM.w;
    float height = DM.h;
    screen_size = { width, height, 0};
}

void GameManager::event_handler()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    for (auto it : scenes)
    {
        switch (event.type)
        {
            Scene *temp;
            case SDL_MOUSEBUTTONDOWN:
                if(it.second->get_window_id() == event.window.windowID)
                    temp = it.second;
                temp->click_objects(event.button.x, event.button.y, event.button.button, true);
                break;
            case SDL_MOUSEBUTTONUP:
                if(it.second->get_window_id() == event.window.windowID)
                    temp = it.second;
                temp->click_objects(event.button.x, event.button.y, event.button.button, false);
                break;
            case SDL_WINDOWEVENT:
                // If last scene clean when SDL_QUIT event is triggered
                if (scenes.size() == 1)
                    break;
                if(it.second->get_window_id() == event.window.windowID)
                    temp = it.second;
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        delete_scene(temp->get_scene_name());
                }
                break;
            case SDL_QUIT:
                quit();
                break;
        }
    }
}

void GameManager::update()
{
    while (!delete_scene_queue.empty())
    {
        Scene *scn = delete_scene_queue.back();
        scenes.erase(scn->get_scene_name());
        delete scn;
        delete_scene_queue.pop_back();
    }
    for (auto &it : scenes)
        it.second->update();
}

void GameManager::render()
{
    for (auto it : scenes)
        it.second->render();
}

void GameManager::quit()
{
    running = false;
}

GameObject* GameManager::instantiate_game_object(std::string scene_name, std::string obj_name, float xpos, float ypos)
{
    GameObject *obj;
    auto it = scenes.find(scene_name);
    if (it != scenes.end())
    {
        obj = it->second->instantiate_game_object(obj_name, xpos, ypos);
        std::cout << "Object instantiated successfully" << std::endl;
    }
    else
        std::cout << "Scene not found" << std::endl;

    return obj;
}

Scene* GameManager::get_scene_by_name(std::string name)
{
    auto it = scenes.find(name);
    if (it == scenes.end())
        return NULL;

    return it->second;
}

void GameManager::add_game_object(GameObject *obj, std::string scene_name)
{
    Scene *scn = get_scene_by_name(scene_name);
    scn->add_game_object(obj);
}

void GameManager::add_scene(Scene *scn)
{
    scenes[scn->get_scene_name()] = scn;
}

void GameManager::add_empty_scene(std::string scene_name, int xpos, int ypos, int width, int height)
{
    Scene *scn = new Scene(scene_name);

    scn->create_window(scene_name, xpos, ypos, width, height, false);
    scenes[scene_name] = scn;
}

void GameManager::delete_scene(std::string name)
{
    auto it = scenes.find(name);
    if (it == scenes.end())
        std::cout << "Scene not found. Skipping..." << std::endl;

    delete_scene_queue.push_back(it->second);
}

GameManager::~GameManager()
{
    for (auto &it : scenes)
        delete it.second;
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
