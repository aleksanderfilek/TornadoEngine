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

Texture *Tex_Create(const char *path, int posX, int posY, uint8_t layer){
    Texture texture;
    texture.layer = layer;
    Tex_setTexture(&texture,Tex_load(path));
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture, 1.0f, 1.0f);
    return addTexture(&texture);
}

Texture *Tex_CreateFromSdlTexture(SDL_Texture *sdlTexture,int posX, int posY, uint8_t layer){
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
    SDL_RenderClear(renderer);
    Texture *textures = malloc(textureSystemLength*sizeof(Texture));
    memcpy(textures,textureSystem,textureSystemLength*sizeof(Texture));
    qsort(textures,textureSystemLength,sizeof(Texture),textureCompare);

    Texture texture;
    int i;
    for(i = 0; i < textureSystemLength; i++){
        texture = textures[i];
        SDL_RenderCopy(renderer,texture.texture,&texture.sourceRect,&texture.destinationRect);
    }
    SDL_RenderPresent(renderer);
    free(textures);
}

void Tex_free(){
    int i;
    for(i = textureSystemLength-1; i>=0;i--){
        SDL_DestroyTexture(textureSystem[i].texture);
    }
    free(textureSystem);
}
