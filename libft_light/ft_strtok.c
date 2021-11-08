/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:16:46 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:42:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_light.h"

static int	is_delim(char c, const char *delims)
{
	int i;

	i = 0;
	while (delims[i] != '\0')
	{
		if (delims[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	advance_ptr(char *ptr, const char *delims)
{
	int i;

	i = 0;
	while (is_delim(*ptr, delims))
	{
		ptr++;
		i++;
	}
	return (i);
}

char		*ft_strtok(char *src, const char *delims)
{
	static char	*ptr;
	char		*token;

	if (src)
	{
		src += advance_ptr(src, delims);
		ptr = src;
	}
	if (!ptr)
		return (NULL);
	token = ptr;
	while (*ptr != '\0')
	{
		if (is_delim(*ptr, delims))
		{
			*ptr++ = '\0';
			ptr += advance_ptr(ptr, delims);
			break ;
		}
		ptr++;
	}
	ptr += advance_ptr(ptr, delims);
	if (*(ptr) == '\0')
		ptr = NULL;
	return (token);
}
