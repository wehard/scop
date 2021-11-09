/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:05:05 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:55:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "mesh.h"
#include "ft_get_next_line.h"
#include "libft_light.h"
#include <unistd.h>
#include <fcntl.h>
#include "obj_loader.h"
#include "vec2.h"

static int	count_face_indices(char *line)
{
	size_t	num_indices;
	char	**parts;

	parts = ft_strsplit(line, ' ');
	num_indices = 0;
	while (parts[num_indices])
	{
		++num_indices;
	}
	if (num_indices == 4)
		num_indices = 6;
	free_parts(parts);
	return (num_indices);
}

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
			m->num_indices += count_face_indices(line + 2);
		free(line);
	}
	close(fd);
	m->num_uvs = m->num_vertices;
	m->num_normals = m->num_vertices;
	mesh_create_verts(m, m->num_vertices);
	mesh_create_indices(m, m->num_indices);
	mesh_create_normals(m, m->num_normals);
	mesh_create_uvs(m, m->num_uvs);
}

static void	read_indices(t_mesh *m, size_t i, char *line, size_t *num_indices)
{
	char	**parts;

	parts = ft_strsplit(line + 1, ' ');
	while (parts[*num_indices])
	{
		++*num_indices;
	}
	if (*num_indices == 3)
	{
		m->indices[i + 0] = ft_atoi(parts[0]) - 1;
		m->indices[i + 1] = ft_atoi(parts[1]) - 1;
		m->indices[i + 2] = ft_atoi(parts[2]) - 1;
	}
	else if (*num_indices == 4)
	{
		m->indices[i + 0] = ft_atoi(parts[0]) - 1;
		m->indices[i + 1] = ft_atoi(parts[1]) - 1;
		m->indices[i + 2] = ft_atoi(parts[2]) - 1;
		m->indices[i + 3] = ft_atoi(parts[0]) - 1;
		m->indices[i + 4] = ft_atoi(parts[2]) - 1;
		m->indices[i + 5] = ft_atoi(parts[3]) - 1;
		*num_indices = 6;
	}
	free_parts(parts);
}

void	read_mesh(int fd, t_mesh *m)
{
	char	*line;
	size_t	i[4];
	size_t	temp_indices;

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
		else if (ft_strncmp(line, "f ", 2) == 0)
		{
			temp_indices = 0;
			read_indices(m, i[3], line, &temp_indices);
			i[3] += temp_indices;
		}
		free(line);
	}
}

t_mesh	*obj_load(const char *filename)
{
	t_mesh	*m;
	int		fd;

	m = mesh_create();
	if (!m)
		exit_message("obj_loader: Failed to create mesh!");
	read_mesh_info(m, filename);
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) == -1)
		exit_message("Error loading obj file!");
	read_mesh(fd, m);
	close(fd);
	mesh_center(m);
	mesh_gen_uvs(m);
	return (m);
}
