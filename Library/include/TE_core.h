#ifndef TECORE_H_
#define TECORE_H_
#define TE_OPENGL

#include<stdio.h>

#include"TE_math.h"
#include"TE_graphics.h"
#include"TE_ui.h"
#include"TE_input.h"

struct WindowInfo{
    vector2ui size;
    bool fullScreen;
};

class State{
public:
    State(){};
    virtual ~State(){};
    virtual void OnStart() = 0;
    virtual void OnUpdate(float elapsedTime) = 0;
    virtual void OnDraw() = 0;
#ifdef TE_DEBUG
    virtual void OnDebug() = 0;
#endif   
};

class TornadoEngine{
private:
    WindowInfo windowInfo;

    SDL_Window *window;
//#ifndef TE_OPENGL
    SDL_Renderer *renderer;
//#else
    SDL_GLContext glContext;
//#endif
    SDL_Event event;

    State *gameState = NULL;
    State *nextState = NULL;

    void CheckState();
    void CloseState();
public:
    TornadoEngine(){}
    ~TornadoEngine();

    bool Init(const char *title, int width, int height, uint32_t flags = SDL_WINDOW_SHOWN);
    void Start(State *startState);

    void SetNextState(State *nextState);

//#ifndef TE_OPENGL
    inline SDL_Renderer *GetRenderer(){ return this->renderer; }
//#endif
     SDL_Window *GetWindow(){ return this->window; }
    inline SDL_Event *GetEvent(){ return &this->event; }
};

#endif