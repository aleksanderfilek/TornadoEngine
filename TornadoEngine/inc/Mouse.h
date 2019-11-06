#ifndef MOUSE_H_
#define MOUSE_H_

#include<SDL2/SDL.h>

class Mouse{
private:
    SDL_Event *event;
public:
    Mouse();
    ~Mouse();


};

#endif