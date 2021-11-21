#version 410
layout(location = 0) in vec3 v_pos;
layout(location = 5) in vec2 v_uv;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec2 f_uv;

void main()
{
	f_uv = v_uv;
	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(v_pos, 1.0);
}
