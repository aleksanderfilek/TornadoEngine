#include"Mouse.h"

Mouse::Mouse(const char* cursorPath, SDL_Renderer *renderer){
    this->texture.loadTexture(cursorPath, renderer);
}

Mouse::~Mouse(){
    this->texture.free();
}

SDL_Point Mouse::getMousePosition(){
    SDL_Point position;
    SDL_GetMouseState(&position.x, &position.y);
    return position;
}

void Mouse::render(SDL_Renderer *renderer){
    SDL_Point position = getMousePosition();
    this->texture.render(renderer);
}

void Mouse::update(const SDL_Event *e){
    this->clicked = e->type == SDL_MOUSEBUTTONDOWN;
    if(this->clicked == true){
        //this->texture.setPosition(16,0);
    }
}