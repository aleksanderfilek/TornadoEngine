#ifndef TEMAIN_H_
#define TEMAIN_H_

#include<stdint.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;

int screenWidth,screenHeight;

uint8_t TE_init(const char *title, int width, int height);
void TE_close();

typedef struct{
    void (*start)();
    int (*update)();
    void (*draw)();
    void (*close)();
}State;

typedef struct{
    enum TimerState{
        stop = 0,
        start = 1
    };

    Uint32 startTicks;
    uint8_t state;
}Timer;

void startTimer(Timer *timer);
Uint32 stopTimer(Timer *timer);
Uint32 restartTimer(Timer *timer);

#endif