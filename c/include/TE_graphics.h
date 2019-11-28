#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

typedef struct{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    
}Texture;

#endif