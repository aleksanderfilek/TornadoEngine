#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Texture{
private:
    SDL_Texture *texture;
    
    SDL_Rect sourceRect = {0,0,0,0};
    SDL_Rect destinationRect = {0,0,0,0};
    SDL_Point scale = {1,1};
public:
    //constructor
    Texture();
    //destructor
    ~Texture();

    bool setTexture(const char* path, SDL_Renderer *renderer);
    void setTexture(SDL_Texture *newTexture){texture = newTexture;};
    //load texture from file
    static SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer);
    //free memory of texture
    void free();

    //rendering functions
    void render(SDL_Renderer *renderer);
    void renderEx(SDL_Renderer *renderer,double angle,SDL_Point* center,SDL_RendererFlip flip = SDL_FLIP_NONE );

    void setPosition(const int x, const int y);
    void setPosition(const SDL_Point position);
    void move(const float x, const float y);

    void setScale(const int x, const int y);
    void setScale(const SDL_Point _scale);

    void setSourceRect(int x, int y, int w, int h){sourceRect={x,y,w,h};};
    void setSourceRect(SDL_Rect srcRect){sourceRect = srcRect;};

    //Properties
    SDL_Rect getSourceRect(){return sourceRect;};
    SDL_Rect getDestinationRect(){return destinationRect;};
    SDL_Point getScale(){return scale;};
    SDL_Texture *getTexture(){return texture;};
};

#endif