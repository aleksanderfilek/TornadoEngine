#include"TE_input.hpp"

using namespace input;

const uint8_t *keyboardState = NULL;

bool isKeyPressed(KeyCode keyCode){
    return keyboardState[keyCode];
}

bool isKeyDown(KeyCode keyCode){

}

bool isKeyUp(KeyCode keyCode){

}

bool mouseButtonPressed(MouseButton mouseButton){
    return SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(mouseButton);
}

bool mouseDown(MouseButton mouseButton){

}

bool mouseButtonUp(MouseButton mouseButton){

}

inline void getMousePosition(int *x,int *y){
    SDL_GetMouseState(x,y);
}
