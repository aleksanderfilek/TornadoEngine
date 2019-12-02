#ifndef TEUI_H_
#define TEUI_H_

#include"TE_graphics.h"

typedef struct{
    enum State{
        none = 0,
        hovered = 1,
        clicked = 2
    };
    Text *text;
    Texture *texture;
    uint8_t state;
    void (*click)();
    void (*hover)();
    void (*unhover)();
}Button;

//TODO: init button function
#endif