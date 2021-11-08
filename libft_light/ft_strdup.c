/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:27:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:38:32 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_light.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	if (!(dup = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		dup[i] = *s1;
		s1++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
