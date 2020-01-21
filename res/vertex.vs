#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 lookAt;
uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoord;

void main()
{
	TexCoord = texCoord;
	gl_Position = projection * lookAt * model * vec4(position, 1);
}