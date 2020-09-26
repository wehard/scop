/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:32:17 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/26 13:36:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdint.h>
#include "vector.h"

struct s_mesh;
struct s_shader;

typedef struct	s_camera
{
	t_vec3		position;
}				t_camera;

typedef struct	s_entity
{
	struct s_mesh *mesh;
	struct s_shader *shader;
	t_vec3		position;
	t_vec3		scale;
	t_vec3		rotation;
	uint32_t	vao_id;
	uint32_t	vbo_id;
	uint32_t	ebo_id;
}				t_entity;

typedef struct	s_mat4
{
	float		data[16];
}				t_mat4;

void	exit_message(const char *message);
void    free_null(size_t count, ...);

t_entity	*create_entity(struct s_mesh *mesh, struct s_shader *shader);
void		draw_entity(t_camera *camera, t_entity *entity);

#endif
