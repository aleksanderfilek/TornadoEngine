#include"TE.h"
#include"TE_graphics.h"

class Game:public TornadoEngine{
private:
    shader Shader;
    Texture tex;
    vector2 position = {120.0f, 120.0f};
    vector2 scale = {2.0f,2.0f};
    vector4 srcRect = {0.0f,0.0f,1.0f,1.0f};
protected:
    virtual void OnStart(){
        Graphics_Init();
        tex = Tex_Load("wall.jpg");
        Shader = Shader_Load("vertex.vs","fragment.frag");
    }

    virtual void OnUpdate(double elapsedTime){
        glUseProgram(Shader);
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            srcRect.x += (float)(0.5f * elapsedTime);
        }
        else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
            srcRect.x -= (float)(0.5f * elapsedTime);
        }

        if( currentKeyStates[ SDL_SCANCODE_UP ] )
        {
            srcRect.y += (float)(0.5f * elapsedTime);
        }
        else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ){
            srcRect.y -= (float)(0.5f * elapsedTime);
        }
    }

    virtual void OnDraw(){
        Tex_DrawEx(&tex,Shader,position,scale,srcRect);
    }

    virtual void OnExit(){
        Graphics_Close();
    }
};

int main(int argc, char **argv){
    Game game;
    game.CreateGame("Title",640,480);
    game.Start();
    return 0;
}