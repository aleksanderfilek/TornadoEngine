#include"Texture.h"
#include<stdio.h>
Texture::Texture(){
}

Texture::~Texture(){
    free();
}

bool Texture::setTexture(const char *path, SDL_Renderer *renderer){
    this->texture = Texture::loadTexture(path,renderer);
    SDL_QueryTexture(this->texture,NULL,NULL,&this->sourceRect.w,&this->sourceRect.h);
    setScale(1,1);
    return this->texture != NULL;
}

SDL_Texture *Texture::loadTexture(const char *path, SDL_Renderer *renderer){
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

void Texture::free(){
    SDL_DestroyTexture( this->texture );
    this->texture = NULL;
    setSourceRect({0,0,0,0});
}

void Texture::render(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer,this->texture,&this->sourceRect,&this->destinationRect);
}

void Texture::renderEx(SDL_Renderer *renderer,double angle, SDL_Point *center,SDL_RendererFlip flip){
    SDL_RenderCopyEx(renderer, this->texture, &this->sourceRect , &this->destinationRect,angle, center, flip);
}

void Texture::setPosition(const int x, const int y){
    this->destinationRect.x = x;
    this->destinationRect.y = y;
}

void Texture::setPosition(const SDL_Point position){
    this->destinationRect.x = position.x;
    this->destinationRect.y = position.y;
}

void Texture::move(const int x, const int y){
    this->destinationRect.x += x;
    this->destinationRect.y += y;
}

void Texture::move(const SDL_Point offset){
    this->destinationRect.x += offset.x;
    this->destinationRect.y += offset.y;
}

void Texture::setScale(const int x, const int y){
    this->scale.x = x;
    this->scale.y = y;
    this->destinationRect.w = this->sourceRect.w * this->scale.x;
    this->destinationRect.h = this->sourceRect.h * this->scale.y;
}

void Texture::setScale(const SDL_Point _scale){
    this->scale.x = _scale.x;
    this->scale.y = _scale.y;
    this->destinationRect.w = this->sourceRect.w * this->scale.x;
    this->destinationRect.h = this->sourceRect.h * this->scale.y;
}