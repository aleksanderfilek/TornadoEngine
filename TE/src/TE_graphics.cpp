#include"TE_graphics.hpp"

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
    glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);
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
        glTexImage2D(GL_TEXTURE_2D, 0, surface->format->format, surface->w, surface->h, 0, surface->format->format, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        int w = surface->w;
        int h = surface->h;

        SDL_FreeSurface(surface);
        vector2ui vec;
        vec.x = w;
        vec.y = h;
        return {texId,vec};
    }
    vector2ui vec;
    return {0,vec};
}

void BindTexture(GLuint &index, const Texture &texture){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

Mesh::Mesh(){

}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

bool Mesh::LoadObj(std::string path){

    std::vector<vector3f> temp_vertices;
    std::vector<vector2f> temp_uvs;

    struct vertexInfo{
        unsigned int v,u;
    };
    std::vector<vertexInfo> _info;

    FILE *file = fopen(path.c_str(),"r");
    if(file == NULL){
        std::cout<<"Imposible to open the file !"<<std::endl;
        return false;
    }

    while(1){
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; 

        if ( strcmp( lineHeader, "v" ) == 0 ){
            vector3f vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            vector2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }
        else if(strcmp(lineHeader, "f") == 0){
            vertexInfo f0, f1, f2;
            fscanf(file, "%d/%d %d/%d %d/%d\n",&f0.v,&f0.u,&f1.v,&f1.u,&f2.v,&f2.u);
            _info.push_back(f0);
            _info.push_back(f1);
            _info.push_back(f2);
        }
    }

    fclose(file);

    std::vector<vector3f> _vertices;
    std::vector<vector2f> _uvs;
    std::vector<vector3ui> _indices;

    for(unsigned int i = 0; i < _info.size(); i+=3){
        _vertices.push_back(temp_vertices[_info[i].v - 1]);
        _uvs.push_back(temp_uvs[_info[i].u - 1]);
        _vertices.push_back(temp_vertices[_info[i + 1].v - 1]);
        _uvs.push_back(temp_uvs[_info[i + 1].u - 1]);
        _vertices.push_back(temp_vertices[_info[i + 2].v - 1]);
        _uvs.push_back(temp_uvs[_info[i + 2].u - 1]);

        _indices.push_back({i, i+1, i+2});
    }

    temp_vertices.clear();
    temp_uvs.clear();
    _info.clear();

    this->Generate(_vertices.data(),_vertices.size(),_uvs.data(),_uvs.size(),_indices.data(),_indices.size());

    return true;
}

void Mesh::Generate(vector3f *_vertices,unsigned int _verticesCount , vector2f *_uvs, unsigned int _uvsCount, vector3ui *_indices, unsigned int _indicesCount){
        GLfloat _vertex[_verticesCount*3 + _uvsCount*2];

        for(int i = 0; i < _verticesCount; i++){
            _vertex[5*i] = _vertices[i].x;
            _vertex[5*i + 1] = _vertices[i].y;
            _vertex[5*i + 2] = _vertices[i].z;
            _vertex[5*i + 3] = _uvs[i].x;
            _vertex[5*i + 4] = _uvs[i].y;
        }

        this->indicesCount = 3*_indicesCount;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1,&EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertex),_vertex,GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesCount*sizeof(vector3ui),_indices,GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        glBindVertexArray(0);
}

inline void SetBackgroundColor(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
}

Font *loadFont(const char *path, unsigned int size){
    Font *font;
    font =  TTF_OpenFont(path, size);
    return font;
}

bool createTextTexture(Texture *texture, Font *font, const char *text, Color color){
    bool succes = true;

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if(textSurface == NULL){
        printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
        succes = false;
    }
    else{
        SDL_Texture *tex =SDL_CreateTextureFromSurface(renderer,textSurface);
        if(tex == NULL){
            printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
            succes = false;
        }
        else{
            texture->texture = tex;
            texture->width = textSurface->w;
            texture->height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }
    return true;
}
