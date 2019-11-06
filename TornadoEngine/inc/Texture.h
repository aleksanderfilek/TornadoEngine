#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Texture{
private:
    SDL_Texture *texture;
    
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
public:
    //constructor
    Texture();
    //destructor
    ~Texture();

    bool setTexture(const char* path, SDL_Renderer *renderer);
    //load texture from file
    static SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer);
    //free memory of texture
    void free();

    //rendering functions
    void render(SDL_Renderer *renderer);
    void render(double angle, SDL_Point* center, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void setPosition(int x, int y);
    void setPosition(SDL_Point position);
    void move(int x, int y);
    void move(SDL_Point offset);

    void setSourceRect(int x, int y, int w, int h){sourceRect={x,y,w,h};};
    void setSourceRect(SDL_Rect srcRect){sourceRect = srcRect;};

    //Properties
    SDL_Rect getSourceRect(){return sourceRect;};
    SDL_Rect getDestinationRect(){return destinationRect;};
};

#endif