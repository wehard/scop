/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:05:05 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/15 20:25:25 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "mesh.h"
#include "ft_get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "ft_printf.h"

static void	read_mesh_info(t_mesh *m, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading model file!");
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v ", 2) == 0)
			m->num_vertices++;
		else if (ft_strncmp(line, "vt", 2) == 0)
			m->num_uvs++;
		else if (ft_strncmp(line, "vn", 2) == 0)
			m->num_normals++;
		else if (ft_strncmp(line, "f ", 2) == 0)
			m->num_indices += 3;
		free(line);
	}
	close(fd);
	m->num_uvs = m->num_vertices;		// !!!
	m->num_normals = m->num_vertices;	// !!!
	mesh_create_verts(m, m->num_vertices);
	mesh_create_indices(m, m->num_indices);
	mesh_create_normals(m, m->num_normals);
	mesh_create_uvs(m, m->num_uvs);
}

// void		triface_calc_bounds(t_triface *t)
// {
// 	size_t i;

// 	t->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
// 	t->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (t->v[i].x < t->bounds.min.x)
// 			t->bounds.min.x = t->v[i].x;
// 		if (t->v[i].y < t->bounds.min.y)
// 			t->bounds.min.y = t->v[i].y;
// 		if (t->v[i].z < t->bounds.min.z)
// 			t->bounds.min.z = t->v[i].z;
// 		if (t->v[i].x > t->bounds.max.x)
// 			t->bounds.max.x = t->v[i].x;
// 		if (t->v[i].y > t->bounds.max.y)
// 			t->bounds.max.y = t->v[i].y;
// 		if (t->v[i].z > t->bounds.max.z)
// 			t->bounds.max.z = t->v[i].z;
// 		i++;
// 	}
// }

// static void	parse_face(t_mesh *m, size_t i, char *line, size_t j)
// {
// 	char	**parts;
// 	char	**tf;
// 	size_t	n;

// 	parts = ft_strsplit(line + 1, ' ');
// 	while (parts[j] && (tf = ft_strsplit(parts[j], '/')))
// 	{
// 		if (!tf[0] || ((n = ft_atoi(tf[0])) && (n > m->num_vertices || n < 1)))
// 			exit_message("Not enough vertices");
// 		m->trifaces[i].v[j] = m->vertices[n - 1];
// 		if (!tf[1] || ((n = ft_atoi(tf[1])) && (n > m->num_uvs || n < 1)))
// 			exit_message("Not enough uvs");
// 		m->trifaces[i].uv[j] = m->uvs[n - 1];
// 		if (!tf[2] || ((n = ft_atoi(tf[2])) && (n > m->num_normals || n < 1)))
// 			exit_message("Not enough normals");
// 		m->trifaces[i].n[j] = m->normals[n - 1];
// 		free_null(5, tf[0], tf[1], tf[2], tf, parts[j]);
// 		j++;
// 	}
// 	free(parts);
// 	m->trifaces[i].e[0] = ft_sub_vec3(m->trifaces[i].v[1], m->trifaces[i].v[0]);
// 	m->trifaces[i].e[1] = ft_sub_vec3(m->trifaces[i].v[2], m->trifaces[i].v[1]);
// 	m->trifaces[i].e[2] = ft_sub_vec3(m->trifaces[i].v[0], m->trifaces[i].v[2]);
// 	m->trifaces[i].normal = m->trifaces[i].n[0];
// 	// triface_calc_bounds(&m->trifaces[i]);
// }

static void read_indices(t_mesh *m, size_t i, char *line)
{
	char	**parts;
	size_t	n;
	size_t j;

	parts = ft_strsplit(line + 1, ' ');
	j = 0;
	while (j < 3)
	{
		m->indices[i + j] = ft_atoi(parts[j]) - 1;
		j++;
	}
}

void		read_mesh(int fd, t_mesh *m)
{
	char	*line;
	size_t	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v ", 2) == 0)
		{
			m->vertices[i[0]++] = ft_parse_vec3(line + 1);
		}
		// else if (ft_strncmp(line, "vt", 2) == 0)
		// 	m->uvs[i[1]++] = ft_parse_vec2(line + 1);
		// else if (ft_strncmp(line, "vn", 2) == 0)
		// 	m->normals[i[2]++] = ft_parse_vec3(line + 2);
		else if (ft_strncmp(line, "f ", 2) == 0)
		{
			read_indices(m, i[3], line); //parse_face(m, i[3]++, line, 0);
			i[3] += 3;
		}
		free(line);
	}
}

static float	ft_abs_f(float f)
{
	if (f < 0.0)
		return (f * -1.0);
	return (f);
}

static int max_axis(t_vec3 v)
{
	if (ft_abs_f(v.x) >= ft_abs_f(v.y) &&  ft_abs_f(v.x) >= ft_abs_f(v.z))
		return (0);
	else if (ft_abs_f(v.y) >= ft_abs_f(v.z) &&  ft_abs_f(v.y) >= ft_abs_f(v.x))
		return (1);
	else
		return (2);
}

static void generate_uvs(t_mesh *mesh)
{
	size_t i;

	i = 0;
	while (i < mesh->num_vertices)
	{
		t_vec2 uv;
		t_vec3 d = ft_normalize_vec3(mesh->vertices[i]);
		int axis = max_axis(d);
		if (axis == 0)
			uv = (t_vec2){ft_abs_f(d.y), ft_abs_f(d.z)};
		else if (axis == 1)
			uv = (t_vec2){ft_abs_f(d.x), ft_abs_f(d.z)};
		else
			uv = (t_vec2){ft_abs_f(d.x), ft_abs_f(d.y)};
		mesh->uvs[i] = uv;
		i++;
	}
}

t_mesh		*obj_load(const char *filename)
{
	t_mesh	*m;
	int		fd;

	if (!(m = mesh_create()))
		return (NULL);
	read_mesh_info(m, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading obj file!");
	read_mesh(fd, m);
	close(fd);
	// mesh_calc_bounds(m);
	generate_uvs(m);
	return (m);
}
