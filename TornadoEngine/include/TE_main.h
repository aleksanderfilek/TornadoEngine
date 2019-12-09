#ifndef TEMAIN_H_
#define TEMAIN_H_

#include<stdint.h>

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"TE_graphics.h"


uint8_t TE_init(const char *title, int width, int height);
void TE_close();

typedef struct{
    void (*start)();
    int (*update)();
    void (*draw)();
    void (*close)();
}State;


typedef struct{
    uint8_t state;
    Uint32 startTicks;
}Timer;

void startTimer(Timer *timer);
Uint32 stopTimer(Timer *timer);
Uint32 restartTimer(Timer *timer);

#endif