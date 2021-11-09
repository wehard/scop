/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:47:47 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/09 09:21:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_light.h"
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void	exit_message(const char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	free_null(size_t count, ...)
{
	va_list	pl;
	size_t	i;
	void	*param_type;

	i = 0;
	va_start(pl, count);
	while (i < count)
	{
		param_type = va_arg(pl, void *);
		free(param_type);
		param_type = NULL;
		i++;
	}
	va_end(pl);
}

void	free_parts(char **parts)
{
	size_t	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

int	verify_ext(const char *filename, const char *extension)
{
	char	*ext;

	ext = ft_strstr(filename, extension);
	if (!ext)
		return (0);
	return (1);
}

int ft_open(const char *file, int oflags)
{
	int	fd;

	fd = open(file, oflags);
	if (fd < 0)
	{
		ft_putstr("ft_open error: ");
		ft_putstr(file);
		ft_putchar(' ');
		ft_putendl(strerror(errno));
	}
	return (fd);
}