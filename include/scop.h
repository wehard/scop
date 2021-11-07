/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:32:17 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/07 14:09:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdint.h>
#include "vec3.h"
#include "vec4.h"
#include "vec2.h"
#include "mat4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

# define WIN_W 1920
# define WIN_H 1080

struct s_mesh;
struct s_shader;
struct s_tex;

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
	struct s_tex *tex;
	struct s_shader *shader;
	t_vec3		position;
	t_vec3		scale;
	t_vec3		rotation;
	uint32_t	vao_id;
	uint32_t	vbo_id;
	uint32_t	ebo_id;
	uint32_t	mbo_id;
	uint32_t	uvbo_id;
	t_mat4		model_matrix;

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
	float		last_time;
	t_mat4		proj_matrix;
}				t_env;

void	exit_message(const char *message);
void    free_null(size_t count, ...);

t_entity	*entity_create(struct s_mesh *mesh, struct s_shader *shader);
t_entity	*entity_create_instanced(struct s_mesh *mesh, struct s_shader *shader, size_t instance_count);
void		entity_draw(t_env *env, t_entity *entity);

void entity_update_buffers(t_entity *entity);

void camera_init(t_camera *camera, t_vec3 pos, t_vec3 forward, t_vec2 yaw_pitch);
void camera_update(t_camera *camera);

void	mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void	mouse_callback(GLFWwindow *window, double xpos, double ypos);

void	exit_message(const char *message);
void	free_null(size_t count, ...);

#endif
