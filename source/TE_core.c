#include"TE_core.h"

#include<stdio.h>
#include<stdlib.h>

TE_Game *game = NULL;

static void check_state();
static void close_state();

int TE_init_game(const char *title, int width, int height, int flags)
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO |  SDL_INIT_TIMER) < 0){
        printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
        return -1;
    }

    game = (TE_Game*)malloc(sizeof(TE_Game));
    game->current_state = NULL;
    game->next_state = NULL;

    // Create window object
    game->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Check if window object was correctly created
    if(game->window == NULL){
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        return -1;
    }

    // Set window info data
    game->window_info.size.x = width;
    game->window_info.size.y = height;
    game->window_info.full_screen = -1;

    // Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // Create OpenGL context
    game->gl_context = SDL_GL_CreateContext(game->window);

    glewExperimental = GL_TRUE;
    // Initialize glew
    glewInit();
    // Create viewport
    glViewport(0,0,width, height);
    // Set background color
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    // Enable depth in rendering
    glEnable(GL_DEPTH_TEST);
    // Enable blending
    glEnable(GL_BLEND);

    // Start input system
    TE_start_input();

    return 0;
}

void TE_start_game(TE_State *start_state)
{
    // Set next state, then i will be transfered to current state
    TE_set_next_state(start_state);

    uint32_t timer;
    double elapsed_time = 0.0f;

    // Quit is switch, when equel 1, loop end
    int quit = 0;
    while (!quit)
    {
        // Get actual timer
        timer = SDL_GetTicks();
        // Update current state
        check_state();

        // Event loop
        while(SDL_PollEvent(&game->event) != 0){
            switch (game->event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_WINDOWEVENT:
                if(game->event.window.event == SDL_WINDOWEVENT_RESIZED){
                }
                break;
            }
        }
        TE_clear();
        // Do state update function
        game->current_state->update(elapsed_time);
        // Update inputs
        TE_update_input();
        // Clear screen

        // Do state draw function
        game->current_state->draw();
        // Render
        TE_render();
        // Calculate elapsed time
        elapsed_time = (double)(SDL_GetTicks() - timer )/1000.0f;
    }
}

void TE_close_game()
{    
    close_state();

    // Close input system
    TE_close_input();

    free(game);
    // Delet OpenGL context
    SDL_GL_DeleteContext(game->gl_context);
    
    // Destroy window object
    SDL_DestroyWindow(game->window);
    game->window = NULL;

    // Quit SDL
    SDL_Quit();
}

TE_State* TE_create_state(void (*start)(), void (*update)(double), void (*draw)(), void (*exit)()){
    TE_State* state = (TE_State*)malloc(sizeof(TE_State));
    if(state == NULL){
        printf("Could not create state\n");
        return NULL;
    }

    state->start = start;
    state->update = update;
    state->draw = draw;
    state->exit = exit;

    return state;
}

void TE_set_next_state(TE_State *next_state)
{
    // Set next state
    game->next_state = next_state;
}

void check_state()
{
    // Check if next state exist
    if(game->next_state != NULL){

        // Check if current state exist
        if(game->current_state != NULL){

            game->current_state->exit();
            // Free current state memory
            free(game->current_state);
        }

        // Set next state to current state
        game->current_state = game->next_state;
        // Forget next state. It is not free, because now current state point to this memory area
        game->next_state = NULL;
        // Run start function of current state
        game->current_state->start();
    }
}

void close_state()
{

    // Check if current state exist
    if(game->current_state != NULL){

        game->current_state->exit();

        // Free current state memory
        free(game->current_state);
        game->current_state = NULL;
    }

    // Check if next state exist
    if(game->next_state != NULL){

        // Free current state memory
        free(game->next_state);
        game->next_state = NULL;
    }
}
