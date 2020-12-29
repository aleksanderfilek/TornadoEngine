#include"TE_graphics.h"

extern TE_Game *game;

inline void TE_clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void TE_set_background_color(uint8_t R, uint8_t G, uint8_t B)
{
    glClearColor((float)R/255,
            (float)G/255,
            (float)B/255,
            1.0f);
}

inline void TE_render()
{
    SDL_GL_SwapWindow(game->window);
}