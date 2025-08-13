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
    vao = 0;
    gl_render_ready = 0;
}

void Scene::create_window(std::string title, int xpos, int ypos, int width, int height, vec3D bg_color, bool full_screen)
{
    int flags = 0;
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
    opengl_contxt = SDL_GL_CreateContext(window);
    gm.init_opengl();
    active_scene = true;
}

void Scene::click_objects(int xpos, int ypos, int button_id, bool click)
{
    for (auto &it : game_objects )
    {
        GameObject *obj = it.second;
        if (obj->check_mouse_on(xpos, ypos))
            obj->click_object(button_id, click);
    }
}

void Scene::mouse_update_event(int xpos, int ypos)
{
    for (auto &it : game_objects )
    {
        GameObject *obj = it.second;
        if (obj->check_mouse_on(xpos, ypos))
            obj->mouse_on_object();
    }
}

void Scene::process_keystroke(unsigned int key, unsigned int mod, bool down)
{
    for (auto &it : game_objects )
    {
        Button *obj = dynamic_cast<Button*>(it.second);
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

void Scene::add_game_object(GameObject *obj)
{
    std::string game_obj_name = obj->get_name();
    auto it = game_objects.find(game_obj_name);
    if (it == game_objects.end())
        game_objects[game_obj_name] = obj;
}

void Scene::update()
{
    if (update_scene)
    {
        for (auto &it : game_objects)
            it.second->update();
    }
}

void Scene::set_vao(const void *vao_data, int size)
{
    glCreateVertexArrays(1, &vao);
    glBindVertexArray( vao );
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, vao_data, GL_STATIC_DRAW);
    gl_render_ready |= 1;
}

void Scene::read_shader_code(std::string filename, enum SHADER_TYPE type)
{
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    
    if(type == VERTEX_SHADER)
        vertex_shader = buffer.str();
    else if (type == FRAGMENT_SHADER)
        fragment_shader = buffer.str();
    else
        std::cout << "Invalid shader type" << std::endl;
}

void Scene::create_shader_program()
{
    shader_program = glCreateProgram();
    const char* src_v = vertex_shader.c_str();
    const char* src_f = fragment_shader.c_str();

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &src_v, NULL);
    glCompileShader(vs);

    int success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &src_f, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shader_program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    gl_render_ready |= 2;
}

void Scene::render()
{
    if (active_scene)
    {
        SDL_RenderClear(renderer);
        
        for (auto it : game_objects)
        {
            SDL_Rect src = it.second->get_src_render_rect();
            SDL_Rect dest = it.second->get_dest_render_rect();

            auto surfaces = it.second->get_surfaces();
            for (auto itr : surfaces)
            {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, itr.second.second);
                SDL_RenderCopy(renderer, texture, &src, &dest);
            }
        }

        SDL_RenderFlush(renderer);

        if (gl_render_ready == 3)
        {
            SDL_GL_MakeCurrent(window, opengl_contxt);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        SDL_RenderPresent(renderer);
    }
}

Scene::~Scene()
{
    for (auto &it : game_objects)
        delete it.second;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
