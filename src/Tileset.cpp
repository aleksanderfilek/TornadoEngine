#include"Tileset.h"

Tileset::Tileset(){

}

Tileset::~Tileset(){
    free();
}

void Tileset::setTilemap(char *Tilemap, int TileScale){
    tilemap = Tilemap;
    tileScale = TileScale;
}

void Tileset::draw(SDL_Renderer *renderer){
    for(int x = 0; x < this->tilesPerEdge.x; x++){
        for(int y = 0; y < this->tilesPerEdge.y; y++){

        }
    }
}

void Tileset::free(){
    delete tilemap;
}

void Tileset::move(Vector2i Offset){
    this->offset = this->offset + Offset;
    if(offset.x >= this->tileSize){
        position.x += 1;
        offset.x -= this->tileSize;
    }
    else if(){

    }
    if(offset.y >= this->tileSize){
        position.y += 1;
        offset.y -= this->tileSize;
    }
}