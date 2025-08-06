#ifndef CHARACTER
#define CHARACTER

#include <iostream>

#include <scene.h>
#include <type_structs.h>

class Character
{
protected:
    std::string name;
    vec3D position;
public:
    Character(std::string nm, vec3D pos) { name = nm; position = pos; }
};

class Player : Character
{
private:
    Scene *player_scene;
public:
    Player(std::string nm) : Character(nm, {0, 0, 0}) {}

    void spawn_player();
};

#endif
