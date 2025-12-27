#ifndef TILE_OBJ
#define TILE_OBJ

#include <game_object.h>

class Tile : public GameObject
{
private:
    bool highlighted;
public:
    Tile(std::string nm) : GameObject(nm)
    {
        highlighted = false;
    }

    bool is_highlighted() { return highlighted; }

    void set_highlighted(bool val) { highlighted = val; }
};

#endif
