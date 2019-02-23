#version 330 core
layout (location = 0) in float index;
layout (location = 1) in vec2 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 position;
uniform vec2 size;

void main()
{

	gl_Position = vec4(aPos + position, 0.0, 1.0);
	switch(int(index)) {
		case 0: {
			gl_Position.xy += size.xy;
		} break;
		case 1: {
			gl_Position.x += size.x;
		} break;
		case 2: {
			// do nothing
		} break;
		case 3: {
			gl_Position.y += size.y;
		} break;
	}
	ourColor = aColor;
	TexCoord = aTexCoord;
}