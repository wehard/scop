#version 330 core
in vec4 f_col;
in vec3 f_normal;
in vec2 f_uv;
out vec4 color;

void main()
{
	color = f_col * vec4(f_uv, 1.0, 1.0);// * 1.0 - (gl_FragCoord.y / 720);
}
