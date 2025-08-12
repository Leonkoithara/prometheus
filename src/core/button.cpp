#include <SDL_rect.h>
#include <SDL_surface.h>

#include <button.h>
#include <game_object.h>
#include <type_structs.h>


void change_bg_on_highlight(GameObject *button)
{
    Button *butt = static_cast<Button*>(button);
    butt->add_texturefile("res/textures/button_hlgt.png", 0);
    butt->set_text(butt->get_text(), {255, 0, 0});
}

void change_bg_off_highlight(GameObject *button)
{
    Button *butt = static_cast<Button*>(button);
    butt->add_texturefile("res/textures/button.png", 0);
    butt->set_text(butt->get_text(), {255, 255, 255});
}

Button::Button(std::string name) : GameObject(name)
{
    add_texturefile("res/textures/button.png", 0);
    set_mouseonobject(change_bg_on_highlight);
    set_mouseoffobject(change_bg_off_highlight);
}
Button::Button(std::string name, unsigned int key, unsigned int mod) : GameObject(name, key, mod)
{
    add_texturefile("res/textures/button.png", 0);
    set_mouseonobject(change_bg_on_highlight);
    set_mouseoffobject(change_bg_off_highlight);
}


void Button::set_text(std::string text)
{
    int max = get_textures().end()->first;
    this->text = text;
    add_texturefile("button_text", max);
    text_color = {255, 255, 255};
}

void Button::set_text(std::string text, vec3D text_color)
{
    int max = get_textures().end()->first;
    this->text_color = text_color;
    this->text = text;
    add_texturefile("button_text", max);
}
