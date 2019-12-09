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

Button *Btn_init(TTF_Font *font, const char *text, SDL_Texture *backgroundTexture, int posX, int posY, float scaleX, float scaleY);

extern SDL_Event event;

Button *buttonSystem;
int buttonElementNumber = 0;

Button *Ecs_Btn_add(Button *button);
void Ecs_Btn_update(int mousePosX, int mousePosY, Button *buttonStructs, int number);
void Ecs_Btn_free();
#endif