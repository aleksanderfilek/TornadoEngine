#ifndef TETEXTURE_H_
#define TETEXTURE_H_

#include"TE.h"
#include<SOIL/SOIL.h>

typedef unsigned int TE_Texture;

void TE_texture_manager_init();
void TE_texture_manager_close();
void TE_texture_manager_clear();

TE_Texture TE_texture_load(const char* path);
void TE_texture_free(TE_Texture texture);
void TE_texture_bind(TE_Texture* texture, unsigned int count);
float2 TE_texture_get_size(TE_Texture texture);

#endif