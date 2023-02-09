#include <SDL_ttf.h>
#include <SDL_render.h>
#include <utility>

#include "text.h"
#include "game_object.h"

Text::Text(std::string name) : GameObject(name) {}

void Text::set_text_boundaries(std::string text, int length)
{
	this->text = text;
	this->length = length;
	auto file_tex_pair = get_textures();
	(*file_tex_pair)[0] = std::make_pair("text", (SDL_Texture*)NULL);
}

void Text::create_textures(SDL_Renderer *renderer)
{
	auto texs = get_textures();
	if (!texs->empty())
	{
		if (texs->at(0).second == NULL)
		{
			TTF_Font *sans = TTF_OpenFont("res/fonts/FreeSans.ttf", 24);
			SDL_Color white = {225, 225, 225, 255};
			SDL_Surface *msg_surface = TTF_RenderText_Blended_Wrapped(sans, text.c_str(), white, length);
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, msg_surface);
			texs->at(0).second = texture;

			set_render_rect_defaults();
		}
	}
}
