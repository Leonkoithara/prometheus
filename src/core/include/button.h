#ifndef BUTTON
#define BUTTON

#include "game_object.h"


class Button : public GameObject
{
private:
	int clicked;
public:
	Button(std::string);
	~Button();

	bool check_clicked(int, int);
	void click_object(int, bool);
	void whileclickevent(int);
	void onceclickevent(int);
	void update();
};


#endif
