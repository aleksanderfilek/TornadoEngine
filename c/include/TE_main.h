#ifndef TEMAIN_H_
#define TEMAIN_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>

typedef struct{
    char *title;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
}Engine;

typedef struct  
{
    void (*start)();
    int (*update)();
    void (*draw)();
    void (*close)();
}State;

int TE_init(Engine *engine, char *title, int width, int heigh);
void TE_close(Engine *engine);

#endif