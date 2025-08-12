#ifndef BUTTON
#define BUTTON

#include <game_object.h>
#include <type_structs.h>


class Button : public GameObject
{
private:
    std::string text;
    vec3D text_color;
public:
    Button(std::string);
    Button(std::string, unsigned int, unsigned int = 0);

    void start() {};
    void update() {};

    void set_text(std::string);
    void set_text(std::string, vec3D);

    bool check_mouse_on(int, int);

    std::string get_text() { return text; }
    vec3D get_text_color() { return text_color; }
};


#endif
