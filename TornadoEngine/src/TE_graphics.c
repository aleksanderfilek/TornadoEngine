#include"TE_graphics.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern SDL_Renderer *renderer;

Texture *textureSystem;
int textureSystemLength = 0;
int textureSystemCapacity = 0;

static Texture *addTexture(const Texture *texture){
    if(textureSystemLength >= textureSystemCapacity){
        textureSystemCapacity += 5;
        textureSystem = (Texture *)realloc(textureSystem,textureSystemCapacity * sizeof(Texture));
    }

    textureSystem[textureSystemLength++] = *texture;
    return &textureSystem[textureSystemLength-1];
}

Texture *Tex_create(const char *path, int posX, int posY, uint8_t layer){
    Texture texture;
    texture.layer = layer;
    Tex_setTexture(&texture,Tex_load(path));
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture, 1.0f, 1.0f);
    return addTexture(&texture);
}

Texture *Tex_createFromSdlTexture(SDL_Texture *sdlTexture,int posX, int posY, uint8_t layer){
    Texture texture;
    Tex_setTexture(&texture, sdlTexture);
    texture.layer = layer;
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture,1.0f,1.0f);

    return addTexture(&texture);
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

void Tex_setTexture(Texture *texture, SDL_Texture *sdlTexture){
    /*
    if(texture->texture != NULL){
        printf("destroy");
        SDL_DestroyTexture(texture->texture);
    }
    */
    texture->texture = sdlTexture;
    int w,h;
    SDL_QueryTexture(sdlTexture,NULL,NULL,&w,&h);
    Tex_setSourceRect(texture,0,0,w,h);
    Tex_setScale(texture,texture->scale.x,texture->scale.y);
}

void Tex_setSourceRect(Texture *texture, int x, int y, int w, int h){
    texture->sourceRect.x = x;
    texture->sourceRect.y = y;
    texture->sourceRect.w = w;
    texture->sourceRect.h = h;
}

void Tex_setPosition(Texture *texture,int posX, int posY){
    texture->destinationRect.x = posX;
    texture->destinationRect.y = posY;
}

void Tex_move(Texture *texture, int offsetX, int offsetY){
    texture->destinationRect.x += offsetX;
    texture->destinationRect.y += offsetY;
}

void Tex_setScale(Texture *texture, float scaleX, float scaleY){
    texture->scale.x = scaleX;
    texture->scale.y = scaleY;
    texture->destinationRect.w = (int)(scaleX * texture->sourceRect.w);
    texture->destinationRect.h = (int)(scaleY * texture->sourceRect.h);
}

int textureCompare(const void *a, const void *b){
    Texture _a = *(Texture*)a;
    Texture _b = *(Texture*)b;
    if(_a.layer < _b.layer) return -1;
    else if(_a.layer == _b.layer) return 0;
    else return 1;
}

void Tex_draw(){
    Texture *textures = malloc(textureSystemLength*sizeof(Texture));
    memcpy(textures,textureSystem,textureSystemLength*sizeof(Texture));
    qsort(textures,textureSystemLength,sizeof(Texture),textureCompare);

    Texture texture;
    int i;
    for(i = 0; i < textureSystemLength; i++){
        texture = textures[i];
        SDL_RenderCopy(renderer,texture.texture,&texture.sourceRect,&texture.destinationRect);
    }
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
        fscanf(file,"%d",&plan[i]);
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
        SDL_Rect dstRect = {tilemap.position.x,tilemap.position.y,tilemap.tileSize,tilemap.tileSize};
        int number = tilemap.tileMapSize.x * tilemap.tileMapSize.y;
        int x,y;
        for(y = 0; y < tilemap.tileMapSize.y; y++){
            for(x = 0; x < tilemap.tileMapSize.x; x++){
                dstRect.x += tilemap.tileSize;
                //zmiana sourceRectu'u
                SDL_RenderCopy(renderer, tilemap.tilesheet,&srcRect,&dstRect);
            }
            dstRect.x = 0;
            dstRect.y += tilemap.tileSize;
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

