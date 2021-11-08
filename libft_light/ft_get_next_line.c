/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:37:45 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:19:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static int	ft_contains_char(char *str, char c)
{
	while (*(str++) != '\0')
		if (*str == c)
			return (1);
	return (0);
}

static char	*ft_free_and_assign(char *descs, char *tmp)
{
	free(descs);
	descs = tmp;
	return (descs);
}

static int	ft_serve_line(int fd, char **descs, char **line, int bytes)
{
	t_gnl_tmp	gnl;

	if ((bytes < 0))
		return (-1);
	if ((bytes == 0 && descs[fd] == NULL) || descs[fd][0] == '\0')
		return (0);
	gnl.len = 0;
	while (descs[fd][gnl.len] != '\n' && descs[fd][gnl.len] != '\0')
		gnl.len++;
	if (descs[fd][gnl.len] == '\n')
	{
		*line = ft_strsub(descs[fd], 0, gnl.len);
		if (!*line)
			return (-1);
		gnl.tmp = ft_strdup(descs[fd] + gnl.len + 1);
		if (!gnl.tmp)
			return (-1);
		descs[fd] = ft_free_and_assign(descs[fd], gnl.tmp);
	}
	else if (descs[fd][gnl.len] == '\0')
	{
		*line = ft_strdup(descs[fd]);
		ft_free_and_assign(descs[fd], NULL);
	}
	return (1);
}

static int	read_it(t_gnl *gnl, int fd, char **descs)
{
	while (gnl->bytes > 0)
	{
		gnl->bytes = read(fd, gnl->buffer, BUFF_SIZE);
		gnl->buffer[gnl->bytes] = '\0';
		if (descs[fd] == NULL)
		{
			descs[fd] = ft_strdup(gnl->buffer);
			if (!descs[fd])
				return (-1);
		}
		else
		{
			gnl->tmp = ft_strjoin(descs[fd], gnl->buffer);
			if (!gnl->tmp)
				return (-1);
			descs[fd] = ft_free_and_assign(descs[fd], gnl->tmp);
		}
		if (ft_contains_char(descs[fd], '\n'))
			break ;
	}
	return (0);
}

int	ft_get_next_line(const int fd, char **line)
{
	static char	*descs[MAX_FD];
	t_gnl		gnl;
	int			result;

	if (fd < 0 || !line)
		return (-1);
	gnl.bytes = 1;
	result = read_it(&gnl, fd, descs);
	if (result == -1)
		return (-1);
	return (ft_serve_line(fd, descs, line, gnl.bytes));
}
