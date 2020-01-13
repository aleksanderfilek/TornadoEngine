#include"TE_graphics.h"

int textureCount = 0;

Graphics::Graphics(){

}

Graphics::~Graphics(){

}

void Graphics::InstantiateMesh(Mesh &mesh){
    glBindVertexArray(mesh.GetId());
}

void Graphics::DeinstantiateMesh(){
    glBindVertexArray(0);
}

 void Graphics::DrawInstantiatedMesh(){
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
 }

void Graphics::Draw(Mesh &mesh){
    glBindVertexArray(mesh.GetId());
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Shader::Load(const char *vertexSourcePath, const char *fragmentSourcePath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        vShaderFile.open(vertexSourcePath);
        fShaderFile.open(fragmentSourcePath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e){
        std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"<<std::endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLchar vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    GLuint program = glCreateProgram();
    glAttachShader(program,vertex);
    glAttachShader(program,fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    this->ID = program;
}

Texture Tex_Load(const char *path){
    SDL_Surface *surface = IMG_Load(path);
    if(surface == NULL){
        std::cout<<"Texture could not be load"<<std::endl;
    }
    else{
        GLuint texId = textureCount++;
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        int w = surface->w;
        int h = surface->h;

        SDL_FreeSurface(surface);
        vector2 vec;
        vec.x = w;
        vec.y = h;
        return {texId,vec};
    }
    vector2 vec;
    return {0,vec};
}

Mesh::Mesh(){
    this->uvsCount = 8;
    uvs = new float[8]{0};
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);

    free(this->vertices);
    free(this->uvs);
    free(this->indices);
}

void Mesh::Generate(){
    GLfloat data[this->verticesCount + this->uvsCount];

    for(int i = 0, v = 0, u = 0; i < this->verticesCount + this->uvsCount; i+=5, v+=3, u+=2){
        data[i + 0] = this->vertices[v + 0];
        data[i + 1] = this->vertices[v + 1];
        data[i + 2] = this->vertices[v + 2];
        data[i + 3] = this->uvs[u + 0];
        data[i + 4] = this->uvs[u + 1];
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesCount * sizeof(int), this->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::SetVertices(float *_vertices, unsigned int count){
    this->verticesCount = count;
    vertices = new float[count];
    for(int i = 0; i < count;i++){
        this->vertices[i] = _vertices[i];
    }
}

void Mesh::SetIndices(int *_indices, unsigned int count){
    this->indicesCount = count;
    indices = new int[count];
    for(int i = 0; i < count;i++){
        this->indices[i] = _indices[i];
    }}

void SetBackgroundColor(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
}
