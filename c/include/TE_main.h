#ifndef TEMAIN_H_
#define TEMAIN_H_

#include<stdint.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>

typedef struct{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    int widht, height;
}TornadoEngine;

uint8_t TE_init(TornadoEngine *engine, const char *title, int width, int height);
void TE_close();

typedef struct{
    void (*start)();
    int (*update)();
    void (*draw)();
    void (*close)();
}State;

typedef struct{
    enum{
        stop = 0,
        start = 1,
        pause = 2
    }TimerState;

    Uint32 startTicks;
    uint8_t state;
}Timer;

void startTimer();
void closeTimer();
Uint32 restartTimer();

#endif