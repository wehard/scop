/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/09 09:18:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft_light.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "obj_loader.h"
#include "scop.h"
#include "shader.h"
#include <math.h>
#include "tex.h"

static void	set_draw_mode(t_env *env)
{
	if (env->wireframe)
	{
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(-0.5, 0.5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glDisable(GL_POLYGON_OFFSET_LINE);
	}
}

static void	update(t_env *env)
{
	float	current_time;

	current_time = glfwGetTime();
	env->delta_time = current_time - env->last_time;
	env->last_time = current_time;
	camera_update(env, &env->camera);
	env->entity->rotation.y += 50.0 * env->delta_time;
}

static void	render(t_env *env)
{
	glClearColor(0.4, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	set_draw_mode(env);
	entity_draw(env, env->entity, env->shader_current);
	glfwSwapBuffers(env->window);
	glfwPollEvents();
}

void	cleanup(t_env *env)
{
	env->shader_current = 0;
	shader_destroy(env->shader_grey);
	shader_destroy(env->shader_tex);
	free(env->entity->tex);
	mesh_destroy(env->entity->mesh);
	free(env->entity);
}

int	main(int argc, char *argv[])
{
	t_env		env;

	if (argc != 2)
	{
		exit_message("./scop [obj]");
		return (EXIT_FAILURE);
	}
	if (!verify_ext(argv[1], ".obj"))
		exit_message("Check .obj filename!");
	init_env(&env);
	init_env_entity(&env, argv[1]);
	while (!glfwWindowShouldClose(env.window)
		&& glfwGetKey(env.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		update(&env);
		render(&env);
	}
	glfwDestroyWindow(env.window);
	cleanup(&env);
	glfwTerminate();
	return (0);
}
