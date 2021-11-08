#version 330 core
layout(location = 0) in vec3 v_pos;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform vec4 color;

void main()
{
	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(v_pos, 1.0);
}
