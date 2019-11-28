#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

typedef struct{
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect position;
}Texture;

SDL_Texture *loadTexture(const char *path);
void setTexturePositionXY(Texture *texture, int x, int y);
void drawTexture(Texture *texture, SDL_Renderer *renderer);
void freeTexture(Texture *texture);


typedef struct{
    TTF_Font *font;
    char *text;
    Texture *texture;
}Text;

TTF_Font *loadFont(const char *path, int size);
void setText(const char *text);
void freeText();
#endif