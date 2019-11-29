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
}Texture;

SDL_Texture *Tex_load(SDL_Renderer *renderer, const char *path);
void Tex_setSourceRect(Texture *texture, SDL_Rect newSourceRect);
void Tex_setPosition(Texture *texture, int x, int y);
void Tex_setScale(Texture *texture, int x, int y);
void Tex_free(Texture *texture);

typedef struct{
    TTF_Font *font;
    char *text;
    Texture *texture;
}Text;

TTF_Font *Text_load(SDL_Renderer *renderer, const char *path);
void Text_free(Text *text);

#endif