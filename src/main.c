/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2020/10/24 20:33:41 by wkorande         ###   ########.fr       */
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
	t_scop *scop;
	
	scop = (t_scop*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		ft_printf("%f, %f\n", scop->camera->pitch, scop->camera->yaw);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	t_scop *scop;
	float xoffset;
	float yoffset;
	
	scop = (t_scop*)glfwGetWindowUserPointer(window);
	xoffset = (xpos-scop->mouse_last_x) * scop->mouse_sensitivity;
	yoffset = (scop->mouse_last_y - ypos) * scop->mouse_sensitivity;

	scop->camera->yaw += xoffset;
	scop->camera->pitch += yoffset;

	if(scop->camera->pitch > 89.0f)
        scop->camera->pitch = 89.0f;
    if(scop->camera->pitch < -89.0f)
        scop->camera->pitch = -89.0f;

	t_vec3 dir;
	dir.x = cosf(ft_deg_to_rad(scop->camera->yaw)) * cosf(ft_deg_to_rad(scop->camera->pitch));
	dir.y = sinf(ft_deg_to_rad(scop->camera->pitch));
	dir.z = sinf(ft_deg_to_rad(scop->camera->yaw)) * cosf(ft_deg_to_rad(scop->camera->pitch));

	scop->camera->forward = (ft_normalize_vec3(dir));
	scop->mouse_last_x = xpos;
	scop->mouse_last_y = ypos;
	ft_printf("forward %.4f %.4f %.4f\n", scop->camera->forward.x, scop->camera->forward.y, scop->camera->forward.z);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	t_scop *scop;
	
	scop = (t_scop*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		scop->wireframe = !scop->wireframe;
	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
		scop->camera->position.z -= 0.1;
	if (key == GLFW_KEY_S && action == GLFW_REPEAT)
		scop->camera->position.z += 0.1;
	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
		scop->camera->position.x -= 0.1;
	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
		scop->camera->position.x += 0.1;
	ft_printf("camera %.4f %.4f %.4f\n", scop->camera->position.x, scop->camera->position.y, scop->camera->position.z);
}

int		main(int argc, char const *argv[])
{
	t_scop scop;
	scop.mouse_last_x = 1280 / 2;
	scop.mouse_last_y = 720 / 2;
	scop.mouse_sensitivity = 0.1f;
	
	if (!glfwInit())
	{
		return (EXIT_FAILURE);
	}
	if (argc != 2)
		return (EXIT_FAILURE);

	scop.wireframe = 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(1280, 720, "scop", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return (EXIT_FAILURE);

	t_shader *s = create_shader("resources/basic.vert", "resources/basic.frag");
	t_mesh *m = obj_load(argv[1]);
	t_entity *e = create_entity(m, s);
	t_camera c;
	c.position = ft_make_vec3(0, 0, 5);
	c.forward = ft_make_vec3(0,0, -1);
	c.yaw = -90.0;
	c.pitch = 0.0;
	
	scop.entity = e;
	scop.camera = &c;

	glfwSetWindowUserPointer(window, &scop);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	float last_time = 0.0;
	scop.delta_time = 0.0;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		float current_time = glfwGetTime();
		scop.delta_time = current_time - last_time;
		last_time = current_time;
		
		glClearColor(0.7, 0.4, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		e->rotation.y += scop.delta_time * 40.0;
		entity_draw(&c, e, (t_vec4){0.2, 0.2, 0.8, 1.0});

		if (scop.wireframe)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonOffset(-0.5, 0.5);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			entity_draw(&c, e, (t_vec4){1, 1, 1, 1.0});
			glDisable(GL_POLYGON_OFFSET_LINE);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	destroy_shader(s);
	mesh_destroy(m);

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
