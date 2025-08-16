#include <string>
#include <algorithm>

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <GL/glew.h>

#include <chrono>
#include <game_manager.h>
#include <game_object.h>
#include <scene.h>


GameManager gm;

GameManager::GameManager()
{
    opengl_init_complete = false;
    previous_frame_duration = std::chrono::duration<float>(0);
    running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL Initialization failed" << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0)
    {
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
        exit(1);
    }

    sans = TTF_OpenFont("res/fonts/FreeSans.ttf", 24);
    const char *ttf_err = TTF_GetError();
    if (std::strlen(ttf_err) != 0)
        std::cout << ttf_err << std::endl;

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
        Scene *temp = NULL;
        if (it.second->get_window_id() == event.window.windowID)
            temp = it.second;
        if (temp != NULL)
        {
            if (std::find(delete_scene_queue.begin(), delete_scene_queue.end(), temp) != delete_scene_queue.end())
            {
                std::cout << "Scene scheduled for deletion. Skipping..." << std::endl;
                break;
            }
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    temp->click_objects(event.button.x, event.button.y, event.button.button, true);
                    break;
                case SDL_MOUSEBUTTONUP:
                    temp->click_objects(event.button.x, event.button.y, event.button.button, false);
                    break;
                case SDL_MOUSEMOTION:
                    temp->mouse_update_event(event.motion.x, event.motion.y);
                    break;
                case SDL_WINDOWEVENT:
                    // If last scene clean when SDL_QUIT event is triggered
                    if (scenes.size() == 1)
                        break;
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                            delete_scene(temp->get_scene_name());
                    }
                    break;
                case SDL_KEYDOWN:
                    temp->process_keystroke(event.key.keysym.sym, event.key.keysym.mod, true);
                    break;
                case SDL_QUIT:
                    quit();
                    break;
                case SDL_POLLSENTINEL:
                    break;
                default:
                    std::cout << "Unhandled event: " << event.type << std::endl;
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    previous_frame_duration = end - start;
}

void GameManager::update()
{
    start = std::chrono::high_resolution_clock::now();
    while (!delete_scene_queue.empty())
    {
        Scene *scn = delete_scene_queue.back();
        scenes.erase(scn->get_scene_name());
        delete scn;
        delete_scene_queue.pop_back();
    }
    for (auto &it : scenes)
    {
        it.second->get_fps_obj()->set_text(std::to_string(previous_frame_duration.count()));
        it.second->update();
    }
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

Scene* GameManager::get_scene_by_name(std::string name)
{
    auto it = scenes.find(name);
    if (it == scenes.end())
        return NULL;

    return it->second;
}

void GameManager::add_scene(Scene *scn)
{
    scenes[scn->get_scene_name()] = scn;
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
    TTF_Quit();
    std::cout << "Game cleaned" << std::endl;
}
