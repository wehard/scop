/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:34:25 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 15:52:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

#define MAX_BOUNDS 50000
#define MIN_BOUNDS -50000
#define BLA 0.001

static void	mesh_calc_bounds(t_mesh *mesh)
{
	size_t	i;

	mesh->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
	mesh->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);
	i = 0;
	while (i < mesh->num_vertices)
	{
		if (mesh->vertices[i].x < mesh->bounds.min.x)
			mesh->bounds.min.x = mesh->vertices[i].x;
		if (mesh->vertices[i].y < mesh->bounds.min.y)
			mesh->bounds.min.y = mesh->vertices[i].y;
		if (mesh->vertices[i].z < mesh->bounds.min.z)
			mesh->bounds.min.z = mesh->vertices[i].z;
		if (mesh->vertices[i].x > mesh->bounds.max.x)
			mesh->bounds.max.x = mesh->vertices[i].x;
		if (mesh->vertices[i].y > mesh->bounds.max.y)
			mesh->bounds.max.y = mesh->vertices[i].y;
		if (mesh->vertices[i].z > mesh->bounds.max.z)
			mesh->bounds.max.z = mesh->vertices[i].z;
		i++;
	}
}

static float	ft_map_range(float v, t_vec2 from, t_vec2 to)
{
	return ((((v - from.x) * (to.y - to.x)) / (from.y - from.x)) + to.x);
}

void	mesh_center(t_mesh *mesh)
{
	size_t	i;
	t_vec3	width;

	mesh_calc_bounds(mesh);
	width = ft_make_vec3(
			(mesh->bounds.max.x - mesh->bounds.min.x) / 2,
			(mesh->bounds.max.y - mesh->bounds.min.y) / 2,
			(mesh->bounds.max.z - mesh->bounds.min.z) / 2);
	i = 0;
	while (i < mesh->num_vertices)
	{
		mesh->vertices[i].x = ft_map_range(mesh->vertices[i].x,
				ft_make_vec2(mesh->bounds.min.x, mesh->bounds.max.x),
				ft_make_vec2(-width.x, width.x));
		mesh->vertices[i].y = ft_map_range(mesh->vertices[i].y,
				ft_make_vec2(mesh->bounds.min.y, mesh->bounds.max.y),
				ft_make_vec2(-width.y, width.y));
		mesh->vertices[i].z = ft_map_range(mesh->vertices[i].z,
				ft_make_vec2(mesh->bounds.min.z, mesh->bounds.max.z),
				ft_make_vec2(-width.z, width.z));
		i++;
	}
}
