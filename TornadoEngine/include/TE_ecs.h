#ifndef TEECS_H_
#define TEECS_H_

#include<SDL2/SDL.h>

#include"TE_graphics.h"
#include"TE_ui.h"

void Ecs_Tex_draw(SDL_Renderer *renderer,const Texture *textureStructs, int number);
void Ecs_Btn_update(SDL_Event *e, Button *buttonStructs, int number);

#endif