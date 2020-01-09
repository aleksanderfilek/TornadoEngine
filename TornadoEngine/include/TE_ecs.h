#ifndef TEECS_H_
#define TEECS_H_

#include<SDL2/SDL.h>

#include"TE_graphics.h"
#include"TE_ui.h"

extern SDL_Renderer *renderer;
extern SDL_Event e;

Texture *textureSystem;
int textureElementNumber = 0;

Texture *Ecs_Tex_Add(Texture *texture);
void Ecs_Tex_draw();
void Ecs_Tex_free();

Button *buttonSystem;
int buttonElementNumber = 0;

void Ecs_Btn_add(Button button);
void Ecs_Btn_update(int mousePosX, int mousePosY, Button *buttonStructs, int number);
void Ecs_Btn_free();

void Ecs_clear();
#endif