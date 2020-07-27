#include"TE_texture.h"


typedef struct{
    unsigned int id;
    float2 size;
}Texture;

typedef struct{
    char* name;
    Texture texture;
}Texture_Map;

typedef struct Texture_Manager{
    long map_bitset;
    Texture_Map* texture_map;
    unsigned int allocated_elements;
}Texture_Manager;

Texture_Manager* texture_manager = NULL;

void TE_texture_manager_init()
{
    texture_manager = (Texture_Manager*)malloc(sizeof(Texture_Manager));
    texture_manager->texture_map = NULL;
    texture_manager->map_bitset = 0;
    texture_manager->allocated_elements = 0;
}

void TE_texture_manager_close()
{
    TE_texture_manager_clear();
    free(texture_manager);
}

void TE_texture_manager_clear()
{
    int i;
    for(i = 0; i < texture_manager->allocated_elements; i++)
    {
        if(texture_manager->map_bitset & 1UL<<i ){
            free(texture_manager->texture_map[i].name);
            glDeleteTextures(1, &texture_manager->texture_map[i].texture.id);
        }
    }

    free(texture_manager->texture_map);
    texture_manager->allocated_elements = 0;
}

TE_Texture TE_texture_load(const char* path)
{
    int i;
    for(i = 0; i < texture_manager->allocated_elements; i++)
    {
        if(texture_manager->map_bitset & 1UL<<i && strcmp(path, texture_manager->texture_map[i].name) == 0)
        {
            return i;
        }
    }

     int width, height;
    unsigned char *image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    Texture texture = {id, {width, height}};
    
    int index;

    int maximum_posible_number = pow(2,texture_manager->allocated_elements) - 1;
    if(texture_manager->map_bitset < maximum_posible_number)
    {
        for(index = 0; index < texture_manager->allocated_elements; index++)
        {
            if(!(texture_manager->map_bitset & 1UL<<index))
            {
                break;
            }
        }
    }
    else{
        // Add texture map element to texture map
        texture_manager->allocated_elements++;
        texture_manager->texture_map = (Texture_Map*)realloc(texture_manager->texture_map, 
                                                    texture_manager->allocated_elements * sizeof(Texture_Map));
        index = texture_manager->allocated_elements - 1;
    }

    texture_manager->texture_map[index].texture = texture;
    texture_manager->texture_map[index].name = (char*)malloc(strlen(path)+1);
    strcpy(texture_manager->texture_map[index].name, path);

    return index;
}

void TE_texture_free(TE_Texture texture)
{
    if(!(texture_manager->map_bitset & 1UL<<texture))
        return;

    free(texture_manager->texture_map[texture].name);
    texture_manager->texture_map[texture].name = NULL;
    glDeleteTextures(1, &texture_manager->texture_map[texture].texture.id);

    texture_manager->map_bitset ^= 1UL << texture;
}

void TE_texture_bind(TE_Texture* texture, unsigned int count)
{
    for(int i = 0; i < count; i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture_manager->texture_map[texture[i]].texture.id);
    }
}

inline float2 TE_texture_get_size(TE_Texture texture)
{
    return texture_manager->texture_map[texture].texture.size;
}