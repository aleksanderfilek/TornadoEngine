#include"TE_ecs.h"

void Ecs_Tex_draw(){
    int i;
    for(i = 0; i < textureElementNumber; i++){
        Texture tex = textureSystem[i];
        SDL_RenderCopy(renderer,tex.texture,&tex.sourceRect,&tex.destinationRect);
    }
}

void Ecs_Btn_update(int mousePosX, int mousePosY , Button *buttonStructs, int number){
    int i;
    Button button;
    for(i = 0; i < number; i++){
        button = buttonStructs[i];
        if(button.texture->destinationRect.x <= mousePosX && 
        button.texture->destinationRect.x + button.texture->destinationRect.w >= mousePosX &&
        button.texture->destinationRect.y <= mousePosY && 
        button.texture->destinationRect.y + button.texture->destinationRect.h >= mousePosY){
            if(!(button.state | hovered)){
                button.state = hovered;
                if(button.hover)button.hover();
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                button.state = clicked;
                if(button.click)button.click();
            }
        }
        else if(button.state | hovered){
            button.state = none;
            if(button.unhover)button.unhover();
        }
    }
}