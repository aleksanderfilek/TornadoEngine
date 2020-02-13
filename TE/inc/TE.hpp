#ifndef TE_HPP_
#define TE_HPP_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<GL/glew.h>
#include<SDL2/SDL_opengl.h>

#include"TE_graphics.hpp"
#include"TE_math.hpp"
#include"TE_ecs.hpp"
#include"TE_audio.hpp"
#include"TE_debug.hpp"
#include"TE_net.hpp"
#include"TE_physics.hpp"
#include"TE_components.hpp"
#include"TE_animation.hpp"
#include"TE_input.hpp"

class TornadoEngine{
private:
    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_Event event;
public:
    TornadoEngine();
    ~TornadoEngine();

    void CreateGame(const char *title, int width, int height);
    void Start();

    SDL_Window *GetWindow(){return window;};

    virtual void OnStart() = 0;
    virtual bool OnUpdate(float elapsedTime) = 0;
    virtual void OnDraw() = 0;
    #ifdef DEBUG
    virtual void OnDebug() = 0;
    #endif
    virtual void OnExit() = 0;
};

class State{
public:
    State();
    virtual ~State() = 0;
    virtual void Draw() = 0;
    virtual int Update();
};

class Timer{
private:
    Uint32 startTicks;
public:
    Timer();
    ~Timer(){};
    float restart();

    float timeInMilliseconds(){
        return (float)(startTicks - SDL_GetTicks())/1000.0f;
        };
};
#endif