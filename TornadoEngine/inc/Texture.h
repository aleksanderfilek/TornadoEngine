#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Texture{
private:
    SDL_Texture *texture;
    
    SDL_Rect sourceRect;
    SDL_Point position;
    SDL_Point scale = {1,1};
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
    void render(SDL_Renderer *renderer,const double angle,const SDL_Point* center,const SDL_RendererFlip flip = SDL_FLIP_NONE );

    void setPosition(const int x, const int y) {position = {x,y};};
    void setPosition(const SDL_Point _position){position = _position;};
    void move(const int x, const int y){position = {position.x + x, position.y + y}; };
    void move(const SDL_Point offset){position = {position.x + offset.x, position.y + offset.y};};

    void setScale(const int x, const int y) { scale = {x,y};};
    void setScale(const SDL_Point _scale){scale = _scale;};

    void setSourceRect(int x, int y, int w, int h){sourceRect={x,y,w,h};};
    void setSourceRect(SDL_Rect srcRect){sourceRect = srcRect;};

    //Properties
    SDL_Rect getSourceRect(){return sourceRect;};
    SDL_Rect getDestinationRect(){return {position.x, position.y,scale.x * sourceRect.w,scale.y * sourceRect.h};};
    SDL_Point getScale(){return scale;};
};

#endif