#ifndef BUTTON
#define BUTTON

#include "game_object.h"


class Button : public GameObject
{
private:
    int clicked;
    std::string text;

    void (*whileclickevent)(int, GameObject*);
    void (*onceclickevent)(int, GameObject*);
public:
    Button(std::string);
    ~Button();

    bool check_clicked(int, int);
    void click_object(int, bool);
    void update();

    void set_text(std::string);

    std::string get_text() { return text; }

    void set_whileclickevent(void (*func)(int, GameObject*)) { whileclickevent = func; }
    void set_onclickevent(void (*func)(int, GameObject*)) { onceclickevent = func; }
};


#endif
