/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_centroid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:02:53 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/21 14:44:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "vec3.h"

static double	tetrahedron_signed_volume(t_tri tri)
{
	return (ft_dot_vec3(tri.a, ft_cross_vec3(tri.b, tri.c)) / 6.0);
}

t_vec3	mesh_calc_centroid(t_mesh *mesh)
{
	t_tri	tri;
	t_vec3	ctd;
	double	total_vol;
	double	tetra_vol;
	size_t	i;

	ctd = ft_make_vec3(0, 0, 0);
	total_vol = 0;
	tetra_vol = 0;
	i = 0;
	while (i < mesh->num_indices)
	{
		tri.a = mesh->vertices[mesh->indices[i + 0]];
		tri.b = mesh->vertices[mesh->indices[i + 1]];
		tri.c = mesh->vertices[mesh->indices[i + 2]];
		tetra_vol = tetrahedron_signed_volume(tri);
		ctd = ft_add_vec3(ctd, ft_mul_vec3(ft_div_vec3(ft_add_vec3(tri.a,
							ft_add_vec3(tri.b, tri.c)), 4.0), tetra_vol));
		total_vol += tetra_vol;
		i += 3;
	}
	return (ft_div_vec3(ctd, total_vol));
}
