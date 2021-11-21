/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_offset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:27:18 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/21 14:31:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "vec3.h"

void	mesh_offset(t_mesh *mesh, t_vec3 offset)
{
	size_t	i;

	i = 0;
	while (i < mesh->num_vertices)
	{
		mesh->vertices[i] = ft_sub_vec3(mesh->vertices[i], offset);
		i++;
	}
}
