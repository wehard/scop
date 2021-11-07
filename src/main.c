/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/07 14:03:31 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "obj_loader.h"
#include "scop.h"

#include "obj_loader.h"
#include "shader.h"

#include "ft_printf.h"
#include <math.h>
#include "tex.h"

GLFWwindow	*init_gl(t_env *env)
{
	GLFWwindow *window;

	if (!glfwInit())
	{
		exit_message("glfwInit failed!");
	}
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

	glfwSetWindowUserPointer(window, env);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return (window);
}

void	init_env(t_env *env)
{
	env->wireframe = 0;
	env->mouse_last_x = WIN_W / 2;
	env->mouse_last_y = WIN_H / 2;
	env->mouse_sensitivity = 0.1f;
	env->proj_matrix = mat4_perspective(45.0, (float)WIN_W / (float)WIN_H, 0.1, 100.0);
	env->delta_time = 0.0;
	env->last_time = 0.0;
}

int	main(int argc, char *argv[])
{
	t_env env;
	GLFWwindow *window;
	t_mesh *mesh;
	t_entity *entity;
	t_camera c;

	srand((unsigned)4);

	if (argc != 1)
	{
		exit_message("./scop [obj]");
		return (EXIT_FAILURE);
	}

	init_env(&env);

	window = init_gl(&env);
	t_shader *basic = shader_create("./shaders/default.vert", "./shaders/grey.frag");
	mesh = obj_load("./objs/teapot.obj");
	entity = entity_create(mesh, basic);
	entity->tex = tex_load("./textures/texture.jpg");
	entity->scale = ft_make_vec3(5, 5, 5);

	camera_init(&c, ft_make_vec3(0, 10, 45), ft_make_vec3(0, -0.3, -1), ft_make_vec2(-90.0, 0.0));

	env.camera = &c;

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		float current_time = glfwGetTime();
		env.delta_time = current_time - env.last_time;
		env.last_time = current_time;

		camera_update(env.camera);

		glClearColor(0.4, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetKey(window, GLFW_KEY_W))
			env.camera->position = ft_add_vec3(env.camera->position, ft_mul_vec3(env.camera->forward, 20.0 * env.delta_time));
		if (glfwGetKey(window, GLFW_KEY_S))
			env.camera->position = ft_sub_vec3(env.camera->position, ft_mul_vec3(env.camera->forward, 20.0 * env.delta_time));
		if (glfwGetKey(window, GLFW_KEY_A))
			env.camera->position = ft_sub_vec3(env.camera->position, ft_mul_vec3(env.camera->right, 20.0 * env.delta_time));
		if (glfwGetKey(window, GLFW_KEY_D))
			env.camera->position = ft_add_vec3(env.camera->position, ft_mul_vec3(env.camera->right, 20.0 * env.delta_time));

		entity->rotation.y += 50.0 * env.delta_time;

		if (env.wireframe)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-0.5, 0.5);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			entity_draw(&env, entity);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		else
		{
			entity_draw(&env, entity);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader_destroy(basic);
	mesh_destroy(mesh);

	free(entity->tex);
	free(entity);

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
