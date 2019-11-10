#include"Texture.h"

Texture::Texture(){

}

Texture::~Texture(){
    free();
}

bool Texture::setTexture(const char *path, SDL_Renderer *renderer){
    this->texture = loadTexture(path,renderer);
        
    return this->texture != NULL;
}

static SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer){
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
    SDL_RenderCopy(this->render,this->texture,&this->sourceRect,&getDestinationRect());
}

void Texture::render(SDL_Renderer *renderer,const double angle, const SDL_Point *center,const SDL_RendererFlip flip = SDL_FLIP_NONE){
    SDL_RenderCopyEx(renderer, this->texture, &this->sourceRect , &getDestinationRect(),angle, center, flip);
}

