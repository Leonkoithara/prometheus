#ifndef BUTTON
#define BUTTON

#include "game_object.h"
#include <SDL2/SDL_render.h>


class Button : public GameObject
{
private:
	int clicked;
	std::string text;
public:
	Button(std::string);
	~Button();

	bool check_clicked(int, int);
	void click_object(int, bool);
	void whileclickevent(int);
	void onceclickevent(int);
	void update();

	void set_text(std::string);

	std::string get_text() { return text; }
};


#endif
