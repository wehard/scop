/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:16:24 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/06 17:24:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include "ft_get_next_line.h"
#include <GL/glew.h>
#include <stdio.h>
#include <errno.h>

static char *load_shader_src(const char *src_path)
{
	int fd;
	char *src;
	char *line;

	fd = open(src_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("load_shader_src: %s %s\n", src_path, strerror(errno));
		exit(EXIT_FAILURE);
	}
	src = (char *)malloc(MAX_SHADER_SRC_SIZE);
	ft_bzero(src, MAX_SHADER_SRC_SIZE);
	while (ft_get_next_line(fd, &line))
	{
		src = ft_strcat(src, line);
		src = ft_strcat(src, "\n");
		free(line);
	}
	close(fd);
	return (src);
}

static uint32_t compile_shader(char *src, GLenum shader_type)
{
	uint32_t shader_id;
	GLint status;
	GLint log_len;
	char *error;

	shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, (const char **)&src, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		error = (char *)malloc(sizeof(char) * log_len);
		glGetShaderInfoLog(shader_id, log_len, NULL, error);
		if (shader_type == GL_FRAGMENT_SHADER)
		{
			ft_printf("%s: %s\n", "frag", error);
		}
		else
		{
			ft_printf("%s: %s\n", "vert", error);
		}
	}
	return (shader_id);
}

t_shader *shader_create(const char *vert_path, const char *frag_path)
{
	t_shader *shader;

	shader = (t_shader *)malloc(sizeof(t_shader));
	if (!shader)
	{
		ft_printf("Failed to load shader!\n");
		exit(EXIT_FAILURE);
	}
	shader->vert_src = load_shader_src(vert_path);
	shader->frag_src = load_shader_src(frag_path);
	shader->vert_id = compile_shader(shader->vert_src, GL_VERTEX_SHADER);
	shader->frag_id = compile_shader(shader->frag_src, GL_FRAGMENT_SHADER);
	shader->program_id = glCreateProgram();
	glAttachShader(shader->program_id, shader->vert_id);
	glAttachShader(shader->program_id, shader->frag_id);
	glLinkProgram(shader->program_id);
	glDeleteShader(shader->vert_id);
	glDeleteShader(shader->frag_id);
	return (shader);
}

void shader_use(t_shader *shader)
{
	if (!shader)
		return;
	glUseProgram(shader->program_id);
}
