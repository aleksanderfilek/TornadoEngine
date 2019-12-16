#include"TE_main.h"

#include<stdio.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

int screenWidth,screenHeight;

State currentState;
State nextState;

uint8_t TE_init(const char *title, int Width, int Height){
    uint8_t success = 1;
    //Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    if( window == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        success = -1;
    }
    else
    {
        screenWidth = Width;
        screenHeight = Height;
        //Create renderer for window
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = -1;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = -1;
            }
            //Initialize SDL_ttf
            if( TTF_Init() == -1 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                success = -1;
            }
        }
    }
    return success;
}

void TE_close(){
    //Destroy window    
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void startTimer(Timer *timer){
    timer->startTicks = SDL_GetTicks();
    timer->state = 1;
}

Uint32 stopTimer(Timer *timer){
    Uint32 time = SDL_GetTicks() - timer->startTicks;
    timer->startTicks = 0;
    timer->state = 0;
    return time;
}

Uint32 restartTimer(Timer *timer){
    Uint32 time = SDL_GetTicks() - timer->startTicks;
    timer->startTicks = SDL_GetTicks();
    timer->state = 1;
    return time;
}