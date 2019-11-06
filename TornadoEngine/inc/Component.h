#ifndef CCOMPONENT_H_
#define CCOMPONENT_H_

#include<SDL2/SDL.h>

class Component{
public:
    Component(){}
    virtual ~Component() = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer *renderer) = 0;
};

#endif