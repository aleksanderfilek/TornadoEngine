#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform vec3 translation;

void main()
{
	float x = (position.x + translation.x) * 0.05f;
	float y = (position.y + translation.y) * 0.05f;
	float z = (position.z + translation.z) * 0.05f;

	gl_Position = vec4(x,y,z, 1.0);
}