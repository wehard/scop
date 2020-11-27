#version 330 core
layout(location = 0) in vec3 v_pos;
layout(location = 1) in mat4 model_matrix; // will use location 1 2 3 4
// layout(location = 1) in vec4 v_col;
layout(location = 5) in vec2 v_uv;
// layout(location = 3) in vec3 v_normal;

// uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform vec4 color;

out vec4 f_col;
out vec3 f_normal;
out vec3 w_normal;
out vec2 f_uv;
out vec3 frag_pos;

void main()
{
	f_uv = v_uv;
	f_col = color;
	f_normal = normalize(v_pos);
	w_normal = mat3(transpose(inverse(model_matrix))) * f_normal;
	frag_pos = vec3(model_matrix * vec4(v_pos, 1.0));
	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(v_pos, 1.0);
}
