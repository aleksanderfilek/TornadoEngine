#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"TE_ecs.h"

typedef struct{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    SDL_Point scale;
}Texture;

Texture *Tex_init(SDL_Renderer *renderer, const char *texturePath, int posX, int posY, int scaleX, int scaleY);
SDL_Texture *Tex_load(SDL_Renderer *renderer, const char *texturePath);
void Tex_setTexture(Texture *textureStruct, SDL_Texture *tex);
void Tex_setSourceRect(Texture *textureStruct, SDL_Rect newSourceRect);
void Tex_setPosition(Texture *textureStruct, int x, int y);
void Tex_setScale(Texture *textureStruct, int x, int y);
void Tex_draw(Texture *textureStruct, SDL_Renderer *renderer);
void Tex_free(Texture *textureStruct);

typedef struct{
    TTF_Font *font;
    char *text;
    Texture *texture;
}Text;

Text *Text_init(SDL_Renderer *renderer, const char *fontPath, int size, const char *text ,int posX, int posY, int scaleX, int scaleY);
TTF_Font *Text_loadFont(const char *path, int size);
void Text_setFont(Text *textStruct, TTF_Font *font);
void Text_setText(SDL_Renderer *renderer, Text *textStruct, const char *newText);
void Text_free(Text *textStruct);

#endif