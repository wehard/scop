/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 19:32:17 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/20 18:28:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdlib.h>
# include <stdint.h>
# include "vec3.h"
# include "vec4.h"
# include "vec2.h"
# include "mat4.h"
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# define WIN_W 1920
# define WIN_H 1080

struct	s_mesh;
struct	s_shader;
struct	s_tex;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		forward;
	t_vec3		right;
	float		pitch;
	float		yaw;
	t_mat4		view_matrix;
}				t_camera;

typedef struct s_entity
{
	struct s_mesh	*mesh;
	struct s_tex	*tex;
	t_vec3			position;
	t_vec3			scale;
	t_vec3			rotation;
	uint32_t		vao_id;
	uint32_t		vbo_id;
	uint32_t		ebo_id;
	uint32_t		mbo_id;
	uint32_t		uvbo_id;
	t_mat4			model_matrix;

}				t_entity;

typedef struct s_key_state
{
	int			i;
	int			one;
	int			two;
	int			three;
}				t_key_state;

typedef struct s_env
{
	struct s_shader	*shader_current;
	struct s_shader	*shader_grey;
	struct s_shader	*shader_tex;
	int				wireframe;
	int				help;
	t_camera		camera;
	t_entity		*entity;
	t_entity		*entity_help;
	float			mouse_last_x;
	float			mouse_last_y;
	float			mouse_sensitivity;
	float			delta_time;
	float			last_time;
	t_mat4			proj_matrix;
	GLFWwindow		*window;
	t_key_state		key_states;
}				t_env;

void		init_env(t_env *env);
void		load_shaders(t_env *env);
void		init_env_entity(t_env *env, const char *filename);

t_entity	*entity_create(struct s_mesh *mesh);
void		entity_draw(t_env *env, t_entity *entity, struct s_shader *shader);

void		entity_update_buffers(t_entity *entity);

void		camera_init(t_camera *camera, t_vec3 pos,
				t_vec3 forward, t_vec2 yaw_pitch);
void		camera_update(t_env *env, t_camera *camera);

void		mouse_button_callback(GLFWwindow *window, int button,
				int action, int mods);
void		mouse_callback(GLFWwindow *window, double xpos, double ypos);

void		exit_message(const char *message);
void		free_null(size_t count, ...);
void		free_parts(char **parts);
int			verify_ext(const char *filename, const char *extension);
int			ft_open(const char *file, int oflags);

void		toggle_help(t_env *env);
void		toggle_used_shader(t_env *env);

#endif
