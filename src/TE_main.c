#include"TE_main.h"

#include<stdio.h>

uint8_t TE_init(TornadoEngine *engine, const char *title, int width, int height){
    uint8_t success = 1;
    //Create window
    engine->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if( engine->window == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        success = -1;
    }
    else
    {
        engine->width = width;
        engine->height = height;
        //Create renderer for window
        engine->renderer = SDL_CreateRenderer( engine->window, -1, SDL_RENDERER_ACCELERATED );
        if( engine->renderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = -1;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( engine->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

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

void TE_close(TornadoEngine *engine){
    //Destroy window    
    SDL_DestroyRenderer( engine->renderer );
    SDL_DestroyWindow( engine->window );
    engine->window = NULL;
    engine->renderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void startTimer(Timer *timer){
    timer->startTicks = SDL_GetTicks();
    timer->state = start;
}

Uint32 stopTimer(Timer *timer){
    Uint32 time = SDL_GetTicks() - timer->startTicks;
    timer->startTicks = 0;
    timer->state = stop;
    return time;
}

Uint32 restartTimer(Timer *timer){
    Uint32 time = SDL_GetTicks() - timer->startTicks;
    timer->startTicks = SDL_GetTicks();
    timer->state = start;
    return time;
}