/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:58:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/26 17:44:47 by wkorande         ###   ########.fr       */
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

void		draw_entity(t_camera *camera, t_entity *entity)
{
	glUseProgram(entity->shader->program_id);
	t_mat4 m = identity_mat4();

	t_mat4 v = identity_mat4();
	t_mat4 p = identity_mat4();

	// m = mat4_translate((t_vec3){-2,0,0});
	m = mat4_trs(ft_make_vec3(0,0,0), ft_make_vec3(0,45,0), ft_make_vec3(1,1,1));
	// m = mat4_rotate_y(-90.0);
	p = create_perspective_mat4(30.0, 720.0 / 1280.0, -1, 10.0);
	v = lookat_mat4(camera->position, ft_add_vec3(camera->position, ft_make_vec3(0, 0, -1)), ft_make_vec3(0,1,0));
	shader_set_uniform_mat4(entity->shader, "model_matrix", m);
	shader_set_uniform_mat4(entity->shader, "view_matrix", v);
	shader_set_uniform_mat4(entity->shader, "proj_matrix", p);
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElements(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0);
	glUseProgram(0);
}
