#ifndef TESHADER_H_
#define TESHADER_H_

#include"TE.h"

#include<GL/glew.h>

typedef unsigned int TE_Shader;

typedef struct TE_ShaderManager{
    unsigned int allocated_elements;

    char** name;
    unsigned int* gl_id;
}TE_ShaderManager;


TE_ShaderManager* TE_shaderManager_init(int size);
void TE_shaderManager_close(TE_ShaderManager* manager);

TE_Shader TE_shader_load(TE_ShaderManager* manager, const char* path);
void TE_shader_free(TE_ShaderManager* manager, TE_Shader shader);
void TE_shader_bind(TE_ShaderManager* manager, TE_Shader shader);
unsigned int TE_shader_get_uniform_location(TE_ShaderManager* manager, TE_Shader shader, const char* name);

#endif