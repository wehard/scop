/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:58:39 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/06 18:02:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>

#include "scop.h"
#include "mesh.h"
#include "shader.h"
#include <math.h>
#include "libft.h"
#include "tex.h"

static void	gen_buffers(t_entity *entity)
{
	glGenVertexArrays(1, &entity->vao_id);
	glGenBuffers(1, &entity->vbo_id);
	glGenBuffers(1, &entity->ebo_id);
	glGenBuffers(1, &entity->mbo_id);

	glGenBuffers(1, &entity->uvbo_id);
}

static void init_buffers(t_entity *entity)
{
	size_t i;

	glBindVertexArray(entity->vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo_id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, entity->uvbo_id);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// if (entity->instance_count > 1)
	// {
	// 	glBindBuffer(GL_ARRAY_BUFFER, entity->mbo_id);
	// 	i = 0;
	// 	while (i < 4)
	// 	{
	// 		glEnableVertexAttribArray(i + 1);
	// 		glVertexAttribPointer(i + 1, 4, GL_FLOAT, GL_FALSE, sizeof(t_mat4), (void*)(i * sizeof(t_vec4)));
	// 		glVertexAttribDivisor(i + 1, 1);
	// 		i++;
	// 	}
	// }
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void entity_update_buffers(t_entity *entity)
{
	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * entity->mesh->num_vertices * 3, entity->mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, entity->uvbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * entity->mesh->num_uvs * 2, entity->mesh->uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * entity->mesh->num_indices, entity->mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, entity->mbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_mat4), &entity->model_matrix, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

t_entity	*entity_create(t_mesh *mesh, t_shader *shader)
{
	t_entity *entity;
	size_t		i;

	if (!(entity = (t_entity*)malloc(sizeof(t_entity))))
		exit_message("Failed to malloc entity!");

	entity->vao_id = -1;
	entity->vbo_id = -1;
	entity->ebo_id = -1;
	entity->mbo_id = -1;
	entity->tex = NULL;

	entity->position = ft_make_vec3(0.0, 0.0, 0.0);
	entity->rotation = ft_make_vec3(0.0, 0.0, 0.0);
	entity->scale = ft_make_vec3(1.0, 1.0, 1.0);
	entity->model_matrix = mat4_trs(entity->position, entity->rotation, entity->scale);

	entity->mesh = mesh;
	entity->shader = shader;
	gen_buffers(entity);
	init_buffers(entity);
	entity_update_buffers(entity);
	return (entity);
}

void		entity_destroy(t_entity *entity)
{
	free(entity);
}

void		entity_draw(t_env *env, t_entity *entity)
{
	shader_use(entity->shader);
	tex_bind(entity->tex);

	shader_set_uniform_mat4(entity->shader, "model_matrix", mat4_trs(entity->position, entity->rotation, entity->scale));
	shader_set_uniform_mat4(entity->shader, "view_matrix", env->camera->view_matrix);
	shader_set_uniform_mat4(entity->shader, "proj_matrix", env->proj_matrix);
	shader_set_uniform_vec4(entity->shader, "color", (t_vec4){0.3, 0.2, 0.5, 1.0});

	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElements(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0);
	tex_bind(0);
	shader_use(0);
}
