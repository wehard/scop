/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 09:58:39 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/26 13:58:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>

#include "scop.h"
#include "mesh.h"
#include "shader.h"
#include <math.h>

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

static t_mat4		identity_mat4(void)
{
	t_mat4 m;

	m.data[0] = 1.0;
	m.data[1] = 0.0;
	m.data[2] = 0.0;
	m.data[3] = 0.0;

	m.data[4] = 0.0;
	m.data[5] = 1.0;
	m.data[6] = 0.0;
	m.data[7] = 0.0;

	m.data[8] = 0.0;
	m.data[9] = 0.0;
	m.data[10] = 1.0;
	m.data[11] = 0.0;

	m.data[12] = 0.0;
	m.data[13] = 0.0;
	m.data[14] = 0.0;
	m.data[15] = 1.0;
	return (m);
}

static t_mat4	mul_mat4(t_mat4 a, t_mat4 b)
{
	// t_mat4	c;
	int			x;
	int			y;
	int			i;

	t_mat4 c = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			i = 0;
			while (i < 4)
			{
				c.data[y * 4 + x] += a.data[y * 4 + i] * b.data[i * 4 + x];
				i++;
			}
			x++;
		}
		y++;
	}
	return (c);
}

	// 		T const rad = fov;
	// 		T const h = glm::cos(static_cast<T>(0.5) * rad) / glm::sin(static_cast<T>(0.5) * rad);
	// 		T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

	// 		detail::tmat4x4<T, defaultp> Result(static_cast<T>(0));
	// 		Result[0][0] = w;
	// 		Result[1][1] = h;
	// 		Result[2][2] = - (zFar + zNear) / (zFar - zNear);
	// 		Result[2][3] = - static_cast<T>(1);
	// 		Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);



static t_mat4        create_perspective_matrix(float fov, float aspect, float zn, float zf)
{
        t_mat4        mat;

		mat = identity_mat4();
		float rad = fov;
		float h = cos(rad * 0.5) / sin(rad * 0.5);
		float w = h * aspect;

		mat.data[0] = w;
		mat.data[5] = h;
		mat.data[10] = -(zf + zn) / (zf - zn);
		mat.data[11] = -1.0;
		mat.data[14] = (-2.0 * zf * zn) / (zf - zn);
        return (mat);
}

// template <typename T, precision P>
// 	GLM_FUNC_QUALIFIER detail::tmat4x4<T, P> lookAt
// 	(
// 		detail::tvec3<T, P> const & eye,
// 		detail::tvec3<T, P> const & center,
// 		detail::tvec3<T, P> const & up
// 	)
// 	{
// 		detail::tvec3<T, P> const f(normalize(center - eye));
// 		detail::tvec3<T, P> const s(normalize(cross(f, up)));
// 		detail::tvec3<T, P> const u(cross(s, f));

// 		detail::tmat4x4<T, P> Result(1);
// 		Result[0][0] = s.x;
// 		Result[1][0] = s.y;
// 		Result[2][0] = s.z;
// 		Result[0][1] = u.x;
// 		Result[1][1] = u.y;
// 		Result[2][1] = u.z;
// 		Result[0][2] =-f.x;
// 		Result[1][2] =-f.y;
// 		Result[2][2] =-f.z;
// 		Result[3][0] =-dot(s, eye);
// 		Result[3][1] =-dot(u, eye);
// 		Result[3][2] = dot(f, eye);
// 		return Result;
// 	}


static t_mat4	lookat(t_vec3 from, t_vec3 to, t_vec3 world_up)
{
	t_mat4	m;
	t_vec3		f;
	t_vec3		s;
	t_vec3		u;

	f = ft_normalize_vec3(ft_sub_vec3(to, from));
	s = ft_normalize_vec3(ft_cross_vec3(f, world_up));
	u = ft_cross_vec3(s, f);

	m = identity_mat4();

	m.data[0] = s.x;
	m.data[1] = s.y;
	m.data[2] = s.z;

	m.data[4] = u.x;
	m.data[5] = u.y;
	m.data[6] = u.z;

	m.data[8] = -f.x;
	m.data[9] = -f.y;
	m.data[10] = -f.z;

	m.data[3] = -ft_dot_vec3(s, from);
	m.data[7] = -ft_dot_vec3(u, from);
	m.data[11] = -ft_dot_vec3(f, from);

	// forward = ft_normalize_vec3(ft_sub_vec3(from, to));
	// right = ft_cross_vec3(ft_normalize_vec3(world_up), forward);
	// up = ft_cross_vec3(forward, right);
	// lookat.data[0] = right.x;
	// lookat.data[1] = right.y;
	// lookat.data[2] = right.z;
	// lookat.data[3] = 0.0f;

	// lookat.data[4] = up.x;
	// lookat.data[5] = up.y;
	// lookat.data[6] = up.z;
	// lookat.data[7] = 0.0f;

	// lookat.data[8] = forward.x;
	// lookat.data[9] = forward.y;
	// lookat.data[10] = forward.z;
	// lookat.data[11] = 0.0f;
	
	// t_mat4 temp = {
	// 	1, 0, 0, from.x,
	// 	0, 1, 0, from.y,
	// 	0, 0, 1, from.z,
	// 	0, 0, 0, 1
	// };
	// lookat.data[3] = -from.x;
	// lookat.data[7] = -from.y;
	// lookat.data[11] = -from.z;
	return (m);
}

void		draw_entity(t_camera *camera, t_entity *entity)
{
	glUseProgram(entity->shader->program_id);
	t_mat4 m = identity_mat4();

	t_mat4 v = identity_mat4();
	t_mat4 p = identity_mat4();

	p = create_perspective_matrix(60.0, 720.0 / 1280.0, 0.1, 100.0);
	// v = lookat(camera->position, ft_add_vec3(camera->position, ft_make_vec3(0, 0, 1)), ft_make_vec3(0,1,0));
	shader_set_uniform_mat4(entity->shader, "model_matrix", m);
	shader_set_uniform_mat4(entity->shader, "view_matrix", v);
	shader_set_uniform_mat4(entity->shader, "proj_matrix", p);
	glBindVertexArray(entity->vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo_id);
	glDrawElements(GL_TRIANGLES, entity->mesh->num_indices, GL_UNSIGNED_INT, 0);
	glUseProgram(0);
}
