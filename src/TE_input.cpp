#include"TE_input.h"

#include<stdio.h>
#include<stdlib.h>


bool Input::keyPressed(KeyCode keyCode){
    return this->currentKeyboardState[static_cast<unsigned int>(keyCode)] && this->previousKeyboardState[static_cast<unsigned int>(keyCode)];
}

bool Input::keyDown(KeyCode keyCode){
    return this->currentKeyboardState[static_cast<unsigned int>(keyCode)] && !this->previousKeyboardState[static_cast<unsigned int>(keyCode)];
}

bool Input::keyUp(KeyCode keyCode){
    return !this->currentKeyboardState[static_cast<unsigned int>(keyCode)] && this->previousKeyboardState[static_cast<unsigned int>(keyCode)];
}

bool Input::mouseButtonPressed(MouseButton mouseButton){
    return this->currentMouseState&SDL_BUTTON(static_cast<unsigned int>(mouseButton)) && this->previousMouseState&SDL_BUTTON(static_cast<unsigned int>(mouseButton));
}

bool Input::mouseButtonDown(MouseButton mouseButton){
    return (this->currentMouseState&SDL_BUTTON(static_cast<unsigned int>(mouseButton))) && !(this->previousMouseState&SDL_BUTTON(static_cast<unsigned int>(mouseButton)));
}

bool Input::mouseButtonUp(MouseButton mouseButton){
    return !(this->currentMouseState&SDL_BUTTON(static_cast<unsigned int>(mouseButton))) && (this->previousMouseState&SDL_BUTTON(static_cast<unsigned int>(mouseButton)));
}

void Input::getMousePosition(int *x,int *y){
    /*not sure how it work if x or y equal NULL*/
    *x = this->mousePosX;
    *y = this->mousePosY;
}

Input::Input(){
    this->currentKeyboardState = SDL_GetKeyboardState(&this->keyboardStateNumber);
    this->previousKeyboardState = (uint8_t *)calloc(this->keyboardStateNumber, sizeof(uint8_t));
}

void Input::Update(){
    //update mouse
    this->previousMouseState = this->currentMouseState;
    this->currentMouseState = SDL_GetMouseState(&this->mousePosX, &this->mousePosY);
    //update keyboard
    SDL_memcpy(this->previousKeyboardState,this->currentKeyboardState,this->keyboardStateNumber * sizeof(uint8_t));
}

Input::~Input(){
    //currentKeyboardState don't need to bee deleted. Probably SDL do this. If try deleting, it gives error: free(): invalid pointer

    delete[] previousKeyboardState;
}