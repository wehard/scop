/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_gen_uvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 16:41:28 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 15:50:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include <math.h>

static float	ft_abs_f(float f)
{
	if (f < 0.0)
		return (f * -1.0);
	return (f);
}

static int	max_axis(t_vec3 v)
{
	if (ft_abs_f(v.x) >= ft_abs_f(v.y) && ft_abs_f(v.x) >= ft_abs_f(v.z))
		return (AXIS_X);
	else if (ft_abs_f(v.y) >= ft_abs_f(v.z) && ft_abs_f(v.y) >= ft_abs_f(v.x))
		return (AXIS_Y);
	else
		return (AXIS_Z);
}

void	mesh_gen_uvs_sphere(t_mesh *mesh)
{
	size_t	i;
	t_vec2	uv;

	i = 0;
	while (i < mesh->num_uvs)
	{
		uv.x = 0.5 + (atan2(mesh->vertices[i].x, mesh->vertices[i].z) / (2 * 3.14));
		uv.y = 0.5 - (asin(mesh->vertices[i].y) / 3.14);
		mesh->uvs[i] = uv;
		i++;
	}
}

void	mesh_gen_uvs(t_mesh *mesh)
{
	size_t	i;
	t_vec2	uv;
	t_vec3	d;
	int		axis;

	i = 0;
	while (i < mesh->num_vertices)
	{
		d = ft_normalize_vec3(mesh->vertices[i]);
		axis = max_axis(d);
		if (axis == AXIS_X)
			uv = (t_vec2){(-d.z), (-d.y)};
		else if (axis == AXIS_Y)
			uv = (t_vec2){(d.x), (d.z)};
		else
			uv = (t_vec2){(d.x), (-d.y)};
		mesh->uvs[i] = uv;
		i++;
	}
}
