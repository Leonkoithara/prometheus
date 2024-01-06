#ifndef BUTTON
#define BUTTON

#include "game_object.h"


class Button : public GameObject
{
private:
    int clicked;
    std::string text;
    char keycode_binding;

    void (*whileclickevent)(int, GameObject*);
    void (*onceclickevent)(int, GameObject*);
public:
    Button(std::string);
    Button(std::string, char);
    ~Button();

    bool check_clicked(int, int);
    void click_object(int, bool);
    void update();

    void set_text(std::string);
    void set_keybinding(char key) { keycode_binding = key; }

    std::string get_text() { return text; }
    char get_keycode_binding() { return keycode_binding; }

    void set_whileclickevent(void (*func)(int, GameObject*)) { whileclickevent = func; }
    void set_onclickevent(void (*func)(int, GameObject*)) { onceclickevent = func; }
};


#endif
