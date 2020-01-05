#include"TE_main.h"

TornadoEngine::TornadoEngine(const char *title, int width, int height){
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    this->glContext = SDL_GL_CreateContext(this->window);
   
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0,0,width, height);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

TornadoEngine::~TornadoEngine(){
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

Timer::Timer(){
    this->startTicks = SDL_GetTicks();
}

double Timer::restart(){
    double t = (double)(SDL_GetTicks() - this->startTicks)/1000.0f;
    this->startTicks = SDL_GetTicks();
    return t;
}