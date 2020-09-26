/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:51:22 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/26 17:27:08 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"
#include <math.h>

// m0 m4 m8  m12
// m1 m5 m9  m13
// m2 m6 m10 m14
// m3 m7 m11 m15

// 00 01 02 03
// 10 11 12 13
// 20 21 22 23
// 30 31 32 33

t_mat4		identity_mat4(void)
{
	t_mat4 m;

	m.data[0] = 1.0;
	m.data[1] = 0.0;
	m.data[2] = 0.0;
	m.data[3] = 0.0;

	m.data[4] = 0.0;
	m.data[5] = 1.0;
	m.data[6] = 0.0;
	m.data[7] = 0.0;

	m.data[8] = 0.0;
	m.data[9] = 0.0;
	m.data[10] = 1.0;
	m.data[11] = 0.0;

	m.data[12] = 0.0;
	m.data[13] = 0.0;
	m.data[14] = 0.0;
	m.data[15] = 1.0;
	return (m);
}

t_mat4 mat4_translate(t_vec3 translation)
{
	t_mat4 mat;

	mat = identity_mat4();
	mat.data[12] = translation.x;
	mat.data[13] = translation.y;
	mat.data[14] = translation.z;
	return (mat);
}

t_mat4	mat4_scale(t_vec3 scale)
{
	t_mat4 mat;

	mat = identity_mat4();
	mat.data[0] = scale.x;
	mat.data[5] = scale.y;
	mat.data[10] = scale.z;
	return (mat);
}

t_mat4 mat4_rotate_x(float angle)
{
	t_mat4 mat;
	float rad = ft_deg_to_rad(angle);
	mat = identity_mat4();
	mat.data[5] = cos(rad);
	mat.data[9] = -sin(rad);
	mat.data[6] = sin(rad);
	mat.data[10] = cos(rad);
	return (mat);
}

t_mat4 mat4_rotate_y(float angle)
{
	t_mat4 mat;
	float rad = ft_deg_to_rad(angle);
	mat = identity_mat4();
	mat.data[0] = cos(rad);
	mat.data[8] = sin(rad);
	mat.data[2] = -sin(rad);
	mat.data[10] = cos(rad);
	return (mat);
}

t_mat4 mat4_rotate_z(float angle)
{
	t_mat4 mat;
	float rad = ft_deg_to_rad(angle);
	mat = identity_mat4();
	mat.data[0] = cos(rad);
	mat.data[4] = -sin(rad);
	mat.data[1] = sin(rad);
	mat.data[5] = cos(rad);
	return (mat);
}

t_mat4 mat4_rotate_xyz(t_vec3 rotation)
{
	t_mat4 m;

	m = mat4_rotate_y(rotation.y);
	m = mul_mat4(m, mat4_rotate_x(rotation.x));
	m = mul_mat4(m, mat4_rotate_z(rotation.z));
	return (m);
}

t_mat4 mat4_trs(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4 trs;
	t_mat4 s;
	t_mat4 r;
	t_mat4 t;

	s = mat4_scale(scale);
	r = mat4_rotate_xyz(rot);
	t = mat4_translate(pos);
	trs = mul_mat4(s, r);
	trs = mul_mat4(trs, t);
	return (trs);
}

// [12][ab] [1⋅a+2⋅c 1⋅b+2⋅d]
// [34][cd] [3⋅a+4⋅c 3⋅b+4⋅d]

// m0 m4 m8  m12
// m1 m5 m9  m13
// m2 m6 m10 m14
// m3 m7 m11 m15

t_mat4	mul_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4	c;
	int		x;
	int		y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			int xv = y + x * 4;
			int yv = y * 4 + x;
			c.data[y + x * 4] =
				a.data[y + x * 4] * b.data[y * 4 + x] +
				a.data[(y + x * 4) + 1] * b.data[(y * 4 + x) * 1] +
				a.data[(y + x * 4) + 2] * b.data[(y * 4 + x) * 2] +
				a.data[(y + x * 4) + 3] * b.data[(y * 4 + x) * 3];
			x++;
		}
		y++;
	}
	return (c);
}

t_mat4	lookat_mat4(t_vec3 from, t_vec3 to, t_vec3 world_up)
{
	t_mat4	m;
	t_vec3		f;
	t_vec3		s;
	t_vec3		u;

	f = ft_normalize_vec3(ft_sub_vec3(to, from));
	s = ft_normalize_vec3(ft_cross_vec3(f, world_up));
	u = ft_cross_vec3(s, f);

	m = identity_mat4();

	m.data[0] = s.x;
	m.data[4] = s.y;
	m.data[8] = s.z;

	m.data[1] = u.x;
	m.data[5] = u.y;
	m.data[9] = u.z;

	m.data[2] = -f.x;
	m.data[6] = -f.y;
	m.data[10] = -f.z;

	m.data[12] = -ft_dot_vec3(s, from);
	m.data[13] = -ft_dot_vec3(u, from);
	m.data[14] = -ft_dot_vec3(f, from);
	return (m);
}

t_mat4        create_perspective_mat4(float fov, float aspect, float zn, float zf)
{
        t_mat4        mat;

		mat = identity_mat4();
		float rad =  ft_deg_to_rad(fov);
		float h = cosf(rad * 0.5) / sinf(rad * 0.5);
		float w = h * aspect;

		mat.data[0] = w;
		mat.data[5] = h;
		mat.data[10] = -(zf + zn) / (zf - zn);
		mat.data[14] = -1.0;
		mat.data[11] = -(2.0 * zf * zn) / (zf - zn);
        return (mat);
}
