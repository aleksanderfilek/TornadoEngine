#include"TE_graphics.h"

#include<stdio.h>

SDL_Texture *Tex_load(SDL_Renderer *renderer, const char *path){
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void Tex_setTexture(Texture *textureStruct, SDL_Texture *tex){
    textureStruct->texture = tex;
    int width, height;
    SDL_QueryTexture(tex,NULL,NULL,&width,&height);
    textureStruct->sourceRect = {0,0,width,height};
}

void Tex_setSourceRect(Texture *textureStruct, SDL_Rect newSourceRect){
    textureStruct->sourceRect = newSourceRect;
}

void Tex_setPosition(Texture *textureStruct, int x, int y){
    textureStruct->destinationRect.x = x;
    textureStruct->destinationRect.y = y;
}

void Tex_setScale(Texture *textureStruct, int x, int y){
    int width = textureStruct->sourceRect.w * x;
    int height = textureStruct->sourceRect.h * y;
    textureStruct->destinationRect.w = width;
    textureStruct->destinationRect.h = height;
}

void Tex_draw(Texture *textureStruct, SDL_Renderer *renderer){

}

void Tex_free(Texture *textureStruct){

}