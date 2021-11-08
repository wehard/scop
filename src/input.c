/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:18:25 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:45:58 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include "libft_light.h"

void	mouse_button_callback(GLFWwindow *window, int button,
	int action, int mods)
{
	t_env	*env;

	mods = 0;
	env = (t_env *)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		if (env->shader_current == env->shader_grey)
			env->shader_current = env->shader_tex;
		else
			env->shader_current = env->shader_grey;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		env->wireframe = !env->wireframe;
	}
}

void	mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_env	*env;
	float	xoffset;
	float	yoffset;
	t_vec3	dir;

	env = (t_env *)glfwGetWindowUserPointer(window);
	xoffset = (xpos - env->mouse_last_x) * env->mouse_sensitivity;
	yoffset = (env->mouse_last_y - ypos) * env->mouse_sensitivity;
	env->camera.yaw += xoffset;
	env->camera.pitch += yoffset;
	if (env->camera.pitch > 89.0f)
		env->camera.pitch = 89.0f;
	if (env->camera.pitch < -89.0f)
		env->camera.pitch = -89.0f;
	dir.x = cosf(ft_deg_to_rad(env->camera.yaw))
		* cosf(ft_deg_to_rad(env->camera.pitch));
	dir.y = sinf(ft_deg_to_rad(env->camera.pitch));
	dir.z = sinf(ft_deg_to_rad(env->camera.yaw))
		* cosf(ft_deg_to_rad(env->camera.pitch));
	env->camera.forward = (ft_normalize_vec3(dir));
	env->camera.right = ft_cross_vec3(env->camera.forward,
			ft_make_vec3(0, 1, 0));
	env->mouse_last_x = xpos;
	env->mouse_last_y = ypos;
}
