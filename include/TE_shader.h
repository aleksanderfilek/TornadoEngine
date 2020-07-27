#ifndef TESHADER_H_
#define TESHADER_H_

#include"TE.h"

#include<GL/glew.h>

typedef unsigned int TE_Shader;

void TE_shader_manager_init();
void TE_shader_manager_close();
void TE_shader_manager_clear();

TE_Shader TE_shader_load(const char* path);
void TE_shader_free(TE_Shader shader);
void TE_shader_bind(TE_Shader shader);
unsigned int TE_shader_get_uniform_location(TE_Shader shader, const char* name);

#endif