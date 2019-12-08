#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"TE_math.h"
#include"TE_ecs.h"

extern SDL_Renderer *renderer;

SDL_Texture **layer;

void Layer_init(int layerCount);
void Layer_free();

typedef struct{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    Vector2f scale;
    int layer;
}Texture;

Texture *Tex_init(const char *texturePath, int posX, int posY, float scaleX, float scaleY, int layer);
SDL_Texture *Tex_load(const char *texturePath);
void Tex_setTexture(Texture *textureStruct, SDL_Texture *tex);
void Tex_setSourceRect(Texture *textureStruct, SDL_Rect newSourceRect);
void Tex_setPosition(Texture *textureStruct, int x, int y);
void Tex_setScale(Texture *textureStruct, float x, floats y);
void Tex_free(Texture *textureStruct);

typedef struct{
    TTF_Font *font;
    char *text;
    Texture *texture;
}Text;

Text *Text_init(TTF_Font *font, const char *text ,int posX, int posY, float scaleX, float scaleY);
TTF_Font *Text_loadFont(const char *path, int size);
void Text_setFont(Text *textStruct, TTF_Font *font);
void Text_setText(Text *textStruct, const char *newText);
void Text_free(Text *textStruct);

#endif