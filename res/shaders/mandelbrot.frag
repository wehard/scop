#version 410

in vec2 f_uv;
out vec4 frag_color;

void main()
{
	float scale = 2.0;
	vec2 center = vec2(0, 0);
	int iter = 256;

	float cr = f_uv.x * scale - center.x;
	float ci = f_uv.y * scale - center.y;

	float zr = 0.0;
	float zi = 0.0;

	float r;
	int i = 0;

	while (i < iter && r < 4.0)
	{
		float t = (zr * zr) - (zi * zi) + cr;
		zi = 2.0 * zr * zi + ci;
		zr = t;
		r = (zr*zr) + (zi*zi);
		i++;
	}
	vec3 col;

	if (r < 2.0)
		col = vec3(0.0);
	else
		col = vec3(fract(float(i)*0.03), fract(float(i)*0.01), fract(float(i)*0.05));
	frag_color = vec4(col, 1.0);
}
