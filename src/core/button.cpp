#include "button.h"
#include "SDL_rect.h"
#include "game_object.h"
#include "type_structs.h"
#include <ostream>


Button::Button(std::string name) : GameObject(name) {
	clicked = -1;
}

bool Button::check_clicked(int xpos, int ypos)
{
	vec3D pos = this->get_position();
	SDL_Rect rect = this->get_dest_render_rect();
	if (
		xpos >= pos.x &&
		ypos >= pos.y &&
		xpos <= rect.x+rect.w &&
		ypos <= rect.y+rect.h
	)
		return true;
	return false;
}

void Button::click_object(int button_id, bool unclick)
{
	if (unclick)
	    clicked = -1;
	else
	{
		clicked = button_id;
		onceclickevent(button_id);
	}
}

void Button::onceclickevent(int buttonid)
{
	std::cout << "Clicked: " << get_name() << std::endl;
}

void Button::whileclickevent(int mouse)
{
	std::cout << "Click ongoing" << std::endl;
}

void Button::update()
{
	if (clicked >= 0)
	    whileclickevent(clicked);
}
