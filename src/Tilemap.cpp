#include"Tilemap.h"

Tilemap::Tilemap(){

}

Tilemap::~Tilemap(){
    free();
}

void Tilemap::setTilemap(char *TilesetNum, int TileSize, int TileScale, Vector2i TilesPerEdge){
    this->tilesetNum = TilesetNum;
    this->tileScale = TileScale;
    this->tileSize = TileSize;
    this->tilesPerEdge = TilesPerEdge
}

void Tilemap::draw(SDL_Renderer *renderer){     //przemyslec obliczenia!!!
    SDL_Rect srcRect = {0,0,this->tileSize,this->tileSize};
    int tileSizeScale = this->tileSize * this->tileScale;
    SDL_Rect dstRect = {0,0,tileSizeScale,tileSizeScale};
    for(int x = 0; x < this->tilesPerEdge.x; x++){
        for(int y = 0; y < this->tilesPerEdge.y; y++){
            srcRect.x = (x*this->tileSize) % this->tilesInRow;
            srcRect.y = (y*this->tileSize) % this->tilesInRow;
            dstRect.x = -this->offset.x + x*tileSizeScale;
            dstRect.y = -this->offset.y + y*tileSizeScale;
            SDL_RenderCopy(renderer,this->tileset,&srcRect,&dstRect);
        }
    }
}

void Tilemap::free(){
    delete this->tilesetNum;
    this->tileScale = 0;
    this->tileSize = 0;
    this->tilesPerEdge = {0,0};
    this->position = {0.0};
    this->offset = {0,0};
}

void Tilemap::move(Vector2i Offset){
    this->offset = this->offset + Offset;

    if(this->offset.x >= this->tileSize){
        this->position.x += (this->offset.x > 0)?1:-1;
        this->offset.x %= this->tileSize;
    }

    if(this->offset.y >= this->tileSize){
        this->position.y += (this->offset.x > 0)?1:-1;
        this->offset.y %= this->tileSize;
    }
}