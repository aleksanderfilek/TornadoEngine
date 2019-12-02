#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

typedef struct{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    SDL_Point scale;
}Texture;

//TODO: init texture function, where are set default things
SDL_Texture *Tex_load(SDL_Renderer *renderer, const char *path);
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

//TODO: init text function
TTF_Font *Text_load(SDL_Renderer *renderer, const char *path, int size);
void Text_setFont(Text *textStruct, TTF_Font *font);
void Text_setText(SDL_Renderer *renderer, Text *textStruct, const char *newText);
void Text_free(Text *textStruct);

#endif