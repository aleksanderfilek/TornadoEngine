#ifndef TETEXTURE_H_
#define TETEXTURE_H_

#include"TE.h"
#include<SOIL/SOIL.h>

typedef unsigned int TE_Texture;

typedef struct TE_TextureManager{
    unsigned long map_bitset;
    unsigned int allocated_elements;

    char** name;
    unsigned int* gl_id;
    int2* size;

}TE_TextureManager;

TE_TextureManager* TE_textureManager_init(int size);
void TE_textureManager_free(TE_TextureManager* manager);
void TE_textureManager_clear(TE_TextureManager* manager);

TE_Texture TE_texture_load(TE_TextureManager* manager, const char* path);
void TE_texture_free(TE_TextureManager* manager, TE_Texture texture);
void TE_texture_bind(TE_TextureManager* manager, TE_Texture* texture, unsigned int count);
int2 TE_texture_get_size(TE_TextureManager* manager, TE_Texture texture);

#endif