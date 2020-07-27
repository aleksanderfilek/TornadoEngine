#ifndef TEINPUT_H_
#define TEINPUT_H_

#include"TE.h"

#include<SDL2/SDL.h>

#include<stdint.h>

enum MouseButton
{
    MouseButton_Left = 1,
    MouseButton_Middle = 2,
    MouseButton_Right = 3
};

void TE_start_input();
void TE_update_input();
void TE_close_input();

int TE_key_pressed(int scancode);
int TE_key_down(int scancode);
int TE_key_up(int scancode);

int TE_mouse_button_pressed(int mouse_button);
int TE_mouse_button_down(int mouse_button);
int TE_mouse_button_up(int mouse_button);

void TE_get_mouse_position(int *x, int *y);
void TE_set_mouse_position(int x, int y);

#endif