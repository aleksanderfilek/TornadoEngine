#include"TE_ui.h"

void Btn_update(SDL_Event *e, Button *button){
    int mousePosX, mousePosY;
    SDL_GetMouseState(&mousePosX,&mousePosY);
    if(button->texture->destinationRect.x <= mousePosX && 
        button->texture->destinationRect.x + button->texture->destinationRect.w >= mousePosX &&
        button->texture->destinationRect.y <= mousePosY && 
        button->texture->destinationRect.y + button->texture->destinationRect.h >= mousePosY){
            if(!(button->state | hovered)){
                button->state = hovered;
                if(button->hover)button->hover();
            }
            if(e->type == SDL_MOUSEBUTTONDOWN){
                button->state = clicked;
                if(button->click)button->click();
            }
        }
        else if(button->state | hovered){
            button->state = none;
            if(button->unhover)button->unhover();
        }
}