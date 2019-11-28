#ifndef TEMAIN_H_
#define TEMAIN_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>

typedef struct  
{
    void (*start)();
    int (*update)();
    void (*draw)();
    void (*close)();
}State;


#endif