#include"Text.h"

Text::Text(char *_text, const char *path, int size, SDL_Renderer *renderer)
:text(_text){
    setFont(path,size, renderer);
}

Text::~Text(){
    free();
}

bool Text::setFont(const char *path, int size, SDL_Renderer *renderer){
    bool success = this->font.loadFont(path,size);
    if(success && renderer != NULL && this->text != NULL){
        success = setText(this->text,renderer);
    }
    return success;
}

bool Text::setText(const char *_text,SDL_Renderer *renderer){
    bool success = true;
    success = font.font != NULL;

    //remove existing texture
    free();

    //Render text as surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(this->font.font,_text,this->color);
    if(textSurface == NULL){
        printf("Unable to render text. SDL_ttf Error: %s\n",TTF_GetError());
        success = false;
    }
    else{
        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if(newTexture == NULL){
            printf("Unable to create texture from rendered text. SDL Error: %s\n",SDL_GetError());
            success = false;
        }
        else{
            setTexture(newTexture);
            setSourceRect(0,0,textSurface->w,textSurface->h);
        }

        SDL_FreeSurface(textSurface);
    }

    return success;
}


