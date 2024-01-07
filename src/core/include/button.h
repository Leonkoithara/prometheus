#ifndef BUTTON
#define BUTTON

#include "game_object.h"


class Button : public GameObject
{
private:
    int clicked;
    std::string text;
    unsigned int keycode_binding;
    unsigned int keycode_binding_mod;

    void (*whileclickevent)(int, GameObject*);
    void (*onceclickevent)(int, GameObject*);
public:
    Button(std::string);
    Button(std::string, unsigned int, unsigned int = 0);
    ~Button();

    bool check_clicked(int, int);
    void click_object(int, bool);
    void update();

    void set_text(std::string);
    void set_keybinding(char key) { keycode_binding = key; }

    std::string get_text() { return text; }
    unsigned int get_keycode_binding() { return keycode_binding; }
    unsigned int get_keycode_binding_mod() { return keycode_binding_mod; }

    void set_whileclickevent(void (*func)(int, GameObject*)) { whileclickevent = func; }
    void set_onclickevent(void (*func)(int, GameObject*)) { onceclickevent = func; }
};


#endif
