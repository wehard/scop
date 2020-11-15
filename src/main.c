/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/15 19:29:05 by wkorande         ###   ########.fr       */
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

// int		on_render(void *param)
// {
// 	return (0);
// }

void	exit_message(const char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void    free_null(size_t count, ...)
{
        va_list pl;
        size_t  i;
        void    *param_type;

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	t_env *env;
	
	env = (t_env*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		ft_printf("%f, %f\n", env->camera->pitch, env->camera->yaw);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	t_env *env;
	float xoffset;
	float yoffset;
	
	env = (t_env*)glfwGetWindowUserPointer(window);
	xoffset = (xpos-env->mouse_last_x) * env->mouse_sensitivity;
	yoffset = (env->mouse_last_y - ypos) * env->mouse_sensitivity;

	env->camera->yaw += xoffset;
	env->camera->pitch += yoffset;

	if(env->camera->pitch > 89.0f)
        env->camera->pitch = 89.0f;
    if(env->camera->pitch < -89.0f)
        env->camera->pitch = -89.0f;

	t_vec3 dir;
	dir.x = cosf(ft_deg_to_rad(env->camera->yaw)) * cosf(ft_deg_to_rad(env->camera->pitch));
	dir.y = sinf(ft_deg_to_rad(env->camera->pitch));
	dir.z = sinf(ft_deg_to_rad(env->camera->yaw)) * cosf(ft_deg_to_rad(env->camera->pitch));

	env->camera->forward = (ft_normalize_vec3(dir));
	env->camera->right = ft_cross_vec3(env->camera->forward, ft_make_vec3(0,1,0));
	env->mouse_last_x = xpos;
	env->mouse_last_y = ypos;
	ft_printf("forward %.4f %.4f %.4f\n", env->camera->forward.x, env->camera->forward.y, env->camera->forward.z);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	t_env *env;
	
	env = (t_env*)glfwGetWindowUserPointer(window);
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
	ft_printf("camera %.4f %.4f %.4f\n", env->camera->position.x, env->camera->position.y, env->camera->position.z);
}

void init_matrices(t_entity *entity)
{
	size_t i = 0;
	float angle = 0;
	while (i < entity->instance_count)
	{
		entity->position[i].x = (cosf(ft_deg_to_rad(angle)) * 40) + (float)(rand() % 30) - 15;
		entity->position[i].y = 2.5 - rand() % 5;
		entity->position[i].z = (sinf(ft_deg_to_rad(angle)) * 40) + (float)(rand() % 30) - 15;
		angle += 360.0 / entity->instance_count;
		entity->rotation[i] = ft_make_vec3(0.0, (float)(rand()%360), 0.0);
		entity->scale[i] = ft_make_vec3(0.1, 0.1, 0.1);
		entity->model_matrix[i] = mat4_trs(entity->position[i], entity->rotation[i], entity->scale[i]);
		i++;
	}
}

int		main(int argc, char const *argv[])
{
	t_env env;
	env.mouse_last_x = WIN_W / 2;
	env.mouse_last_y = WIN_H / 2;
	env.mouse_sensitivity = 0.1f;
	srand((unsigned)4);
	if (!glfwInit())
	{
		return (EXIT_FAILURE);
	}
	if (argc != 2)
		return (EXIT_FAILURE);

	env.wireframe = 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(WIN_W, WIN_H, "env", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return (EXIT_FAILURE);

	t_shader *basic = create_shader("resources/basic.vert", "resources/basic.frag");
	t_shader *instanced = create_shader("resources/instanced.vert", "resources/instanced.frag");

	t_mesh *teapot = obj_load(argv[1]);
	t_entity *entity = entity_create(teapot, basic);
	t_entity *entity_instanced = entity_create_instanced(teapot, instanced, 5000);

	entity->scale[0] = ft_make_vec3(5,5,5);

	init_matrices(entity_instanced);
	entity_update_buffers(entity_instanced);
	
	t_camera c;
	camera_init(&c, ft_make_vec3(0, 10, 45), ft_make_vec3(0, -0.3, -1), -90.0, 0.0);
	
	env.camera = &c;
	env.shader_basic = basic;
	env.shader_instanced = instanced;

	env.proj_matrix =  mat4_perspective(45.0, (float)WIN_W / (float)WIN_H, 0.1, 100.0);

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
		
		glClearColor(0.7, 0.4, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetKey(window, GLFW_KEY_W))
			env.camera->position = ft_add_vec3(env.camera->position, ft_mul_vec3(env.camera->forward, 0.3));
		if (glfwGetKey(window, GLFW_KEY_S))
			env.camera->position = ft_sub_vec3(env.camera->position, ft_mul_vec3(env.camera->forward, 0.3));
		if (glfwGetKey(window, GLFW_KEY_A))
			env.camera->position = ft_sub_vec3(env.camera->position, ft_mul_vec3(env.camera->right, 0.3));
		if (glfwGetKey(window, GLFW_KEY_D))
			env.camera->position = ft_add_vec3(env.camera->position, ft_mul_vec3(env.camera->right, 0.3));

		if (env.wireframe)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-0.5, 0.5);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			entity_draw(&env, entity);
			entity_draw_instanced(&env, entity_instanced);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		else
		{
			entity_draw(&env, entity);
			entity_draw_instanced(&env, entity_instanced);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	destroy_shader(basic);
	destroy_shader(instanced);
	mesh_destroy(teapot);

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
