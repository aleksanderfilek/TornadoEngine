#ifndef TE_H_
#define TE_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<GL/glew.h>
#include<SDL2/SDL_opengl.h>

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
    virtual void OnUpdate(double elapsedTime) = 0;
    virtual void OnDraw() = 0;
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
    double restart();

    double timeInMilliseconds(){
        return (double)(startTicks - SDL_GetTicks())/1000.0f;
        };
};
#endif