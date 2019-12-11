#include"TE_graphics.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern SDL_Renderer *renderer;

Texture *textureSystem;
int textureSystemLength = 0;
int textureSystemCapacity = 0;

static Texture *insertTexture(const Texture *texture){
    if(textureSystemLength >= textureSystemCapacity){
        textureSystemCapacity += 5;
        textureSystem = (Texture *)realloc(textureSystem,textureSystemCapacity * sizeof(Texture));
    }

    int i;
    for(i = textureSystemLength - 1; (i >= 0 && textureSystem->layer > texture->layer); i--){
        textureSystem[i+1] = textureSystem[i];
    }
    textureSystem[i] = *texture;

    return &textureSystem[i];
}

void Tex_init(){
    textureSystemCapacity = 10;
    textureSystem = (Texture *)realloc(textureSystem,textureSystemCapacity * sizeof(Texture));
}

Texture *Tex_Create(const char *path, int posX, int posY, uint8_t layer){
    Texture texture;
    texture.texture = Tex_load(path);
    texture.layer = layer;
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture,1.0f,1.0f);

    return insertTexture(&texture);
}

Texture *Tex_CreateFromSdlTexture(SDL_Texture *sdlTexture,int posX, int posY, uint8_t layer){
    Texture texture;
    Tex_setTexture(&texture, sdlTexture);
    texture.layer = layer;
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture,1.0f,1.0f);

    return insertTexture(&texture);
}

void Tex_setTexture(Texture *texture, SDL_Texture *sdlTexture){
    if(texture->texture != NULL){
        SDL_DestroyTexture(texture->texture);
    }
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
    texture->destinationRect.x = scaleX * textureSystem->sourceRect.w;
    texture->destinationRect.y = scaleY * textureSystem->sourceRect.h;
}

void Tex_draw(){
    int i;
    Texture texture;
    for(i = 0; i < textureSystemLength; i++){
        texture = textureSystem[i];
        SDL_RenderCopy(renderer,texture.texture,&texture.sourceRect,&texture.destinationRect);
    }
}

void Tex_free(){
    int i;
    for(i = textureSystemLength-1; i>=0;i--){
        SDL_DestroyTexture(textureSystem[i].texture);
    }
    free(textureSystem);
}
/*
Texture **textureSystem;
int textureElementNumber = 0;
int layerNumber = 0;

Texture *Ecs_Tex_add(Texture *texture){
    textureElementNumber++;
    int layer = texture->layer;
    textureSystem[layer] = (Texture *)realloc(textureSystem,textureElementNumber*sizeof(Texture));
    textureSystem[layer][textureElementNumber] = *texture;
    return &texture[textureElementNumber];
}

void Ecs_Tex_draw(){
    int j;
    for(j = 0; j < layerNumber; j++){
        int i;
        for(i = 0; i < textureElementNumber; i++){
            Texture tex = textureSystem[j][i];
            SDL_RenderCopy(renderer,tex.texture,&tex.sourceRect,&tex.destinationRect);
        }
    }
}

void Ecs_Tex_free(){
    int j;
    for(j=0; j < layerNumber; j++){
        int i;
        for(i = 0; i < textureElementNumber; i++){
            Tex_free(&textureSystem[j][i]);
        }
        free(textureSystem[j]);
    }
    textureElementNumber = 0;
}

Texture *Tex_init(const char *texturePath, int posX, int posY, float scaleX, float scaleY, int layer){
    Texture texture;
    if(texturePath != NULL){
        SDL_Texture *tex = Tex_load(texturePath);
        Tex_setTexture(&texture,tex);
    }
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture,scaleX,scaleY);
    texture.layer = layer;
    return NULL;//Ecs_Tex_Add(&texture);
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
    Text *textStruct = malloc(sizeof(Text));
    Texture texture;
    textStruct->font = font;
    Text_setText(textStruct,text);
    Tex_setPosition(&texture,posX,posY);
    Tex_setScale(&texture,scaleX,scaleY);
    textStruct->texture = NULL;//Ecs_Tex_Add(&texture); 
    return textStruct;
}

TTF_Font *Text_loadFont(const char *path, int size){
    return TTF_OpenFont(path, size);
}

void Text_setFont(Text *textStruct, TTF_Font *font){
    Text_setText(textStruct,textStruct->text);
}

void Text_setText(Text *textStruct, const char *newText){
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

void Layer_init(int layerCount){
    textureSystem = (Texture **)malloc(layerCount * sizeof(Texture *));
}

void Layer_free(){
    Ecs_Tex_free();
    free(textureSystem);
    layerNumber = 0;
}
*/