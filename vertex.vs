#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 lookAt;
uniform mat4 projection;
uniform mat4 model;

out vec4 ourColor;

void main()
{
	ourColor = vec4(texCoord.x,texCoord.y,1.0,1.0);
	gl_Position = projection * lookAt * model * vec4(position, 1);
}