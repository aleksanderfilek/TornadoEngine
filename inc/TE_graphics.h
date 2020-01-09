#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<GL/glew.h>
#include<SDL_opengl.h>

#include<TE_math.h>

void Graphics_Init();
void Graphics_Close();

typedef unsigned int shader;
shader Shader_Load(const char *vertexSourcePath, const char *fragmentSourcePath);

struct Texture{
    GLuint id;
    vector2 size;
};

Texture Tex_Load(const char *path);
void Tex_Draw(Texture *texture, shader Shader, vector2 position);
void Tex_DrawEx(Texture *texture, shader Shader, vector2 position, vector2 scale, vector4 srcRect);
//TODO: add this function
void Tex_Destroy(Texture texture);

void SetBackgroundColor(float r, float g, float b, float a);
#endif