/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:14:54 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/20 18:50:07 by wkorande         ###   ########.fr       */
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
			"res/shaders/grey.vert",
			"res/shaders/grey.frag");
	env->shader_tex = shader_create(
			"res/shaders/textured.vert",
			"res/shaders/textured.frag");
	env->shader_norm = shader_create(
			"res/shaders/normals.vert",
			"res/shaders/normals.frag");
	env->shader_current = env->shader_grey;
}

static void	init_env_help_entity(t_env *env)
{
	t_mesh	*mesh;

	mesh = mesh_create();
	mesh_create_verts(mesh, 4);
	mesh_create_indices(mesh, 6);
	mesh_create_uvs(mesh, 4);
	mesh->vertices[0] = ft_make_vec3(-1, -1, 0);
	mesh->vertices[1] = ft_make_vec3(-1, 1, 0);
	mesh->vertices[2] = ft_make_vec3(1, 1, 0);
	mesh->vertices[3] = ft_make_vec3(1, -1, 0);
	mesh->indices[0] = 0;
	mesh->indices[1] = 1;
	mesh->indices[2] = 2;
	mesh->indices[3] = 2;
	mesh->indices[4] = 3;
	mesh->indices[5] = 0;
	mesh->uvs[0] = ft_make_vec2(0, 0);
	mesh->uvs[1] = ft_make_vec2(0, 1);
	mesh->uvs[2] = ft_make_vec2(1, 1);
	mesh->uvs[3] = ft_make_vec2(1, 0);
	env->entity_help = entity_create(mesh);
	env->entity_help->tex = tex_load("res/textures/instructions.png");
	env->entity_help->position = ft_make_vec3(0, 0, -15);
	env->entity_help->scale = ft_make_vec3(20, 20, 20);
	env->entity_help->rotation = ft_make_vec3(0, 180, 180);
}

void	init_env(t_env *env)
{
	env->wireframe = 0;
	env->help = 0;
	env->mouse_last_x = WIN_W / 2;
	env->mouse_last_y = WIN_H / 2;
	env->mouse_sensitivity = 0.1f;
	env->proj_matrix = mat4_perspective(45.0,
			(float)WIN_W / (float)WIN_H, 0.1, 100.0);
	env->delta_time = 0.0;
	env->last_time = 0.0;
	camera_init(&env->camera, ft_make_vec3(0, 0, 30),
		ft_make_vec3(0, 0, -1), ft_make_vec2(-90.0, 0.0));
	env->shader_current = NULL;
	env->shader_grey = NULL;
	env->shader_grey = NULL;
	env->window = init_gl();
	glfwSetWindowUserPointer(env->window, env);
	glfwSetInputMode(env->window, GLFW_STICKY_KEYS, GLFW_TRUE);
	load_shaders(env);
	init_env_help_entity(env);
}

void	init_env_entity(t_env *env, const char *filename)
{
	t_mesh	*mesh;

	mesh = obj_load(filename);
	env->entity = entity_create(mesh);
	env->entity->tex = tex_load("res/textures/unicorn.png");
	env->entity->scale = ft_make_vec3(5, 5, 5);
}
