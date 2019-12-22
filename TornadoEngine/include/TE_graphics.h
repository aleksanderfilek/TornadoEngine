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
Texture *Tex_create(const char *path, int posX, int posY, uint8_t layer);
Texture *Tex_createFromSdlTexture(SDL_Texture *sdlTexture,int posX, int posY, uint8_t layer);
void Tex_setTexture(Texture *texture, SDL_Texture *sdlTexture);
void Tex_setSourceRect(Texture *texture, int x, int y, int w, int h);
void Tex_setPosition(Texture *texture,int posX, int posY);
void Tex_move(Texture *texture, int offsetX, int offsetY);
void Tex_setScale(Texture *texture, float scaleX, float scaleY);
void Tex_draw();
void Tex_free();

typedef struct{
    SDL_Texture *tilesheet;
    Vector2i position;
    Vector2f scale;
    int tileSize;
    Vector2i tileMapSize;
    uint8_t *tileplan;
}Tilemap;

int Tile_createFromArray(const char *path, uint8_t *plan, int posX, int posY, int tileSize, int tileMapWidth, int tileMapHeight);
int Tile_createFromFile(const char *path, const char *plan, int posX, int posY);

void Tile_setPosition(int tilemap, int posX, int posY);
void Tile_setScale(int tilemap, float scaleX, float scaleY);
void Tile_setElement(int tilemap, int elementIndex, uint8_t element);
void Tile_draw();
void Tile_free();
#endif