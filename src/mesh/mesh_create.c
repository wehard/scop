/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:24:04 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/26 10:15:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ft_printf.h"

t_mesh	*mesh_create(void)
{
	t_mesh *m;

	if (!(m = (t_mesh*)malloc(sizeof(t_mesh))))
	{
		ft_printf("mesh_create: failed to allocate memory for t_mesh!\n");
		return (NULL);
	}
	m->num_vertices = 0;
	m->vertices = NULL;
	m->num_trifaces = 0;
	m->trifaces = NULL;
	m->num_normals = 0;
	m->normals = NULL;
	m->num_uvs = 0;
	m->uvs = NULL;
	m->indices = NULL;
	m->num_indices = 0;
	// m->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
	// m->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);
	return (m);
}

void	mesh_create_verts(t_mesh *m, size_t num_vertices)
{
	if (!m)
		return ;
	m->num_vertices = num_vertices;
	if (num_vertices == 0)
		return ;
	if (m->vertices)
		free(m->vertices);
	if (!(m->vertices = (t_vec3*)malloc(sizeof(t_vec3) * num_vertices)))
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
	if (!(m->indices = (unsigned int*)malloc(sizeof(unsigned int) * num_indices)))
	{
		ft_printf("mesh_create: failed to allocate memory for vertices!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_create_normals(t_mesh *m, size_t num_normals)
{
	if (!m)
		return ;
	m->num_normals = num_normals;
	if (num_normals == 0)
		return ;
	if (m->normals)
		free(m->normals);
	if (!(m->normals = (t_vec3*)malloc(sizeof(t_vec3) * num_normals)))
	{
		ft_printf("mesh_create: failed to allocate memory for normals!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_create_uvs(t_mesh *m, size_t num_uvs)
{
	if (!m)
		return ;
	m->num_uvs = num_uvs;
	if (num_uvs == 0)
		return ;
	if (m->uvs)
		free(m->uvs);
	if (!(m->uvs = (t_vec2*)malloc(sizeof(t_vec2) * num_uvs)))
	{
		ft_printf("mesh_create: failed to allocate memory for uvs!\n");
		exit(EXIT_FAILURE);
	}
}

void	mesh_create_trifaces(t_mesh *m, size_t num_trifaces)
{
	if (!m)
		return ;
	if (m->trifaces)
		free(m);
	m->num_trifaces = num_trifaces;
	if (num_trifaces == 0)
		return ;
	if (!(m->trifaces = (t_triface*)malloc(sizeof(t_triface) * num_trifaces)))
	{
		ft_printf("mesh_create: failed to allocate memory for faces!\n");
		exit(EXIT_FAILURE);
	}
}
