/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:58:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/13 23:31:31 by wkorande         ###   ########.fr       */
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * mesh->num_vertices * 3, mesh->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->num_indices, mesh->indices, GL_STATIC_DRAW);
}


t_entity	*create_entity(t_mesh *mesh, t_shader *shader)
{
	t_entity *entity;

	if (!(entity = (t_entity*)malloc(sizeof(t_entity))))
		exit_message("Failed to malloc entity!");
	entity->position = ft_make_vec3(0.0, 0.0, 0.0);
	entity->rotation = ft_make_vec3(0.0, 0.0, 0.0);
	entity->scale = ft_make_vec3(1.0, 1.0, 1.0);
	entity->mesh = mesh;
	entity->shader = shader;
	gen_buffers(entity);
	return (entity);
}

t_entity	*entity_create_instanced(t_mesh *mesh, size_t count)
{
	t_entity *entity;

	if (!(entity = (t_entity*)malloc(sizeof(t_entity))))
		exit_message("Failed to malloc entity!");
	entity->instance_count = count;


	return (entity);
}

void		entity_draw(t_camera *camera, t_entity *entity, t_vec4 color)
{
	glUseProgram(entity->shader->program_id);
	t_mat4 m = mat4_identity();

	t_mat4 v = mat4_identity();
	t_mat4 p = mat4_identity();

	// m = mat4_translate((t_vec3){-2,0,0});
	m = mat4_trs(ft_make_vec3(0, 0, 0), entity->rotation, ft_make_vec3(1,1,1));
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

void	entity_draw_instanced(t_scop *scop, t_entity *entity, size_t count)
{
	glUseProgram(entity->shader->program_id);
	shader_set_uniform_mat4(entity->shader, "model_matrix", mat4_trs(ft_make_vec3(0,0, 0), entity->rotation, ft_make_vec3(1,1,1)));
	shader_set_uniform_mat4(entity->shader, "view_matrix", scop->camera->view_matrix);
	shader_set_uniform_mat4(entity->shader, "proj_matrix", scop->proj_matrix);
	shader_set_uniform_vec4(entity->shader, "color", (t_vec4){1.0, 1.0, 1.0, 1.0});
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElementsInstanced(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0, count);
	glUseProgram(0);
}
