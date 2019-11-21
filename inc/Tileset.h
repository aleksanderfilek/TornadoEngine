#ifndef TILESET_H_
#define TILESET_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"Vector.h"

class Tileset{
private:
    char *tilemap;
    int tileScale = 0;
    int tileSize = 0;
    Vector2i tilesPerEdge;
    Vector2i position;
    Vector2i offset;
public:
    Tileset();
    ~Tileset();

    void setTilemap(char *Tilemap, int TileSize);
    void draw(SDL_Renderer *renderer);
    void free();

    void move(Vector2i Offset);
    void move(int x, int y);
};

#endif