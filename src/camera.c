/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:25:47 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/07 16:06:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "vec2.h"

static void	camera_update_view_matrix(t_camera *camera)
{
	camera->view_matrix = mat4_lookat(camera->position,
			ft_add_vec3(camera->position, camera->forward),
			ft_make_vec3(0, 1, 0));
}

void	camera_update(t_env *env, t_camera *camera)
{
	if (glfwGetKey(env->window, GLFW_KEY_W))
		env->camera.position = ft_add_vec3(env->camera.position,
				ft_mul_vec3(env->camera.forward, 20.0 * env->delta_time));
	if (glfwGetKey(env->window, GLFW_KEY_S))
		env->camera.position = ft_sub_vec3(env->camera.position,
				ft_mul_vec3(env->camera.forward, 20.0 * env->delta_time));
	if (glfwGetKey(env->window, GLFW_KEY_A))
		env->camera.position = ft_sub_vec3(env->camera.position,
				ft_mul_vec3(env->camera.right, 20.0 * env->delta_time));
	if (glfwGetKey(env->window, GLFW_KEY_D))
		env->camera.position = ft_add_vec3(env->camera.position,
				ft_mul_vec3(env->camera.right, 20.0 * env->delta_time));
	camera_update_view_matrix(camera);
}

void	camera_init(t_camera *camera, t_vec3 pos, t_vec3 forward,
			t_vec2 yaw_pitch)
{
	if (!camera)
		return ;
	camera->position = pos;
	camera->forward = forward;
	camera->yaw = yaw_pitch.x;
	camera->pitch = yaw_pitch.y;
	camera_update_view_matrix(camera);
}
