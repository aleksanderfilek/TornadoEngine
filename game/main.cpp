#include"TE.h"
#include"TE_graphics.h"

#include"Player.h"

class Game:public TornadoEngine{
private:
    Graphics graphics;
    Mesh mesh;
    Shader program;
    mat4x4 model;
    GLuint modelLoc;

    mat4x4 lookAt;

    GLuint lookLoc;

    Texture texture;

    Player player;

    vector3f up = {0.0f, 1.0f, 0.0f};

protected:
    virtual void OnStart(){
        texture = Tex_Load("res/wall.jpg");
        
        program.Load("res/vertex.vs","res/fragment.frag");
        mesh.LoadObj("res/Floor.obj");

        glUseProgram(program.ID);
        modelLoc = glGetUniformLocation(program.ID,"model");
        GLuint projectionLoc = glGetUniformLocation(program.ID,"projection");

        mat4x4 projection;
        matrix_projection(projection,800,600,120.0f,0.1f,1000.0f);

        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,&projection[0].x);

        lookLoc = glGetUniformLocation(program.ID,"lookAt");

        vector3f eye = {0.0f, 0.0f, 0.0f};
        vector3f center = {0.0f, 0.0f, 1.0f};

        matrix_identity(model);
        matrix_translate(model,{0.0f, -1.0f, 0.0f});
    }

    virtual void OnUpdate(float elapsedTime){
        vector3f eye, forward;
        player.Update(elapsedTime, eye ,forward);

        vector3f target = {0.0f,0.0f,0.0f};
        target = eye + forward;
        matrix_lookAt(lookAt,eye,target,up);
    }
    virtual void OnDraw(){
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,&model[0].x);  
        glUniformMatrix4fv(lookLoc,1,GL_FALSE,&lookAt[0].x);

        glBindTexture(GL_TEXTURE_2D,texture.id);
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