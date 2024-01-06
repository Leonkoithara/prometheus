#include <SDL_rect.h>
#include <SDL_surface.h>

#include "button.h"
#include "game_object.h"
#include "type_structs.h"


void button_empty_callback(int x, GameObject*) {};
Button::Button(std::string name) : GameObject(name)
{
    clicked = -1;
    whileclickevent = &button_empty_callback;
    onceclickevent = &button_empty_callback;
}

bool Button::check_clicked(int xpos, int ypos)
{
    SDL_Rect rect = this->get_dest_render_rect();
    if (
        xpos >= rect.x &&
        ypos >= rect.y &&
        xpos <= rect.x+rect.w &&
        ypos <= rect.y+rect.h
    )
        return true;
    return false;
}

void Button::click_object(int button_id, bool click)
{
    if (click)
    {
        clicked = button_id;
        onceclickevent(button_id, this);
    }
    else
        clicked = -1;
}

void Button::set_text(std::string text)
{
    int max = get_textures().end()->first;
    this->text = text;
    add_texturefile("button_text", max);
}

void Button::update()
{
    if (clicked >= 0)
        whileclickevent(clicked, this);
}
