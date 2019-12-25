#include"TE_graphics.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern SDL_Renderer *renderer;

Texture *textureSystem;
int textureSystemLength = 0;
int textureSystemCapacity = 0;

static int addTexture(){
    if(textureSystemLength >= textureSystemCapacity){
        textureSystemCapacity += 5;
        textureSystem = (Texture *)realloc(textureSystem,textureSystemCapacity * sizeof(Texture));
    }
    textureSystemLength++;
    return textureSystemLength-1;
}

int Tex_create(const char *path, int posX, int posY, uint8_t layer){
    Texture texture;
    texture.layer = layer;
    SDL_Texture *tex = Tex_load(path);

    int index = addTexture();
    Tex_setTexture(index,tex);
    Tex_setPosition(index,posX,posY);
    Tex_setScale(index,1.f,1.f);
    return index;
}

int Tex_createFromSdlTexture(SDL_Texture *sdlTexture,int posX, int posY, uint8_t layer){
    Texture texture;
    texture.layer = layer;

    int index = addTexture();
    Tex_setTexture(index,sdlTexture);
    Tex_setPosition(index,posX,posY);
    Tex_setScale(index,1.f,1.f);

    return index;
}

SDL_Texture *Tex_load(const char *path){
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n",path,IMG_GetError());
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL){
            printf("Unable to create texture from %s! SDL_image Error: %s\n",path,IMG_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Tex_setTexture(int textureIndex, SDL_Texture *sdlTexture){
    /*
    if(texture->texture != NULL){
        printf("destroy");
        SDL_DestroyTexture(texture->texture);
    }
    */
    textureSystem[textureIndex].texture = sdlTexture;
    int w,h;
    SDL_QueryTexture(sdlTexture,NULL,NULL,&w,&h);
    Tex_setSourceRect(textureIndex,0,0,w,h);
    Tex_setScale(textureIndex,textureSystem[textureIndex].scale.x,textureSystem[textureIndex].scale.y);
}

void Tex_setSourceRect(int textureIndex, int x, int y, int w, int h){
    textureSystem[textureIndex].sourceRect.x = x;
    textureSystem[textureIndex].sourceRect.y = y;
    textureSystem[textureIndex].sourceRect.w = w;
    textureSystem[textureIndex].sourceRect.h = h;
}

void Tex_setPosition(int textureIndex,int posX, int posY){
    textureSystem[textureIndex].destinationRect.x = posX;
    textureSystem[textureIndex].destinationRect.y = posY;
}

void Tex_move(int textureIndex, int offsetX, int offsetY){
    textureSystem[textureIndex].destinationRect.x += offsetX;
    textureSystem[textureIndex].destinationRect.y += offsetY;
}

void Tex_setScale(int textureIndex, float scaleX, float scaleY){
    textureSystem[textureIndex].scale.x = scaleX;
    textureSystem[textureIndex].scale.y = scaleY;
    textureSystem[textureIndex].destinationRect.w = (int)(scaleX * textureSystem[textureIndex].sourceRect.w);
    textureSystem[textureIndex].destinationRect.h = (int)(scaleY * textureSystem[textureIndex].sourceRect.h);
}

int textureCompare(const void *a, const void *b){
    Texture _a = *(Texture*)a;
    Texture _b = *(Texture*)b;
    if(_a.layer < _b.layer) return -1;
    else if(_a.layer == _b.layer) return 0;
    else return 1;
}

void Tex_draw(){
    Texture *textures = (Texture *)malloc(textureSystemLength*sizeof(Texture));
    memcpy(textures,textureSystem,textureSystemLength*sizeof(Texture));
    qsort(textures,textureSystemLength,sizeof(Texture),textureCompare);

    Texture texture;
    int i;
    for(i = 0; i < textureSystemLength; i++){
        texture = textures[i];
        SDL_RenderCopy(renderer,texture.texture,&texture.sourceRect,&texture.destinationRect);
    }
    //printf("i = %d\n",i);
    free(textures);
}

void Tex_free(){
    int i;
    for(i = textureSystemLength-1; i>=0;i--){
        SDL_DestroyTexture(textureSystem[i].texture);
    }
    free(textureSystem);
}

Tilemap *tilemapSystem;
int tilemapSystemLength = 0;

/*
int Tile_createFromArray(const char *path, uint8_t *plan, int posX, int posY, int tileSize, int tileMapWidth, int tileMapHeight){
    tilemapSystemLength++;
    tilemapSystem = (Tilemap *)realloc(tilemapSystem, tilemapSystemLength*sizeof(Tilemap));

    Tilemap tilemap;
    tilemap.position.x = posX;
    tilemap.position.y = posY;
    tilemap.scale.x = 1;
    tilemap.scale.y = 1;
    tilemap.tileSize = tileSize;
    tilemap.tileMapSize.x = tileMapWidth;
    tilemap.tileMapSize.y = tileMapHeight;
    
    if(plan != NULL){
        int number = tileMapWidth * tileMapHeight;
        tilemap.tileplan = malloc(number * sizeof(uint8_t));
        memcpy(tilemap.tileplan,plan,number);

        free(plan);
        plan = NULL;
    }

    tilemap.tilesheet = Tex_load(path);
    tilemapSystem[tilemapSystemLength-1] = tilemap;

    return tilemapSystemLength-1;
}

int Tile_createFromFile(const char *path, const char *planPath, int posX, int posY){

    FILE *file;
    file = fopen(planPath,"r");

    int size,width, height;
    fscanf(file,"%d",&size);
    fscanf(file,"%d",&width);
    fscanf(file,"%d",&height);

    int number = width * height;

    uint8_t *plan = malloc(number * sizeof(uint8_t));

    int i;
    for(i = 0; i < number; i++){
        fscanf(file,"%hhd",&plan[i]);
    }

    fclose(file);
    
    int index = Tile_createFromArray(path,plan,posX,posY,size,width,height);

    return index;
}

void Tile_setPosition(int tilemap, int posX, int posY){
    tilemapSystem[tilemap].position.x = posX;
    tilemapSystem[tilemap].position.y = posY;
}

void Tile_setScale(int tilemap, float scaleX, float scaleY){
    tilemapSystem[tilemap].scale.x = scaleX;
    tilemapSystem[tilemap].scale.y = scaleY;
}

void Tile_setElement(int tilemap, int elementIndex, uint8_t element){
    tilemapSystem[tilemap].tileplan[elementIndex] = element;
}

void Tile_draw(){
    Tilemap tilemap;
    int i;
    for(i = 0; i < tilemapSystemLength; i++){
        tilemap = tilemapSystem[i];
        SDL_Rect srcRect = {0,0,tilemap.tileSize,tilemap.tileSize};
        SDL_Rect dstRect = {
            tilemap.position.x,
            tilemap.position.y,
            (int)(tilemap.tileSize * tilemap.scale.x),
            (int)(tilemap.tileSize * tilemap.scale.y)
            };
        int number = tilemap.tileMapSize.x * tilemap.tileMapSize.y;
        int w,h;
        SDL_QueryTexture(tilemap.tilesheet,NULL,NULL,&w,&h);
        w /= tilemap.tileSize;
        h /= tilemap.tileSize;
        int x,y;
        for(y = 0; y < tilemap.tileMapSize.y; y++){
            for(x = 0; x < tilemap.tileMapSize.x; x++){
                dstRect.x += (int)(tilemap.tileSize * tilemap.scale.x);
                srcRect.x = tilemap.tileSize * (tilemap.tileplan[tilemap.tileMapSize.x*y + x] % w);
                srcRect.y = tilemap.tileSize * (tilemap.tileplan[tilemap.tileMapSize.x*y + x] / w);
                SDL_RenderCopy(renderer, tilemap.tilesheet,&srcRect,&dstRect);
            }
            dstRect.x = tilemap.position.x;
            dstRect.y += (int)(tilemap.tileSize* tilemap.scale.y);
        }
    }
}

void Tile_free(){
    int i;
    for(i = 0; i < tilemapSystemLength; i++){
        free(tilemapSystem[i].tileplan);
        SDL_DestroyTexture(tilemapSystem[i].tilesheet);
    }
}
*/
