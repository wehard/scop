/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/26 13:43:34 by wkorande         ###   ########.fr       */
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

int		main(int argc, char const *argv[])
{
	if (!glfwInit())
	{
		
		return (EXIT_FAILURE);
	}
	if (argc != 2)
		return (EXIT_FAILURE);

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
	c.position = ft_make_vec3(0,0,10);

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		draw_entity(&c, e);

		if (glfwGetKey(window, GLFW_KEY_UP))
			c.position.z -= 0.0001;
		if (glfwGetKey(window, GLFW_KEY_DOWN))
			c.position.z += 0.0001;
		if (glfwGetKey(window, GLFW_KEY_LEFT))
			c.position.x -= 0.0001;
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
			c.position.x += 0.0001;

		ft_printf("z: %.4f\n", c.position.z);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	destroy_shader(s);
	mesh_destroy(m);

	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
