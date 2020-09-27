/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:16:24 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/27 12:24:31 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include "ft_get_next_line.h"
#include <GL/glew.h>
// #include "matrix.h"

static char *load_shader_src(char *src_path)
{
	int fd;
	char *src;
	char *line;

	fd = open(src_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Failed to read shader file!\n");
		exit(EXIT_FAILURE);
	}
	src = (char*)malloc(MAX_SHADER_SRC_SIZE);
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
	glShaderSource(shader_id, 1, (const char**)&src, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		error = (char*)malloc(sizeof(char) * log_len);
		glGetShaderInfoLog(shader_id, log_len, NULL, error);
		ft_printf("%s: %s\n", shader_type == GL_FRAGMENT_SHADER ? "frag" : "vert", error);
	}

	return (shader_id);
}


t_shader *create_shader(char *vert_path, char *frag_path)
{
	t_shader *shader;

	if (!(shader = (t_shader*)malloc(sizeof(t_shader))))
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

void destroy_shader(t_shader *shader)
{
	glDeleteProgram(shader->program_id);
	free(shader->vert_src);
	free(shader->frag_src);
	free(shader);
}

void shader_set_uniform_mat4(t_shader *shader, char *loc_name, t_mat4 m)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&m.data[0]);
}

void shader_set_uniform_vec3(t_shader *shader, char *loc_name, t_vec3 v)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniform3f(location, v.x, v.y, v.z);
}

void shader_set_uniform_vec4(t_shader *shader, char *loc_name, t_vec4 v)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}
