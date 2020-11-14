/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:32:17 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/14 21:17:44 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdint.h>
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

# define WIN_W 1280
# define WIN_H 720

struct s_mesh;
struct s_shader;

typedef struct	s_camera
{
	t_vec3		position;
	t_vec3		forward;
	t_vec3		right;
	float		pitch;
	float		yaw;
	t_mat4		view_matrix;
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
	size_t		instance_count;
}				t_entity;

typedef struct	s_env
{
	int			wireframe;
	t_camera	*camera;
	t_entity	*entity;
	float		mouse_last_x;
	float		mouse_last_y;
	float		mouse_sensitivity;
	float		delta_time;
	t_mat4		proj_matrix;
	struct s_shader	*shader_instanced;
	struct s_shader	*shader_basic;
}				t_env;

void	exit_message(const char *message);
void    free_null(size_t count, ...);

t_entity	*create_entity(struct s_mesh *mesh, struct s_shader *shader);
void		entity_draw(t_camera *camera, t_entity *entity, t_vec4 color);
void		entity_draw_instanced(t_env *env, t_entity *entity, size_t count);

void camera_init(t_camera *camera, t_vec3 pos, t_vec3 forward, float yaw, float pitch);
void camera_update(t_camera *camera);

#endif
