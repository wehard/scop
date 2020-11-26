#version 330 core
in vec4 f_col;
in vec3 f_normal;
in vec2 f_uv;
in vec3 frag_pos;
out vec4 color;

uniform sampler2D main_texture;

vec3 triplanar_blend(vec3 normal){
	// normal is the world-space normal of the fragment
	vec3 blending = abs(normal);
	blending = normalize(max(blending, 0.00001)); // Force weights to sum to 1.0
	float b = (blending.x + blending.y + blending.z);
	blending /= vec3(b, b, b);
	return blending;
}

void main()
{
	vec2 uv_front = f_normal.xy;
    vec2 uv_side = f_normal.zy;
    vec2 uv_top = f_normal.xz;

	vec4 col_front = texture2D(main_texture, uv_front);
	vec4 col_side = texture2D(main_texture, uv_side);
	vec4 col_top = texture2D(main_texture, uv_top);

	vec3 weights = f_normal;
	weights = abs(weights);
	float power = 10.0;
	weights.x = pow(weights.x, power);
	weights.y = pow(weights.y, power);
	weights.z = pow(weights.z, power);
	weights = weights / (weights.x + weights.y + weights.z);

	col_front *= weights.z;
	col_side *= weights.x;
	col_top *= weights.y;

	vec4 col = col_front + col_side + col_top;

	vec3 light_pos = vec3(2.0, 20.0, 20.0);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diffuse = max(dot(f_normal, light_dir), 0.0);

	color = col * diffuse;
}
