#include"TE_graphics.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void Layer_init(int layerCount){
    layer = (SDL_Texture **)malloc(layerCount * sizeof(SDL_Texture *));
    int w,h;
    SDL_GetRendererOutputSize(renderer,&w,&h);
    int i;
    for(i = 0;i<layerCount;i++){
        layer[i] = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,w,h);
    }
}

void Layer_free(){
    int layerCount = sizeof(layer)/sizeof(SDL_Texture*);
    int i;
    for(i = 0; i < layerCount; i++){
        SDL_DestroyTexture(layer[i]);
        layer[i] = NULL;
    }
    free(layer);
}

Texture *Tex_init(const char *texturePath, int posX, int posY, float scaleX, float scaleY){
    Texture texture;
    if(texturePath != NULL){
        SDL_Texture *tex = Tex_load(texturePath);
        Tex_setTexture(&texture,tex);
    }
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture,scaleX,scaleY);
    Ecs_Tex_Add(texture);
    return &texture;
}

SDL_Texture *Tex_load(const char *texturePath){
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( texturePath );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", texturePath, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", texturePath, SDL_GetError() );
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

void Tex_setScale(Texture *textureStruct, float x, float y){
    textureStruct->scale.x = x;
    textureStruct->scale.y = y;
    int width = (int)(textureStruct->sourceRect.w * x);
    int height = (int)(textureStruct->sourceRect.h * y);
    textureStruct->destinationRect.w = width;
    textureStruct->destinationRect.h = height;
}

void Tex_free(Texture *textureStruct){
    SDL_DestroyTexture( textureStruct->texture );
    textureStruct->texture = NULL;
    SDL_Rect src = {0,0,0,0};
    textureStruct->sourceRect = src;
    Vector2f scale = {1,1};
    textureStruct->scale = scale;
}

Text *Text_init(TTF_Font *font, const char *text ,int posX, int posY, float scaleX, float scaleY){
    Text textStruct;
    textStruct.font = font;
    Text_setText(renderer,&textStruct,text);
    Tex_setPosition(&textStruct.texture,posX,posY);
    Tex_setScale(&textStruct.texture,scaleX,scaleY);
    return &textStruct;
}

TTF_Font *Text_loadFont(const char *path, int size){
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
            strcpy(textStruct->text,newText);
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