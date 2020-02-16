#include"TE.hpp"

TornadoEngine::TornadoEngine(){

}

void TornadoEngine::CreateGame(const char *title, int width, int height){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS);

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    this->glContext = SDL_GL_CreateContext(this->window);
   
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0,0,width, height);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    SDL_WarpMouseInWindow(this->window,width/2,height/2);
}

TornadoEngine::~TornadoEngine(){
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void TornadoEngine::Start(){
    OnStart();

    Timer timer;
    float elapsedTime = 0;

    bool quit = false;
    while (!quit)
    {
        while(SDL_PollEvent(&this->event)){
            if(this->event.type == SDL_QUIT){
                quit = true;
            }
        }
        OnUpdate(elapsedTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        OnDraw();
        #ifdef DEBUG
        OnDebug();
        #endif
        SDL_GL_SwapWindow(this->window);

        elapsedTime = timer.restart();
    }

    OnExit();
}

Timer::Timer(){
    this->startTicks = SDL_GetTicks();
}

float Timer::restart(){
    float t = (float)(SDL_GetTicks() - this->startTicks)/1000.0f;
    this->startTicks = SDL_GetTicks();
    return t;
}