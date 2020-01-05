#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>

#include<SDL2/SDL.h>
#include<SDL2/SDL_main.h>
#include<SDL2/SDL_image.h>
#include<GL/glew.h>
#include<SDL2/SDL_opengl.h>

#include<TE_math.h>

void Graphics_Init();
void Graphics_Close();

typedef unsigned int shader;
shader Shader_Load(const char *vertexSourcePath, const char *fragmentSourcePath);

class Material{
private:
    shader program;
    std::vector<GLuint> textures;
public:
    Material(shader Program);
    ~Material();

    void Use();
};

struct Texture{
    GLuint id;
    vector2 size;
};

Texture Tex_Load(const char *path);
void Tex_Draw(Texture *texture, shader Shader, vector2 position);
void Tex_DrawEx(Texture *texture, shader Shader, vector2 position, vector2 scale, vector4 srcRect); //TODO: add sourceRect 


#endif