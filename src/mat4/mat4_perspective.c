/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_perspective.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:26:52 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 16:54:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"
#include "libft.h"
#include <math.h>

t_mat4	mat4_perspective(float fov, float aspect, float zn, float zf)
{
	t_mat4	mat;
	float	tanhalffov;
	float	rad;

	rad = ft_deg_to_rad(fov);
	mat = mat4_init();
	tanhalffov = tanf(fov / 2.0);
	mat.data[0] = 1.0 / (aspect * tanhalffov);
	mat.data[5] = 1.0 / tanhalffov;
	mat.data[10] = -(zf + zn) / (zf - zn);
	mat.data[11] = -1.0;
	mat.data[14] = -(2.0 * zf * zn) / (zf - zn);
	return (mat);
}
