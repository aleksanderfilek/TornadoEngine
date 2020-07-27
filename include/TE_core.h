#ifndef TECORE_H_
#define TECORE_H_

#include"TE.h"
#include"TE_math.h"

#include<SDL2/SDL.h>

#include<GL/glew.h>

#include<stdint.h>

typedef struct {
    void (*start)();
    void (*update)(double elapsed_time);
    void (*draw)();
    void (*exit)();
}TE_State;

TE_State* TE_create_state(void (*start)(), void (*update)(double), void (*draw)(), void (*exit)());
void TE_set_next_state(TE_State *next_state);

typedef struct {
    float2 size;
    uint8_t full_screen;
}TE_Window_Info;

typedef struct TE_Game{
    SDL_Window *window;
    SDL_GLContext gl_context;
    SDL_Event event;

    TE_Window_Info window_info;

    TE_State *current_state;
    TE_State *next_state;
}TE_Game;

int TE_init_game(const char *title, int width, int height, int flags);
void TE_start_game(TE_State *start_state);
void TE_close_game();


#endif