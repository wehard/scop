/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_set_vert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 18:23:08 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:56:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "mesh.h"

void	mesh_set_vert(t_mesh *m, size_t i, t_vec3 v)
{
	if (!m || !m->vertices || i > m->num_vertices - 1)
	{
		exit_message("mesh_set_vert: failed to set vertex!\n");
	}
	else
		m->vertices[i] = v;
}
