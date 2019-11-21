#ifndef TILESET_H_
#define TILESET_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"Vector.h"

class Tilemap{
private:
    char *tilesetNum;
    int tileScale = 0;
    int tileSize = 0;
    Vector2i tilesPerEdge;
    Vector2i position;
    Vector2i offset;

    SDL_Texture *tileset;
    int tilesInRow = 0;
public:
    Tilemap();
    ~Tilemap();

    void setTilemap(char *Tilemap, int TileSize, int TileScale, Vector2i TilesPerEdge);
    void draw(SDL_Renderer *renderer);
    void free();
    void setTileset(SDL_Texture *Tileset, int TilesInRow){tileset = Tileset; tilesInRow = TilesInRow;}

    void setPosition(Vector2i Position){position = Position;}
    void setPosition(int x, int y){position = {x,y};}
    void move(Vector2i Offset);
    void move(int x, int y);
};

#endif