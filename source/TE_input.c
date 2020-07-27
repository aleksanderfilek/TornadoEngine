#include"TE_input.h"

int keyboard_state_number = 0;
const uint8_t *current_keyboard_state = NULL;
uint8_t *previous_keyboard_state = NULL;

int32_t current_mouse_state, previous_mouse_state;
int mouse_position_X = 0, mouse_position_Y = 0;

void TE_start_input(){
    current_keyboard_state = SDL_GetKeyboardState(&keyboard_state_number);
    previous_keyboard_state = (uint8_t *)calloc(keyboard_state_number, sizeof(uint8_t));
}

void TE_update_input(){
    //update mouse
    previous_mouse_state = current_mouse_state;
    current_mouse_state = SDL_GetMouseState(&mouse_position_X, &mouse_position_Y);
    //update keyboard
    SDL_memcpy(previous_keyboard_state, current_keyboard_state, keyboard_state_number * sizeof(uint8_t));
}

void TE_close_input(){

    //currentKeyboardState don't need to bee deleted. Probably SDL do this. If try deleting, it gives error: free(): invalid pointer
    free(previous_keyboard_state);

}

int TE_key_pressed(int scancode){
    return current_keyboard_state[scancode] && previous_keyboard_state[scancode];
}

int TE_key_down(int scancode){
    return current_keyboard_state[scancode] && !previous_keyboard_state[scancode];
}

int TE_key_up(int scancode){
    return !current_keyboard_state[scancode] && previous_keyboard_state[scancode];
}

int TE_mouse_button_pressed(int mouse_button){
    return current_mouse_state&SDL_BUTTON(mouse_button) && previous_mouse_state&SDL_BUTTON(mouse_button);
}

int TE_mouse_button_down(int mouse_button){
    return current_mouse_state&SDL_BUTTON(mouse_button) && !previous_mouse_state&SDL_BUTTON(mouse_button);
}

int TE_mouse_button_up(int mouse_button){
    return !current_mouse_state&SDL_BUTTON(mouse_button) && previous_mouse_state&SDL_BUTTON(mouse_button);
}

void TE_get_mouse_position(int *x,int *y){
    if(x != NULL) *x = mouse_position_X;
    if(y != NULL) *y = mouse_position_Y;
}

void TE_set_mouse_position(int x, int y){
    extern TE_Game* game;
    SDL_WarpMouseInWindow(game->window, x, y);
    mouse_position_X = x;
    mouse_position_Y = y;
}