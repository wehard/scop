#version 330 core
in vec4 f_col;
in vec3 f_normal;
in vec2 f_uv;
out vec4 color;

void main()
{
	color = vec4(f_uv.x, f_uv.y, 0.0, 1.0);// * 1.0 - (gl_FragCoord.y / 720);
}
