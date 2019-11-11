#include"Button.h"

Button::Button(){

}

Button::~Button(){
    delete this->background;
    delete this->background;
}

void Button::draw(SDL_Renderer *renderer){
    this->background->render(renderer);
    this->text->render(renderer);
}

void Button::update(Mouse *mouse){
    
    if(hover(&mouse->getMousePosition())){
        this->isHovered = true;
        if(mouse->getMouseDown()){
            this->isClicked = true;
        }
        else{
            this->isClicked = false;
        }
    }
    else {
        this->isHovered = false;
    }
}

bool Button::hover(SDL_Point *point){
    SDL_Rect *dstRect = &this->background->getDestinationRect();
    if(point->x >= dstRect->x && point->x <= dstRect->x + dstRect->w &&
        point->y >= dstRect->y && point->y <= dstRect->y + dstRect->h){
        return true;
    }

    return false;
}

