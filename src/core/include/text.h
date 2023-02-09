#ifndef TEXT
#define TEXT

#include "game_object.h"


class Text : public GameObject
{
private:
	std::string text;
	int length;
public:
	Text(std::string);
	~Text();

	void set_text_boundaries(std::string, int);
	void create_textures(SDL_Renderer *);
};

#endif
