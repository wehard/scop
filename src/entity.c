/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:58:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/15 12:21:47 by wkorande         ###   ########.fr       */
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
	t_mesh *mesh;

	mesh = entity->mesh;
	glGenVertexArrays(1, &entity->vao_id);
	glBindVertexArray(entity->vao_id);

	glGenBuffers(1, &entity->vbo_id);
	glGenBuffers(1, &entity->ebo_id);

	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh->num_vertices * 3, mesh->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->num_indices, mesh->indices, GL_STATIC_DRAW);
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

	i = 0;
	while (i < instance_count)
	{
		entity->position[i] = ft_make_vec3(0.0, 0.0, 0.0);
		entity->rotation[i] = ft_make_vec3(0.0, 0.0, 0.0);
		entity->scale[i] = ft_make_vec3(1.0, 1.0, 1.0);
		i++;
	}
	
	entity->mesh = mesh;
	entity->shader = shader;
	gen_buffers(entity);
	return (entity);
}

void		entity_draw(t_camera *camera, t_entity *entity, t_vec4 color)
{
	shader_use(entity->shader);
	
	t_mat4 m = mat4_identity();
	t_mat4 v = mat4_identity();
	t_mat4 p = mat4_identity();

	m = mat4_trs(entity->position[0], entity->rotation[0], entity->scale[0]);
	p = mat4_perspective(45.0, 1.6, 0.1, 100.0);
	v = mat4_lookat(camera->position, ft_add_vec3(camera->position, camera->forward), ft_make_vec3(0,1,0));
	shader_set_uniform_mat4(entity->shader, "model_matrix", m);
	shader_set_uniform_mat4(entity->shader, "view_matrix", v);
	shader_set_uniform_mat4(entity->shader, "proj_matrix", p);
	shader_set_uniform_vec4(entity->shader, "color", color);
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElements(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0);
	glUseProgram(0);
}

void	entity_draw_instanced(t_env *env, t_entity *entity)
{
	size_t i;

	i = 0;
	float angle = 0;
	while (i < entity->instance_count)
	{
		entity->position[i].x = cosf(ft_deg_to_rad(angle)) * 30;
		entity->position[i].y = 0;
		entity->position[i].z = sinf(ft_deg_to_rad(angle)) * 30;
		angle += 360.0 / entity->instance_count;
		i++;
	}
	shader_use(entity->shader);
	shader_set_uniform_mat4(entity->shader, "model_matrix", mat4_trs(ft_make_vec3(0, 0, 0), entity->rotation[0], ft_make_vec3(1,1,1)));
	shader_set_uniform_mat4(entity->shader, "view_matrix", env->camera->view_matrix);
	shader_set_uniform_mat4(entity->shader, "proj_matrix", env->proj_matrix);
	shader_set_uniform_vec4(entity->shader, "color", (t_vec4){0.3, 0.2, 0.5, 1.0});
	shader_set_uniform_vec3_array(entity->shader, "positions", entity->position, entity->instance_count);
	
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElementsInstanced(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0, entity->instance_count);
	
	shader_use(0);
}
