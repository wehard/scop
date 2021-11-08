/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:14:54 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:34:07 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "obj_loader.h"
#include "tex.h"

static GLFWwindow	*init_gl(void)
{
	GLFWwindow	*window;

	if (!glfwInit())
		exit_message("glfwInit failed!");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	window = glfwCreateWindow(WIN_W, WIN_H, "scop", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		exit_message("glewInit failed!");
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glEnable(GL_DEPTH_TEST);
	return (window);
}

void	load_shaders(t_env *env)
{
	env->shader_grey = shader_create(
			"resources/shaders/grey.vert",
			"resources/shaders/grey.frag");
	env->shader_tex = shader_create(
			"./resources/shaders/textured.vert",
			"./resources/shaders/textured.frag");
	env->shader_current = env->shader_grey;
}

void	init_env(t_env *env)
{
	env->wireframe = 0;
	env->mouse_last_x = WIN_W / 2;
	env->mouse_last_y = WIN_H / 2;
	env->mouse_sensitivity = 0.1f;
	env->proj_matrix = mat4_perspective(45.0,
			(float)WIN_W / (float)WIN_H, 0.1, 100.0);
	env->delta_time = 0.0;
	env->last_time = 0.0;
	camera_init(&env->camera, ft_make_vec3(0, 10, 45),
		ft_make_vec3(0, -0.3, -1), ft_make_vec2(-90.0, 0.0));
	env->shader_current = NULL;
	env->shader_grey = NULL;
	env->shader_grey = NULL;
	env->window = init_gl();
	glfwSetWindowUserPointer(env->window, env);
	load_shaders(env);
}

void	init_env_entity(t_env *env, const char *filename)
{
	t_mesh	*mesh;

	mesh = obj_load(filename);
	env->entity = entity_create(mesh);
	env->entity->tex = tex_load("./resources/textures/texture.png");
	env->entity->scale = ft_make_vec3(5, 5, 5);
}
