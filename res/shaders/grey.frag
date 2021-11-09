#version 330 core

out vec4 color;

void main()
{
	color = vec4(0.1) * (gl_PrimitiveID % 5) + vec4(0.1);
}
