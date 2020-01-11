#ifndef TEGRAPHICS_H_
#define TEGRAPHICS_H_

#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include<unordered_map>

#include<SDL.h>
#include<SDL_main.h>
#include<SDL_image.h>
#include<GL/glew.h>
#include<SDL_opengl.h>

#include<TE_math.h>

void Graphics_Init();
void Graphics_Close();


struct Shader{
    int ID;
    std::unordered_map<std::string,GLuint> uniformLocation;
    //TODO: add uniform searching
    void Load(const char *vertexSourcePath, const char *fragmentSourcePath);
};

struct MaterialProperty{
    GLuint location;
    int type;
    union value{
        float Float;
        vector2 Vector2;
        vector3 vector3;
        vector4 Vector4;
        mat2x2 Mat2x2;
        mat3x3 Mat3x3;
        mat4x4 Mat4x4;
    };
};

class Material{
private:
    Shader programShader;
    std::vector<MaterialProperty> property;
public:
    Material();
    ~Material();

    void Use();

    int BindTexture(int texture);
    int SetFloat(std::string uniformName, float value, bool Static);
    int SetVector2(std::string uniformName, vector2 value, bool Static);
    int SetVector3(std::string uniformName, vector3 value, bool Static);
    int SetVector4(std::string uniformName, vector4 value, bool Static);
    int SetMat2x2(std::string uniformName, mat2x2 value, bool Static);
    int SetMat3x3(std::string uniformName, mat3x3 value, bool Static);
    int SetMat4x4(std::string uniformName, mat4x4 value, bool Static);
};

class Mesh{
private:
    GLuint ID;
public:
    vector3 *vertices;
    int *triangles;
    vector2 *uvs;

    void Generate();
};

void SetBackgroundColor(float r, float g, float b, float a);
#endif