#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec4 ourColor;

void main()
{
	ourColor = vec4(texCoord.x,texCoord.y,1.0,1.0);
	gl_Position = vec4(position.x,position.y,position.z, 1.0);
}