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

Button::Button(std::string name, bool transparent) : GameObject(name)
{
    if (!transparent)
    {
        add_texturefile("res/textures/button.png", 0);
        set_mouseonobject(change_bg_on_highlight);
        set_mouseoffobject(change_bg_off_highlight);
    }
}
Button::Button(std::string name, unsigned int key, unsigned int mod, bool transparent) : GameObject(name, key, mod)
{
    if (!transparent)
    {
        add_texturefile("res/textures/button.png", 0);
        set_mouseonobject(change_bg_on_highlight);
        set_mouseoffobject(change_bg_off_highlight);
    }
}

void Button::set_text(std::string text, vec3D text_color)
{
    int max = get_surfaces().end()->first;
    this->text_color = text_color;
    this->text = text;
    std::string textfile = get_surfaces()[max-1].first;
    if (textfile == "button_text")
    {
        SDL_FreeSurface(get_surfaces()[max-1].second);
        add_texturefile("button_text", max-1);
    }
    else
        add_texturefile("button_text", max);
}
