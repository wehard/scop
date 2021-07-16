/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:24:04 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 16:14:56 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ft_printf.h"

t_mesh	*mesh_create(void)
{
	t_mesh	*m;

	m = (t_mesh *)malloc(sizeof(t_mesh));
	if (!m)
	{
		ft_printf("mesh_create: failed to allocate memory for t_mesh!\n");
		return (NULL);
	}
	m->num_vertices = 0;
	m->vertices = NULL;
	m->num_normals = 0;
	m->normals = NULL;
	m->num_uvs = 0;
	m->uvs = NULL;
	m->indices = NULL;
	m->num_indices = 0;
	return (m);
}

void	mesh_create_verts(t_mesh *m, size_t num_vertices)
{
	if (!m || num_vertices == 0)
		return ;
	m->num_vertices = num_vertices;
	if (m->vertices)
		free(m->vertices);
	m->vertices = (t_vec3 *)malloc(sizeof(t_vec3) * num_vertices);
	if (!m->vertices)
	{
		ft_printf("mesh_create: failed to allocate memory for vertices!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_create_indices(t_mesh *m, size_t num_indices)
{
	if (!m || num_indices == 0)
		return ;
	m->num_indices = num_indices;
	m->indices = (unsigned int *)malloc(sizeof(unsigned int) * num_indices);
	if (!m->indices)
	{
		ft_printf("mesh_create: failed to allocate memory for vertices!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_create_normals(t_mesh *m, size_t num_normals)
{
	if (!m || num_normals == 0)
		return ;
	m->num_normals = num_normals;
	if (m->normals)
		free(m->normals);
	m->normals = (t_vec3 *)malloc(sizeof(t_vec3) * num_normals);
	if (!m->normals)
	{
		ft_printf("mesh_create: failed to allocate memory for normals!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_create_uvs(t_mesh *m, size_t num_uvs)
{
	if (!m || num_uvs == 0)
		return ;
	m->num_uvs = num_uvs;
	if (m->uvs)
		free(m->uvs);
	m->uvs = (t_vec2 *)malloc(sizeof(t_vec2) * num_uvs);
	if (!m->uvs)
	{
		ft_printf("mesh_create: failed to allocate memory for uvs!\n");
		exit(EXIT_FAILURE);
	}
}
