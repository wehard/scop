/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/06 18:03:44 by wkorande         ###   ########.fr       */
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
#include <stdarg.h>
#include "obj_loader.h"
#include "shader.h"
#include <stdlib.h>
#include "ft_printf.h"
#include <math.h>
#include "tex.h"

void exit_message(const char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void free_null(size_t count, ...)
{
	va_list pl;
	size_t i;
	void *param_type;

	i = 0;
	va_start(pl, count);
	while (i < count)
	{
		param_type = va_arg(pl, void *);
		free(param_type);
		param_type = NULL;
		i++;
	}
	va_end(pl);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	t_env *env;

	env = (t_env *)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		ft_printf("%f, %f\n", env->camera->pitch, env->camera->yaw);
	}
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_env *env;
	float xoffset;
	float yoffset;

	env = (t_env *)glfwGetWindowUserPointer(window);
	xoffset = (xpos - env->mouse_last_x) * env->mouse_sensitivity;
	yoffset = (env->mouse_last_y - ypos) * env->mouse_sensitivity;

	env->camera->yaw += xoffset;
	env->camera->pitch += yoffset;

	if (env->camera->pitch > 89.0f)
		env->camera->pitch = 89.0f;
	if (env->camera->pitch < -89.0f)
		env->camera->pitch = -89.0f;

	t_vec3 dir;
	dir.x = cosf(ft_deg_to_rad(env->camera->yaw)) * cosf(ft_deg_to_rad(env->camera->pitch));
	dir.y = sinf(ft_deg_to_rad(env->camera->pitch));
	dir.z = sinf(ft_deg_to_rad(env->camera->yaw)) * cosf(ft_deg_to_rad(env->camera->pitch));

	env->camera->forward = (ft_normalize_vec3(dir));
	env->camera->right = ft_cross_vec3(env->camera->forward, ft_make_vec3(0, 1, 0));
	env->mouse_last_x = xpos;
	env->mouse_last_y = ypos;
	// ft_printf("forward %.4f %.4f %.4f\n", env->camera->forward.x, env->camera->forward.y, env->camera->forward.z);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	t_env *env;

	env = (t_env *)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		env->wireframe = !env->wireframe;
	// if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	// 	env->camera->position = ft_add_vec3(env->camera->position, ft_mul_vec3(env->camera->forward, 0.3));
	// if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	// 	env->camera->position = ft_sub_vec3(env->camera->position, ft_mul_vec3(env->camera->forward, 0.3));
	// if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	// 	env->camera->position = ft_sub_vec3(env->camera->position, ft_mul_vec3(env->camera->right, 0.3));
	// if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	// 	env->camera->position = ft_add_vec3(env->camera->position, ft_mul_vec3(env->camera->right, 0.3));
	// ft_printf("camera %.4f %.4f %.4f\n", env->camera->position.x, env->camera->position.y, env->camera->position.z);
}

void init_matrices(t_entity *entity)
{
	size_t i = 0;
	float angle = 0;

	entity->position.x = (cosf(ft_deg_to_rad(angle)) * 40) + (float)(rand() % 30) - 15;
	entity->position.z = (sinf(ft_deg_to_rad(angle)) * 40) + (float)(rand() % 30) - 15;
	entity->position.y = 2.5 - rand() % 10 * (ft_len_vec2((t_vec2){entity->position.x, entity->position.z}) / 50.0);
	// angle += 360.0 / entity->instance_count;
	entity->rotation = ft_make_vec3((float)(rand() % 360), (float)(rand() % 360), (float)(rand() % 360));
	entity->scale = ft_make_vec3(0.3, 0.3, 0.3);
	entity->model_matrix = mat4_trs(entity->position, entity->rotation, entity->scale);
	i++;
}

int main(int argc, char *argv[])
{
	char buf[300];
	getcwd(buf, sizeof(buf));

	ft_printf("cwd: %s\n", buf);

	t_env env;
	env.mouse_last_x = WIN_W / 2;
	env.mouse_last_y = WIN_H / 2;
	env.mouse_sensitivity = 0.1f;
	srand((unsigned)4);
	if (!glfwInit())
	{
		return (EXIT_FAILURE);
	}
	if (argc != 1)
	{
		exit_message("./scop [obj]");
		return (EXIT_FAILURE);
	}

	env.wireframe = 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(WIN_W, WIN_H, "scop", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return (EXIT_FAILURE);

	t_shader *basic = shader_create("./shaders/default.vert", "./shaders/grey.frag");

	t_mesh *arg_mesh = obj_load("./objs/teapot.obj");
	t_entity *entity = entity_create(arg_mesh, basic);
	entity->tex = tex_load("./textures/texture.jpg");
	entity->scale = ft_make_vec3(5, 5, 5);

	t_camera c;
	camera_init(&c, ft_make_vec3(0, 10, 45), ft_make_vec3(0, -0.3, -1), -90.0, 0.0);

	env.camera = &c;
	env.shader_basic = basic;

	env.proj_matrix = mat4_perspective(45.0, (float)WIN_W / (float)WIN_H, 0.1, 100.0);

	glfwSetWindowUserPointer(window, &env);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	float last_time = 0.0;
	env.delta_time = 0.0;

	glEnable(GL_DEPTH_TEST);

	size_t i;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		float current_time = glfwGetTime();
		env.delta_time = current_time - last_time;
		last_time = current_time;

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

		entity->rotation.y += 10.0 * env.delta_time;

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
	mesh_destroy(arg_mesh);

	free(entity->tex);
	entity_destroy(entity);


	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
