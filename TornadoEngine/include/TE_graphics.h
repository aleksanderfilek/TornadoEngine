#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"TE_math.h"

typedef struct{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    Vector2f scale;
    uint8_t layer;
}Texture;

SDL_Texture *Tex_load(const char *texturePath);
int Tex_Create(const char *path, int posX, int posY, uint8_t layer);
int Tex_CreateFromSdlTexture(SDL_Texture *sdlTexture,int posX, int posY, uint8_t layer);
void Tex_setTexture(Texture *texture, SDL_Texture *sdlTexture);
void Tex_setSourceRect(Texture *texture, int x, int y, int w, int h);
void Tex_setPosition(Texture *texture,int posX, int posY);
void Tex_move(Texture *texture, int offsetX, int offsetY);
void Tex_setScale(Texture *texture, float scaleX, float scaleY);
void Tex_draw();
void Tex_free();
#endif