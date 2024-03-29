/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:18:25 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/21 15:56:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include "libft_light.h"

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

void	toggle_help(t_env *env)
{
	t_key_state	key_state;

	key_state.i = glfwGetKey(env->window, GLFW_KEY_I);
	if (key_state.i == GLFW_PRESS && env->key_states.i != GLFW_PRESS)
	{
		env->help = !env->help;
	}
	env->key_states.i = key_state.i;
}

void	toggle_wireframe(t_env *env)
{
	t_key_state	key_state;

	key_state.y = glfwGetKey(env->window, GLFW_KEY_Y);
	if (key_state.y == GLFW_PRESS && env->key_states.y != GLFW_PRESS)
	{
		env->wireframe = !env->wireframe;
	}
	env->key_states.y = key_state.y;
}

static void	toggle_used_shader_ex(t_env *env)
{
	t_key_state	key_state;

	key_state.three = glfwGetKey(env->window, GLFW_KEY_3);
	if (key_state.three == GLFW_PRESS && env->key_states.three != GLFW_PRESS)
	{
		if (env->shader_current != env->shader_frac)
			env->shader_current = env->shader_frac;
		else
			env->shader_current = env->shader_grey;
	}
	env->key_states.three = key_state.three;
}

void	toggle_used_shader(t_env *env)
{
	t_key_state	key_state;

	key_state.one = glfwGetKey(env->window, GLFW_KEY_1);
	if (key_state.one == GLFW_PRESS && env->key_states.one != GLFW_PRESS)
	{
		if (env->shader_current != env->shader_tex)
			env->shader_current = env->shader_tex;
		else
			env->shader_current = env->shader_grey;
	}
	env->key_states.one = key_state.one;
	key_state.two = glfwGetKey(env->window, GLFW_KEY_2);
	if (key_state.two == GLFW_PRESS && env->key_states.two != GLFW_PRESS)
	{
		if (env->shader_current != env->shader_norm)
			env->shader_current = env->shader_norm;
		else
			env->shader_current = env->shader_grey;
	}
	env->key_states.two = key_state.two;
	toggle_used_shader_ex(env);
}
