/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:21:37 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 16:53:56 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"
#include "libft.h"
#include <math.h>

t_mat4	mat4_rot_x(float angle)
{
	t_mat4	mat;
	float	rad;

	rad = ft_deg_to_rad(angle);
	mat = mat4_identity();
	mat.data[5] = cosf(rad);
	mat.data[9] = -sinf(rad);
	mat.data[6] = sinf(rad);
	mat.data[10] = cosf(rad);
	return (mat);
}

t_mat4	mat4_rot_y(float angle)
{
	t_mat4	mat;
	float	rad;

	rad = ft_deg_to_rad(angle);
	mat = mat4_identity();
	mat.data[0] = cosf(rad);
	mat.data[8] = sinf(rad);
	mat.data[2] = -sinf(rad);
	mat.data[10] = cosf(rad);
	return (mat);
}

t_mat4	mat4_rot_z(float angle)
{
	t_mat4	mat;
	float	rad;

	rad = ft_deg_to_rad(angle);
	mat = mat4_identity();
	mat.data[0] = cosf(rad);
	mat.data[4] = -sinf(rad);
	mat.data[1] = sinf(rad);
	mat.data[5] = cosf(rad);
	return (mat);
}

t_mat4	mat4_rot_xyz(t_vec3 rotation)
{
	t_mat4	m;

	m = mat4_rot_y(rotation.y);
	m = mat4_mul(m, mat4_rot_x(rotation.x));
	m = mat4_mul(m, mat4_rot_z(rotation.z));
	return (m);
}
