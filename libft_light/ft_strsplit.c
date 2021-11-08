/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:09:06 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:15:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_light.h"

static int	ft_wordlen(char *str, char end)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != end)
		++i;
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**strs;
	size_t	nwords;
	size_t	i;
	int		len;

	nwords = ft_nwords((char *)s, c);
	if (!(strs = (char **)malloc(sizeof(char *) * (nwords + 1))))
		return (NULL);
	i = 0;
	while (i < nwords)
	{
		while (*s == c)
			s++;
		len = ft_wordlen((char*)s, c);
		if (!(strs[i] = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ft_memcpy(strs[i], s, len);
		strs[i][len] = '\0';
		s += len;
		i++;
	}
	strs[nwords] = NULL;
	return (strs);
}
