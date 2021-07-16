/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:16:24 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 17:08:14 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include <GL/glew.h>

void shader_set_uniform_mat4(t_shader *shader, char *loc_name, t_mat4 m)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&m.data[0]);
}

void shader_set_uniform_vec3(t_shader *shader, char *loc_name, t_vec3 v)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniform3fv(location, 1, (GLfloat*)&v);
}

void shader_set_uniform_vec4(t_shader *shader, char *loc_name, t_vec4 v)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void shader_set_uniform_vec3_array(t_shader *shader, char *loc_name, t_vec3 *v, size_t count)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniform3fv(location, count, (GLfloat*)&v[0]);
}

void shader_set_uniform_vec4_array(t_shader *shader, char *loc_name, t_vec4 *v, size_t count)
{
	GLuint location = glGetUniformLocation(shader->program_id, loc_name);
	glUniform4fv(location, count, (GLfloat*)&v[0]);
}
