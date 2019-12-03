#ifndef TEECS_H_
#define TEECS_H_

#include<SDL2/SDL.h>

#include"TE_graphics.h"
#include"TE_ui.h"

extern SDL_Renderer *renderer;
extern SDL_Event e;

Texture *textureSystem;
int textureElementNumber = 0;

void Ecs_Tex_Add(Texture texture);
void Ecs_Tex_draw();
void Ecs_Tex_free();

Text *text;
int textElementNumber = 0;

void Ecs_Btn_update(int mousePosX, int mousePosY, Button *buttonStructs, int number);

#endif