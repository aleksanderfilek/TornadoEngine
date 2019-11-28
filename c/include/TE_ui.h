#ifndef TEUI_H_
#define TEUI_H_

#include"TE_graphics.h"

typedef struct{
    Texture *texture;
    Text *text;
    int (*clicked)();
}Button;

#endif