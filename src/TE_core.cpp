#include"TE_core.h"

TornadoEngine engine;
Input *inputManager;

bool TornadoEngine::Init(const char *title, int width, int height, uint32_t flags){
    if(SDL_Init(SDL_INIT_VIDEO |  SDL_INIT_TIMER) < 0){
        printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
        return true;
    }
    else{
        #ifdef TE_OPENGL
            flags |= SDL_WINDOW_OPENGL;
        #endif

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
        if(window == NULL){
            printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
            return true;
        }
        else{
            windowInfo.size.x = width;
            windowInfo.size.y = height;
            windowInfo.fullScreen = false;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                                SDL_GL_CONTEXT_PROFILE_CORE);

            this->glContext = SDL_GL_CreateContext(this->window);
        
            glewExperimental = GL_TRUE;
            glewInit();

            glViewport(0,0,width, height);
            glClearColor(1.0f,1.0f,1.0f,1.0f);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&imgFlags)){
                printf("SDL_image could not initialize! SDL_image Error: %s\n",IMG_GetError());
                return true;
            }
            else{
                if(TTF_Init() == -1){
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",TTF_GetError());
                    return true;
                }
            }

            inputManager = new Input();
        }
    }
    return true;
}


void TornadoEngine::Start(State *startState){
    this->SetNextState(startState);

    uint32_t timer;
    float elapsedTime = 0.0f;

    bool quit = false;
    while (!quit)
    {
        timer = SDL_GetTicks();
        this->CheckState();

        while(SDL_PollEvent(&this->event) != 0){
            switch (this->event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                if(this->event.window.event == SDL_WINDOWEVENT_RESIZED){
                }
                break;
            }
        }

        gameState->OnUpdate(elapsedTime);
        inputManager->Update();
        //ui_update();
        
        Clear();
        gameState->OnDraw();

    #ifdef TE_DEBUG
        gameState->OnDebug();
    #endif

        Render();

        elapsedTime = (float)(SDL_GetTicks() - timer )/1000.0f;
    }
}

TornadoEngine::~TornadoEngine(){
    this->CloseState();
    delete inputManager;
    // /ui_close();
    
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void TornadoEngine::SetNextState(State *_nextState){
    nextState = _nextState;
}

void TornadoEngine::CheckState(){
    if(nextState != NULL){
        if(gameState != NULL){
            delete gameState;
        }
        gameState = nextState;
        nextState = NULL;
        gameState->OnStart();
    }
}

void TornadoEngine::CloseState(){
    if(gameState != NULL){
        delete gameState;
        gameState = NULL;
    }

    if(nextState != NULL){
        delete nextState;
        nextState = NULL;
    }
}