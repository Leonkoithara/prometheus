#ifndef PLAYING_AREA
#define PLAYING_AREA

#include <scene.h>


class PlayingArea : public Scene
{
public:
    PlayingArea(std::string nm) : Scene(nm) {}

    void render();
};

#endif
