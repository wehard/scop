#version 330 core
layout(location = 0) in vec3 v_pos;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform vec4 color;

out vec4 p;

void main()
{
	p = vec4(normalize(abs(v_pos)), 1.0);
	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(v_pos, 1.0);
}
