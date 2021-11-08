/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:47:47 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 16:55:57 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

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
