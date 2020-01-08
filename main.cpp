#include"TE.h"
#include"TE_graphics.h"

class TornadoEngine{
protected:
    virtual void OnStart(){

    }

    virtual void OnUpdate(){
        
    }
};

int main(int argc, char **argv){
    TornadoEngine engine("Title",640, 480);
    Graphics_Init();

    Texture tex = Tex_Load("wall.jpg");
    vector2 position = {120.0f, 120.0f};
    vector2 scale = {2.0f,2.0f};
    vector4 srcRect = {0.0f,0.0f,1.0f,1.0f};

    Timer timer;
    double deltaTime = 0.0f;

    shader Shader = Shader_Load("vertex.vs","fragment.frag");

    glUseProgram(Shader);

    SDL_Event event;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            srcRect.x += (float)(0.5f * deltaTime);
        }
        else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
            srcRect.x -= (float)(0.5f * deltaTime);
        }

        if( currentKeyStates[ SDL_SCANCODE_UP ] )
        {
            srcRect.y += (float)(0.5f * deltaTime);
        }
        else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ){
            srcRect.y -= (float)(0.5f * deltaTime);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        Tex_DrawEx(&tex,Shader,position,scale,srcRect);

        SDL_GL_SwapWindow(engine.GetWindow());

        deltaTime = timer.restart();
    }


    Graphics_Close();
    return 0;
}