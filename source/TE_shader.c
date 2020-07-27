#include"TE_shader.h"

#include<stdio.h>
#include<string.h>

typedef struct Shader{
    unsigned int Id;
}Shader;

typedef struct{
    char* name;
    Shader shader;
}Shader_Map;

typedef struct Shader_manager{
    long map_bitset;
    Shader_Map* shader_map;
    unsigned int allocated_elements;
} Shader_Manager;

Shader_Manager* shader_manager = NULL;

void TE_shader_manager_init()
{
    shader_manager = (Shader_Manager*)malloc(sizeof(Shader_Manager));
    shader_manager->shader_map = NULL;
    shader_manager->map_bitset = 0;
    shader_manager->allocated_elements = 0;
}

void TE_shader_manager_close()
{
    TE_shader_manager_clear();
    free(shader_manager);
}

void TE_shader_manager_clear()
{
    int i;
    for(i = 0; i < shader_manager->allocated_elements; i++)
    {
        if(shader_manager->map_bitset & 1UL<<i ){
            free(shader_manager->shader_map[i].name);
            glDeleteShader(shader_manager->shader_map[i].shader.Id);
        }
    }

    free(shader_manager->shader_map);
    shader_manager->allocated_elements = 0;
}

TE_Shader TE_shader_load(const char* path)
{
    // Check if shader was loaded
    // If was loaded return it
    int i;
    for(i = 0; i < shader_manager->allocated_elements; i++)
    {
        if(shader_manager->map_bitset & 1UL<<i && strcmp(path, shader_manager->shader_map[i].name) == 0)
        {
            return i;
        }
    }

    // Load shader from file
    FILE* file = fopen(path, "r");

    if(file == NULL){
        printf("Imposible to open the file!\n");
        return -1;
    }

    unsigned int vertex_shader_size = 1024;
    unsigned int vertex_shader_used_bytes = 0;
    char* vertex_shader_code = (char*)calloc(vertex_shader_size, sizeof(char));

    size_t fragment_shader_size = 1024;
    size_t fragment_shader_used_bytes = 0;
    char* fragment_shader_code = (char*)calloc(fragment_shader_size, sizeof(char));

    int shader_type = -1;

    char chunk[128];

    while(fgets(chunk, sizeof(chunk), file) != NULL)
    {
        if(strstr(chunk, "// vertex") != NULL)
        {
            shader_type = 0;
            //continue;
        }
        else if(strstr(chunk, "// fragment") != NULL)
        {
            shader_type = 1;
            //continue;
        }

        switch (shader_type)
        {
        case 0:
                if((vertex_shader_size - vertex_shader_used_bytes) < strlen(chunk)){
                    vertex_shader_code = (char*)realloc(vertex_shader_code, vertex_shader_size + 1024);
                    vertex_shader_size += 1024;
                }
                strcat(vertex_shader_code, chunk);
                vertex_shader_used_bytes += strlen(chunk);
            break;  
        case 1:
                if((fragment_shader_size - fragment_shader_used_bytes) < strlen(chunk)){
                    fragment_shader_code = (char*)realloc(fragment_shader_code, fragment_shader_size + 1024);
                    fragment_shader_size += 1024;
                }
                strcat(fragment_shader_code, chunk);
                fragment_shader_used_bytes += strlen(chunk);
            break;
        }
    }

    fclose(file);

    // Create shader program
    char vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char**)&vertex_shader_code, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char**)&fragment_shader_code, NULL);
    glCompileShader(fragment);

    unsigned int program = glCreateProgram();
    glAttachShader(program,vertex);
    glAttachShader(program,fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertex_shader_code);
    free(fragment_shader_code);

    // Create shader
    Shader shader;
    shader.Id = program;

    int index;

    int maximum_posible_number = pow(2,shader_manager->allocated_elements) - 1;
    if(shader_manager->map_bitset < maximum_posible_number)
    {
        for(index = 0; index < shader_manager->allocated_elements; index++)
        {
            if(!(shader_manager->map_bitset & 1UL<<index))
            {
                break;
            }
        }
    }
    else{
        // Add shader map element to shader map
        shader_manager->allocated_elements++;
        shader_manager->shader_map = (Shader_Map*)realloc(shader_manager->shader_map, 
                                                    shader_manager->allocated_elements * sizeof(Shader_Map));
        index = shader_manager->allocated_elements - 1;
    }

    shader_manager->shader_map[index].shader = shader;
    shader_manager->shader_map[index].name = (char*)malloc(strlen(path)+1);
    strcpy(shader_manager->shader_map[index].name, path);

    return index;
}

void TE_shader_free(TE_Shader shader)
{
    if(!(shader_manager->map_bitset & 1UL<<shader))
        return;

    free(shader_manager->shader_map[shader].name);
    shader_manager->shader_map[shader].name = NULL;
    glDeleteProgram(shader_manager->shader_map[shader].shader.Id);

    shader_manager->map_bitset ^= 1UL << shader;
}

inline void TE_shader_bind(TE_Shader shader)
{
    glUseProgram(shader_manager->shader_map[shader].shader.Id);
}

inline unsigned int TE_shader_get_uniform_location(TE_Shader shader, const char* name)
{
    glGetUniformLocation(shader_manager->shader_map[shader].shader.Id, name);
}

