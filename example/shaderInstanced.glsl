#vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat3 offset[100];
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position + offset[gl_InstanceID], 1.0f);
    Normal = mat3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(position, 1.0f));
    TexCoord = texCoord;
}

#fragment
#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightPos = vec3(-1.0f, 1.0f, 0.0f);

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = ambient + diffuse;
    vec4 texColor = vec4(result, 1.0f) * texture(ourTexture, TexCoord);

    color = texColor;
}