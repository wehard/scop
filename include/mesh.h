/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:00:35 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:21:50 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include <stdlib.h>
# include "vec3.h"
# include "vec2.h"

# define AXIS_X 0
# define AXIS_Y 1
# define AXIS_Z 2

typedef struct s_triface
{
	t_vec3		v[3];
	t_vec3		n[3];
	t_vec2		uv[3];
	t_vec3		normal;
	t_vec3		e[3];
}				t_triface;

typedef struct s_bounds
{
	t_vec3		min;
	t_vec3		max;
}				t_bounds;

typedef struct s_mesh
{
	unsigned int	*indices;
	size_t			num_indices;
	t_vec3			*vertices;
	size_t			num_vertices;
	t_vec3			*normals;
	size_t			num_normals;
	t_vec2			*uvs;
	size_t			num_uvs;
	t_bounds		bounds;
}				t_mesh;

t_mesh			*mesh_create(void);
void			mesh_destroy(t_mesh *m);
void			mesh_create_verts(t_mesh *m, size_t num_vertices);
void			mesh_create_indices(t_mesh *m, size_t num_indices);
void			mesh_create_normals(t_mesh *m, size_t num_normals);
void			mesh_create_uvs(t_mesh *m, size_t num_uvs);
void			mesh_set_vert(t_mesh *m, size_t i, t_vec3 v);

void			mesh_gen_uvs(t_mesh *mesh);
void			mesh_center(t_mesh *mesh);

#endif
