#version 330 core
in vec4 f_col;
in vec3 w_normal;
in vec3 f_normal;
in vec2 f_uv;
in vec3 frag_pos;
out vec4 color;

uniform sampler2D main_texture;

void main()
{
	color = texture(main_texture, f_uv);
}
