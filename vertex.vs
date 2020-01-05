#version 330 core
layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;

uniform vec2 position;
uniform vec2 size;
uniform vec4 srcRect;


void main()
{
	float x =  size.x * Position.x;
	x = x / 640;
	x = x - 1;

	float px = position.x;
	px = px / 640;
	x = x + px;

	float y = size.y * Position.y;
	y = y / 480;
	y = y + 1;

	float py = position.y;
	py = py / 480;
	y = y - py;

	gl_Position = vec4(x,y,1.0f, 1.0f);
	texCoord = vec2(TexCoord.x*srcRect.z + srcRect.x, TexCoord.y*srcRect.w + srcRect.y);
}