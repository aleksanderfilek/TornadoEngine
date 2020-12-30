#include"TE_texture.h"

TE_TextureManager* TE_textureManager_init(int size)
{
    TE_TextureManager* manager = (TE_TextureManager*)malloc(sizeof(TE_TextureManager));

    manager->allocated_elements = size;
    manager->name = (char**)calloc(size, sizeof(char*));
    manager->gl_id = (unsigned int*)malloc(size * sizeof(unsigned int));
    manager->size = (int2*)malloc(size * sizeof(int2));

    return manager;
}

void TE_textureManager_free(TE_TextureManager* manager)
{
    TE_textureManager_clear(manager);
    free(manager);
}

void TE_textureManager_clear(TE_TextureManager* manager)
{
    // free string and delete glTexture
    for(int i = 0; i < manager->allocated_elements; i++)
    {
        if(manager->name[i] != NULL){
            free(manager->name[i]);
            glDeleteTextures(1, &manager->gl_id[i]);
        }
    }

    free(manager->name);
    free(manager->gl_id);
    free(manager->size);
    manager->allocated_elements = 0;
}

TE_Texture TE_texture_load(TE_TextureManager* manager, const char* path)
{
    // check if texture already was loaded. If yes, return index
    for(int i = 0; i < manager->allocated_elements; i++)
    {
        if(manager->name[i] != NULL && strcmp(path, manager->name[i]) == 0)
        {
            return i;
        }
    }

    // load texture from file
    int2 size;
    unsigned char *image = SOIL_load_image(path, &size.x, &size.y, 0, SOIL_LOAD_RGBA);

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    glBindTexture(GL_TEXTURE_2D, gl_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);


    // find space for new texture
    int index;
    for(index = 0; index < manager->allocated_elements; index++)
    {
        if(manager->name[index] == NULL)
        {
            break;
        }
    }

    // condition is true, means that there is need to allocate new space
    if(index == manager->allocated_elements)
    {
        manager->allocated_elements++;
        manager->name = (char**)realloc(manager->name, manager->allocated_elements * sizeof(char*));
        manager->gl_id = (unsigned int*)realloc(manager->gl_id, manager->allocated_elements * sizeof(unsigned int));
        manager->size = (int2*)realloc(manager->size, manager->allocated_elements * sizeof(int2));

        index = manager->allocated_elements - 1; // get new index
    }

    manager->name[index] = (char*)malloc(strlen(path)+1); //allocate memory for name
    strcpy(manager->name[index], path);
    manager->gl_id[index] = gl_id; 
    manager->size[index] = size; 

    return index;
    

}

void TE_texture_free(TE_TextureManager* manager, TE_Texture texture)
{
    if(manager->name[texture] == NULL)
        return;

    free(manager->name[texture]);
    manager->name[texture] = NULL;
    glDeleteTextures(1, &manager->gl_id[texture]);
    manager->size[texture] = (int2){0,0};
}

void TE_texture_bind(TE_TextureManager* manager, TE_Texture* texture, unsigned int count)
{
    for(int i = 0; i < count; i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, manager->gl_id[texture[i]]);
    }
}

inline int2 TE_texture_get_size(TE_TextureManager* manager, TE_Texture texture)
{
    return manager->size[texture];
}