#version 330 core
layout (location = 0) in float index;
layout (location = 1) in vec2 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 vertexPositions[4];

void main()
{
	gl_Position = vec4(aPos + vertexPositions[int(index)], 0.0, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
}