#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "button.h"
#include "game_object.h"
#include "type_structs.h"


void button_empty_callback(int x) {};
Button::Button(std::string name) : GameObject(name)
{
	clicked = -1;
	whileclickevent = &button_empty_callback;
	onceclickevent = &button_empty_callback;
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

void Button::click_object(int button_id, bool click)
{
	if (click)
	{
		clicked = button_id;
		onceclickevent(button_id);
	}
	else
		clicked = -1;
}

void Button::set_text(std::string text)
{
	int max = get_textures()->end()->first;
	this->text = text;
	add_texturefile("button_text", max);
}

void Button::update()
{
	if (clicked >= 0)
	    whileclickevent(clicked);
}

void Button::create_textures(SDL_Renderer *renderer)
{
	auto texs = get_textures();
	if (!texs->empty())
	{
		for (auto &texture : *texs)
		{
			if (texture.second.second == NULL)
			{
				if (texture.second.first != "button_text")
				{
					SDL_Surface *surface = IMG_Load(texture.second.first.c_str());
					texture.second.second = SDL_CreateTextureFromSurface(renderer, surface);
					SDL_FreeSurface(surface);
				}
				else
				{
					TTF_Font *sans = TTF_OpenFont("res/fonts/FreeSans.ttf", 24);
					std::cout << TTF_GetError() << std::endl;
					SDL_Color white = {225, 225, 225, 255};
					SDL_Surface *msg_surface = TTF_RenderText_Blended_Wrapped(sans, text.c_str(), white, 200);
					texture.second.second = SDL_CreateTextureFromSurface(renderer, msg_surface);
				}
			}
		}

		set_render_rect_defaults();
	}
}
