#include"TE.h"
#include"TE_graphics.h"

class Game:public TornadoEngine{
private:
    Graphics graphics;
    Mesh mesh;
    Shader program;
    mat4x4 model;
    float angle;
    GLuint modelLoc;

    mat4x4 lookAt;
    vector3f eye = {0.0f, 0.0f, 0.0f};
    vector3f target = {0.0f, 0.0f, 1.0f};
    vector3f up = {0.0f, 1.0f, 0.0f};

    GLuint lookLoc;
    float speed = 4.0f;

    float jumpForce = 5.0f;
    float velocityY = 0.0f;
    float gravity = 9.81f;

    Texture texture;
    Texture texture1;

    Texture currentTexture;

    vector2i mouse;
protected:
    virtual void OnStart(){
        texture = Tex_Load("wall.jpg");
        texture1 = Tex_Load("Floor.png");
        
        currentTexture = texture;

        program.Load("vertex.vs","fragment.frag");
        mesh.LoadObj("Floor.obj");

        glUseProgram(program.ID);
        modelLoc = glGetUniformLocation(program.ID,"model");
        GLuint projectionLoc = glGetUniformLocation(program.ID,"projection");

        mat4x4 projection;
        matrix_projection(projection,800,600,120.0f,0.1f,1000.0f);


        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,&projection[0].x);


        lookLoc = glGetUniformLocation(program.ID,"lookAt");

        // vector3f vertices[]{ 
        //     //FRONT
        //     {-1.0f, 1.0f, 1.0f},
        //     {1.0f, 1.0f, 1.0f},
        //     {-1.0f, -1.0f, 1.0f},

        //     {1.0f, 1.0f, 1.0f},
        //     {1.0f, -1.0f, 1.0f},
        //     {-1.0f, -1.0f, 1.0f},

        //     //BACK
        //     {-1.0f, 1.0f, -1.0f},
        //     {1.0f, 1.0f, -1.0f},
        //     {-1.0f, -1.0f, -1.0f},

        //     {1.0f, 1.0f, -1.0f},
        //     {1.0f, -1.0f, -1.0f},
        //     {-1.0f, -1.0f, -1.0f},

        //     //TOP
        //     {-1.0f, 1.0f, 1.0f},
        //     {1.0f, 1.0f, -1.0f},
        //     {1.0f, 1.0f, 1.0f},
        
        //     {-1.0f, 1.0f, 1.0f},
        //     {-1.0f, 1.0f, -1.0f},
        //     {1.0f, 1.0f, -1.0f},
        // };

        // vector2f uvs[]{
        //     {1.0f,0.0f},
        //     {1.0f,0.0f},
        //     {1.0f,0.0f},

        //     {0.0f,1.0f},
        //     {0.0f,1.0f},
        //     {0.0f,1.0f},

        //     {0.5f,0.0f},
        //     {0.5f,0.0f},
        //     {0.5f,0.0f},

        //     {0.0f,0.5f},
        //     {0.0f,0.5f},
        //     {0.0f,0.5f},

            
        //     {0.25f,0.25f},
        //     {0.25f,0.25f},
        //     {0.25f,0.25f},

        //     {0.5f,0.5f},
        //     {0.5f,0.5f},
        //     {0.5f,0.5f}
        // };

        // vector3ui indices[]{
        //     {0, 1, 2},
        //     {3, 4, 5},
        //     {6, 7, 8},
        //     {9, 10, 11},
        //     {12, 13, 14},
        //     {15, 16, 17}
        // };

        // mesh.Generate(vertices,18,uvs,18,indices,6);
  
    }

    virtual void OnUpdate(double elapsedTime){
        angle += (float)elapsedTime;
        matrix_identity(model);
        matrix_translate(model,{0.0f, -1.0f, 0.0f});

        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            eye-={speed * (float)elapsedTime,0.0f,0.0f};
        }
        else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        {
            eye+={speed * (float)elapsedTime,0.0f,0.0f};
        }

        if( currentKeyStates[ SDL_SCANCODE_UP ] )
        {
            eye+={0.0f,0.0f,speed * (float)elapsedTime};
        }
        else if( currentKeyStates[ SDL_SCANCODE_DOWN] )
        {
            eye-={0.0f,0.0f,speed * (float)elapsedTime};
        }


        if( currentKeyStates[ SDL_SCANCODE_SPACE ] && velocityY == 0.0f)
        {
            velocityY = jumpForce;
        }

        eye+={0.0f, velocityY * (float)elapsedTime,0.0f};

        if(eye.y <= 0.0f){
            velocityY = 0.0f;
        }else{
            velocityY -= (float)elapsedTime * gravity;
        }


        if(currentKeyStates[SDL_SCANCODE_RETURN]){
            if(currentTexture.id == texture.id)
                currentTexture = texture1;
            else 
                currentTexture = texture;

        }

        matrix_lookAt(lookAt,eye,target,up);
    }
    virtual void OnDraw(){
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,&model[0].x);  
        glUniformMatrix4fv(lookLoc,1,GL_FALSE,&lookAt[0].x);

        glBindTexture(GL_TEXTURE_2D,currentTexture.id);
        graphics.Draw(mesh);
    }

    virtual void OnExit(){
    }
};

int main(int argc, char **argv){
    Game game;
    game.CreateGame("Title",800,600);
    game.Start();
    return 0;
}