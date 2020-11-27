#version 330 core
in vec4 f_col;
in vec3 f_normal;
in vec3 w_normal;
in vec2 f_uv;
in vec3 frag_pos;

out vec4 color;

void main()
{
	vec3 light_pos = vec3(2.0, 15.0, 25.0);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diffuse = max(dot(w_normal, light_dir), 0.0);
	float light_intensity = 5.0;
	color = f_col * diffuse * light_intensity;
}
