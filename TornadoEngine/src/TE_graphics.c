#include"TE_graphics.h"

#include<stdio.h>

void Tex_init(SDL_Renderer *renderer, const char *texturePath, int posX, int posY, int scaleX, int scaleY){

}

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

    textureStruct->sourceRect.x = 0;
    textureStruct->sourceRect.y = 0;
    textureStruct->sourceRect.w = width;
    textureStruct->sourceRect.h = height;

    textureStruct->destinationRect.x = 0;
    textureStruct->destinationRect.y = 0;
    textureStruct->destinationRect.w = width * textureStruct->scale.x;
    textureStruct->destinationRect.h = height * textureStruct->scale.y;
}

void Tex_setSourceRect(Texture *textureStruct, SDL_Rect newSourceRect){
    textureStruct->sourceRect = newSourceRect;
}

void Tex_setPosition(Texture *textureStruct, int x, int y){
    textureStruct->destinationRect.x = x;
    textureStruct->destinationRect.y = y;
}

void Tex_setScale(Texture *textureStruct, int x, int y){
    textureStruct->scale.x = x;
    textureStruct->scale.y = y;
    int width = textureStruct->sourceRect.w * x;
    int height = textureStruct->sourceRect.h * y;
    textureStruct->destinationRect.w = width;
    textureStruct->destinationRect.h = height;
}

void Tex_draw(Texture *textureStruct, SDL_Renderer *renderer){
        SDL_RenderCopy(renderer,textureStruct->texture,&textureStruct->sourceRect,&textureStruct->destinationRect);
}

void Tex_free(Texture *textureStruct){
    SDL_DestroyTexture( textureStruct->texture );
    textureStruct->texture = NULL;
    SDL_Rect src = {0,0,0,0};
    textureStruct->sourceRect = src;
    SDL_Point scale = {1,1};
    textureStruct->scale = scale;
}

TTF_Font *Text_load(SDL_Renderer *renderer, const char *path, int size){
    return TTF_OpenFont(path, size);
}

void Text_setFont(Text *textStruct, TTF_Font *font){

}

void Text_setText(SDL_Renderer *renderer, Text *textStruct, const char *newText){
    //Get rid of preexisting texture
    Text_free(textStruct);

    SDL_Color textColor = { 0, 0, 0 };
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( textStruct->font, newText, textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        SDL_Texture *mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            Tex_setTexture(textStruct->texture,mTexture);
            textStruct->text = newText;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void Text_free(Text *textStruct){
    Tex_free(textStruct->texture);
    TTF_CloseFont(textStruct->font);
    textStruct->font = NULL;
}