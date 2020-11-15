/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:58:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/15 16:13:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>

#include "scop.h"
#include "mesh.h"
#include "shader.h"
#include <math.h>
#include "libft.h"

static void	gen_buffers(t_entity *entity)
{
	glGenVertexArrays(1, &entity->vao_id);
	glGenBuffers(1, &entity->vbo_id);
	glGenBuffers(1, &entity->ebo_id);
	glGenBuffers(1, &entity->mbo_id);
}

static void init_buffers(t_entity *entity)
{
	size_t i;

	glBindVertexArray(entity->vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo_id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	if (entity->instance_count > 1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, entity->mbo_id);
		i = 0;
		while (i < 4)
		{
			glEnableVertexAttribArray(i + 1);
			glVertexAttribPointer(i + 1, 4, GL_FLOAT, GL_FALSE, sizeof(t_mat4), (void*)(i * sizeof(t_vec4)));
			glVertexAttribDivisor(i + 1, 1);
			i++;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void entity_update_buffers(t_entity *entity)
{
	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * entity->mesh->num_vertices * 3, entity->mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * entity->mesh->num_indices, entity->mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, entity->mbo_id);
	glBufferData(GL_ARRAY_BUFFER, entity->instance_count * sizeof(t_mat4), entity->model_matrix, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

t_entity	*entity_create(t_mesh *mesh, t_shader *shader)
{
	t_entity *entity;
	entity = entity_create_instanced(mesh, shader, 1);
	return (entity);
}



t_entity	*entity_create_instanced(t_mesh *mesh, t_shader *shader, size_t instance_count)
{
	t_entity *entity;
	size_t		i;

	if (!(entity = (t_entity*)malloc(sizeof(t_entity))))
		exit_message("Failed to malloc entity!");
	entity->instance_count = instance_count;
	entity->position = malloc(sizeof(t_vec3) * instance_count);
	entity->rotation = malloc(sizeof(t_vec3) * instance_count);
	entity->scale = malloc(sizeof(t_vec3) * instance_count);
	entity->model_matrix = malloc(sizeof(t_mat4) * instance_count);
	entity->vao_id = -1;
	entity->vbo_id = -1;
	entity->ebo_id = -1;
	entity->mbo_id = -1;

	i = 0;
	while (i < instance_count)
	{
		entity->position[i] = ft_make_vec3(0.0, 0.0, 0.0);
		entity->rotation[i] = ft_make_vec3(0.0, 0.0, 0.0);
		entity->scale[i] = ft_make_vec3(1.0, 1.0, 1.0);
		entity->model_matrix[i] = mat4_trs(entity->position[i], entity->rotation[i], entity->scale[i]);
		i++;
	}
	
	entity->mesh = mesh;
	entity->shader = shader;
	gen_buffers(entity);
	init_buffers(entity);
	entity_update_buffers(entity);
	return (entity);
}

void		entity_draw(t_env *env, t_entity *entity)
{
	shader_use(env->shader_basic);
	
	shader_set_uniform_mat4(env->shader_basic, "model_matrix", mat4_trs(entity->position[0], entity->rotation[0], entity->scale[0]));
	shader_set_uniform_mat4(env->shader_basic, "view_matrix", env->camera->view_matrix);
	shader_set_uniform_mat4(env->shader_basic, "proj_matrix", env->proj_matrix);
	shader_set_uniform_vec4(env->shader_basic, "color", (t_vec4){0.3, 0.2, 0.5, 1.0});
	
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElements(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0);
	shader_use(0);
}

void	entity_draw_instanced(t_env *env, t_entity *entity)
{
	shader_use(env->shader_instanced);
	shader_set_uniform_mat4(env->shader_instanced, "view_matrix", env->camera->view_matrix);
	shader_set_uniform_mat4(env->shader_instanced, "proj_matrix", env->proj_matrix);
	shader_set_uniform_vec4(env->shader_instanced, "color", (t_vec4){0.3, 0.2, 0.5, 1.0});
	
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElementsInstanced(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0, entity->instance_count);
	
	shader_use(0);
}
