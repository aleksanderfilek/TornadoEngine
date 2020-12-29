#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include"TE.h"

#include<SDL2/SDL.h>

#include<GL/glew.h>

#include<stdint.h>

void TE_clear();
void TE_set_background_color(uint8_t R, uint8_t G, uint8_t B);
void TE_render();


#endif