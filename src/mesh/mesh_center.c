/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:34:25 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/07 16:45:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

#define MAX_BOUNDS 50000
#define MIN_BOUNDS -50000

static void	mesh_calc_bounds(t_mesh *mesh)
{
	size_t i;

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


void	mesh_center(t_mesh *mesh)
{
	size_t	i;
	t_vec3 width;

	mesh_calc_bounds(mesh);

	width.x = mesh->bounds.max.x - mesh->bounds.min.x;
	width.y = mesh->bounds.max.y - mesh->bounds.min.y;
	width.z = mesh->bounds.max.z - mesh->bounds.min.z;

	i = 0;
	while (i < mesh->num_vertices)
	{
		mesh->vertices[i].x -= width.x / 2;
		mesh->vertices[i].y -= width.y / 2;
		mesh->vertices[i].z -= width.z / 2;
		i++;
	}
}
