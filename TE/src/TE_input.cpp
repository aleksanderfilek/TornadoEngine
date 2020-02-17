#include"TE_input.hpp"

#include<stdio.h>

int keyboardStateNumber = 0;
const uint8_t *currentKeyboardState = NULL;
uint8_t *previousKeyboardState = NULL;

int32_t currentMouseState, previousMouseState;
int mousePosX, mousePosY;


bool keyPressed(KeyCode keyCode){
    return currentKeyboardState[keyCode] && previousKeyboardState[keyCode];
}

bool keyDown(KeyCode keyCode){
    return currentKeyboardState[keyCode] && !previousKeyboardState[keyCode];
}

bool keyUp(KeyCode keyCode){
    return !currentKeyboardState[keyCode] && previousKeyboardState[keyCode];
}

bool mouseButtonPressed(MouseButton mouseButton){
    return currentMouseState&SDL_BUTTON(mouseButton) && previousMouseState&SDL_BUTTON(mouseButton);
}

bool mouseButtonDown(MouseButton mouseButton){
    return currentMouseState&SDL_BUTTON(mouseButton) && !previousMouseState&SDL_BUTTON(mouseButton);
}

bool mouseButtonUp(MouseButton mouseButton){
    return !currentMouseState&SDL_BUTTON(mouseButton) && previousMouseState&SDL_BUTTON(mouseButton);
}

inline void getMousePosition(int *x,int *y){
    /*not sure how it work if x or y equal NULL*/
    *x = mousePosX;
    *y = mousePosY;
}

void input_Start(){
    currentKeyboardState = SDL_GetKeyboardState(&keyboardStateNumber);
    previousKeyboardState = (uint8_t *)calloc(keyboardStateNumber, sizeof(uint8_t));
}

void input_Update(){
    //update mouse
    previousMouseState = currentMouseState;
    currentMouseState = SDL_GetMouseState(&mousePosX, &mousePosY);
    //printf("prev = %d   cur = %d\n",previousMouseState,currentMouseState);
    //update keyboard
    SDL_memcpy(previousKeyboardState,currentKeyboardState,keyboardStateNumber * sizeof(uint8_t));
}

void input_Close(){
    //currentKeyboardState don't need to bee deleted. Probably SDL do this. If try deleting, it gives error: free(): invalid pointer

    delete previousKeyboardState;
}